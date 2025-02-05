#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

int main() {
    LJ_ERROR lj_cue;
    LJ_HANDLE lj_handle = 0;
    double labjackSerialNumber;
    double pu_btnAIN0, pu_btnAIN1, pd_btnAIN2;
    double al_ledFIO4, dac1leds;
    int counter = 0;

    lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &lj_handle);
    lj_cue = ePut(lj_handle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);

    // LabJack serial numebr
    lj_cue = eGet(lj_handle, LJ_ioGET_CONFIG, LJ_chSERIAL_NUMBER, &labjackSerialNumber, 0);
    printf("The serial number of the LabJack is: %.0lf\n", labjackSerialNumber);

    // Enable and set up timer
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 1, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_COUNTER_PIN_OFFSET, 5, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc48MHZ_DIV, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_DIVISOR, 47, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmPWM8, 0, 0);
    lj_cue = Go();

    // Set up the other I/O
    lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 0, 0, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 1, 0, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 2, 0, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 4, 1, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);

    while (counter < 300) {


        Sleep(100);
        counter++;
    }
}