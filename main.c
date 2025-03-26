/* Name: Nicholas Rosati
 * Date: 2025-03-26
 * Purpose:
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

#define MAX_TEMP 27
#define MIN_TEMP 18

double clampDouble(double lower, double upper, double val);
const char* writeTime(void);

int main() {
    LJ_HANDLE ljHandle = 0;
    LJ_ERROR lj_cue = 0;
    double ljSN, btnAIN1pd, temperatureSens, temperature, temperatureRangePercent, pwmPercent, outputValue;
    int counter = 0;

    lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &ljHandle);

    if (lj_cue == LJE_DEVICE_ALREADY_OPEN) {
        printf("LabJack in use! Exiting\n");
        return 0;
    }
    if (ljHandle == 0) {
        printf("Invalid LabJack handle received. Exiting\n");
        return 0;
    }

    ePut(ljHandle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);
    eGet(ljHandle, LJ_ioGET_CONFIG, LJ_chSERIAL_NUMBER, &ljSN, 0);
    printf("Serial number: %.0lf\n", ljSN);

    // Timer setup
    AddRequest(ljHandle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 1, 0, 0);
    AddRequest(ljHandle, LJ_ioPUT_CONFIG, LJ_chTIMER_COUNTER_PIN_OFFSET, 4, 0, 0);
    AddRequest(ljHandle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc48MHZ, 0, 0);
    AddRequest(ljHandle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmPWM8, 0, 0);
    AddRequest(ljHandle, LJ_ioPUT_TIMER_VALUE, 0, 65535, 0, 0);
    Go();

    do {
        AddRequest(ljHandle, LJ_ioGET_AIN, 0, 0, 0, 0);
        AddRequest(ljHandle, LJ_ioGET_AIN, 1, 0, 0, 0);
        Go();
        GetResult(ljHandle, LJ_ioGET_AIN, 0, &temperatureSens);
        temperature = temperatureSens * 100;
        GetResult(ljHandle, LJ_ioGET_AIN, 1, &btnAIN1pd);

        if (counter % 10 == 0) {
            temperatureRangePercent = (temperature - MIN_TEMP) / (MAX_TEMP - MIN_TEMP);
            pwmPercent = 1.0 - temperatureRangePercent;
            outputValue = clampDouble(0, 65535, pwmPercent * 65535);
            AddRequest(ljHandle, LJ_ioPUT_TIMER_VALUE, 0, outputValue, 0, 0);
            Go();
            printf("Temperature: %.1f, Fan status: %.1f\n", temperature, pwmPercent);
        }

        if (counter % 150 == 0) {
            //TODO
        }

        counter++;
        Sleep (100);
    } while (btnAIN1pd < 0.5);

    return 0;
}

/**
 * Clamps a given double value to a given bound
 * @param lower Lower bound
 * @param upper Upper bound
 * @param val Value to clamp
 * @return Clamped value (double)
 */
double clampDouble(double lower, double upper, double val) {
    if (val > upper) {
        return upper;
    }
    if (val < lower) {
        return lower;
    }
    return val;
}

const char* writeTime(void) {
    time_t curTime;
    time(&curTime);
    return ctime(&curTime);
}