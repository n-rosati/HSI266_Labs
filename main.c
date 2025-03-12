#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

int main() {
    LJ_HANDLE lj_handle = 0;
    LJ_ERROR lj_cue = 0;
    double ljSN = 0;
    double ambientLightSens, opticalSens;
    int count = 0, stickyBit = 0;

    lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &lj_handle);
    lj_cue = ePut(lj_handle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);

    lj_cue = eGet(lj_handle, LJ_ioGET_CONFIG, LJ_chSERIAL_NUMBER, &ljSN, 0);
    printf("Serial number: %.0lf\n", ljSN);

    // Set up initial timer
    AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 1, 0, 0);
    AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_COUNTER_PIN_OFFSET, 5, 0, 0);
    AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc12MHZ_DIV, 0, 0);
    AddRequest(lj_handle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmPWM8, 0, 0);
    AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 65535, 0, 0);
    Go();

    while (count < 3){
        AddRequest(lj_handle, LJ_ioGET_AIN, 0, 0, 0, 0);
        AddRequest(lj_handle, LJ_ioGET_AIN, 1, 0, 0, 0);
        Go();
        GetResult(lj_handle, LJ_ioGET_AIN, 0, &ambientLightSens);
        GetResult(lj_handle, LJ_ioGET_AIN, 1, &opticalSens);

        // Detect the ambient light sensor to activate the servo
        if (ambientLightSens < 1.0 && stickyBit == 0) {
            count++;
            stickyBit = 1;
            AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 4, 1, 0, 0);
            Go();
        } else {
            stickyBit = 0;
            AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 4, 0, 0, 0);
            Go();
        }

        // Make the red LED blink
        if (opticalSens > 4.5) {
            AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 32768, 0, 0);
            Go();
        } else {
            AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 65535, 0, 0);
            Go();
        }
    }

    Close();
}