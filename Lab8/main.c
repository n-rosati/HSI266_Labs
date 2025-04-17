/* Name: Nicholas Rosati
 * Date: 2025-03-19
 * Purpose: The program continuously monitors the inputs FIO4, FIO5, and AIN0. FIO4 is a reed sensor, FIO5 is a button, and AIN0 is a pressure sensor.
 *          When the reed sensor is low and pressure sensor is high, the buzzer on FIO6 will sound.
 *          The buzzer will continue to sound until the push button is pressed.
 *
 *          The program will also log the date and time to a file called `log.txt` every 10 seconds. When the alarm
 *          is triggered, an additional line is written to the file saying the alarm was triggered.
 */

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

const char* writeTime(void);

int main() {
    LJ_HANDLE lj_handle = 0;
    LJ_ERROR lj_cue = 0;
    double ljSN = 0;
    double reedSens, pressSens, btnFIO5;
    int counter = 0, alarm = 0, tone = 0;

    lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &lj_handle);
    lj_cue = ePut(lj_handle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);

    lj_cue = eGet(lj_handle, LJ_ioGET_CONFIG, LJ_chSERIAL_NUMBER, &ljSN, 0);
    printf("Serial number: %.0lf\n", ljSN);

    // Timer setup
    AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 1, 0, 0);
    AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_COUNTER_PIN_OFFSET, 6, 0, 0);
    AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc1MHZ_DIV, 0, 0);
    AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_DIVISOR, 15, 0, 0);
    AddRequest(lj_handle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmPWM8, 0, 0);
    AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 0, 0, 0);
    Go();

    // Open the file
    FILE* fp;
    fopen_s(&fp, "log.txt", "w");

    // Get initial button state
    AddRequest(lj_handle, LJ_ioGET_DIGITAL_BIT, 5, 0, 0, 0);
    Go();
    GetResult(lj_handle, LJ_ioGET_DIGITAL_BIT, 5, &btnFIO5);

    while (btnFIO5 == 0) {
        // Get sensor inputs
        AddRequest(lj_handle, LJ_ioGET_DIGITAL_BIT, 4, 0, 0, 0);
        AddRequest(lj_handle, LJ_ioGET_DIGITAL_BIT, 5, 0, 0, 0);
        AddRequest(lj_handle, LJ_ioGET_AIN, 0, 0, 0, 0);
        Go();
        GetResult(lj_handle, LJ_ioGET_DIGITAL_BIT, 4, &reedSens);
        GetResult(lj_handle, LJ_ioGET_DIGITAL_BIT, 5, &btnFIO5);
        GetResult(lj_handle, LJ_ioGET_AIN, 0, &pressSens);

        if (reedSens == 0 && pressSens > 4.5 && alarm == 0) {
            fprintf(fp, "%s\n⚠️ALARM TRIGGERED!⚠️\n\nReed sensor: %.0f\tPressure sensor: %.2f\n", writeTime(), reedSens, pressSens);
            alarm = 1;
        }

        if (alarm && (counter % 5 == 0)) {
            if (tone == 0) {
                AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 32768, 0 , 0);
                Go();
            } else {
                AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 49151, 0 , 0);
                Go();
            }

            tone = !tone;
        }

        if (counter % 100 == 0) {
            fprintf(fp, "%sReed sensor: %.0f\tPressure sensor: %.2f\n", writeTime(), reedSens, pressSens);
        }

        counter++;
        Sleep(100);
    }

    fclose(fp);
    AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 0, 0 , 0);
    Go();
    Close();
    return 0;
}

const char* writeTime(void) {
    time_t curTime;
    time(&curTime);
    return ctime(&curTime);
}

/* CONSOLE OUTPUT
Serial number: 320093113
*/