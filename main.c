/* Name: Nicholas Rosati
 * Program name: HSI266 Lab 5
 * Date 2025-02-12
 * Purpose: The program will run for 20 seconds. It will use DAC0 and DAC1 to control a bipolar LED, FIO5 to control a buzzer, and AIN1 and AIN2 to read the states of two push buttons.
 *          When button 1 is pressed, it will toggle the bipolar LED's colour. When button 2 is pressed (and held) it will turn on the buzzer as well as output the buzzer state
 *          to the console at a rate of 10 updates/second
 */

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

int convertAINtoDigital(double val);

int main() {
    LJ_HANDLE lj_handle = 0;
    LJ_ERROR lj_cue = 0;
    double ljSN = 0;
    double btn_puAIN1 = 0;
    double btn_pdAIN2 = 0;
    double ledState = 0;
    int btn1State = 0;
    int btn1OldState = 0;
    int ticks = 0;

    lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &lj_handle);
    lj_cue = ePut(lj_handle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);

    lj_cue = eGet(lj_handle, LJ_ioGET_CONFIG, LJ_chSERIAL_NUMBER, &ljSN, 0);
    printf("Serial number: %.0lf\n", ljSN);

    // Set up timer
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 1, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_COUNTER_PIN_OFFSET, 5, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc48MHZ_DIV, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_DIVISOR, 47, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmPWM8, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_ioPUT_TIMER_VALUE, 65536, 0, 0);
    Go();

    while (ticks < 200) {
        // get states
        lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 1, 0, 0, 0);
        lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 2, 0, 0, 0);
        Go();
        lj_cue = GetResult(lj_handle, LJ_ioGET_AIN, 1, &btn_puAIN1);
        lj_cue = GetResult(lj_handle, LJ_ioGET_AIN, 2, &btn_pdAIN2);

        btn1State = convertAINtoDigital(btn_puAIN1);
        // If the button is being pressed (not released) AND it's state is different from the previous cycle
        if (btn1State == 1 && (btn1State ^ btn1OldState)) {
            if (ledState == 0) {
                lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 5, 0, 0);
                lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);
                ledState = 1;
            } else {
                lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 0, 0, 0);
                lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 5, 0, 0);
                ledState = 0;
            }
            Go();
        }
        btn1OldState = btn1State;

        // Buzzer logic controlled by a pull down input
        if (convertAINtoDigital(btn_pdAIN2)) {
            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 32768, 0, 0);
            Go();
            printf("The buzzer is on\n");
        } else {
            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 65536, 0, 0);
            Go();
        }

        Sleep(100);
        ticks++;
    }

    Close();
    system("pause");
    return 0;
}

int convertAINtoDigital(const double val) {
    return val > 4.5 ? 1 : 0;
}


/* OUTPUT
Serial number: 320093113
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
The buzzer is on
Press any key to continue . . .
 */
