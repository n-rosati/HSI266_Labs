/* Name: Nicholas Rosati
 * Program name: HSI266 Lab 4
 * Date: 2025-02-05
 * Purpose: The program runs for 30 seconds then quits. It will wait for user input on buttons connected to AIN0, AIN1, AIN2.
 *          When a button is pressed, the program will output to the console that the button is pressed and the associated LED state,
 *          at a rate of 10 updates/second.
 *          When button 1 is pressed, the red LED will turn on. When it is released it will turn off.
 *          When button 2 is pressed, the blue LED turns off and the amber one turns on. When it is released, the LEDs turn on and off respectively.
 *          When button 3 is pressed, the buzzer will turn on. When it is released it will turn off.
 */

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

int main() {
    LJ_ERROR lj_cue = 0;
    LJ_HANDLE lj_handle = 0;
    double labjackSerialNumber = 0;
    double pu_btnAIN0 = 0, pu_btnAIN1 = 0, pd_btnAIN2 = 0;
    double al_ledFIO4 = 0, dac1LEDs = 0;
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
    lj_cue = Go();

    while (counter < 300) {
        lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 0, 0, 0, 0);
        lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 1, 0, 0, 0);
        lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 2, 0, 0, 0);
        Go();
        lj_cue = GetResult(lj_handle, LJ_ioGET_AIN, 0, &pu_btnAIN0);
        lj_cue = GetResult(lj_handle, LJ_ioGET_AIN, 1, &pu_btnAIN1);
        lj_cue = GetResult(lj_handle, LJ_ioGET_AIN, 2, &pd_btnAIN2);

        // Button 1 and red LED
        if (pu_btnAIN0 < 0.5) {
            lj_cue = AddRequest(lj_handle, LJ_ioDIGITAL_BIT_OUT, 4, 0, 0, 0);
            Go();
            printf("Button 1 pressed, red LED is on\n");
        } else if (pu_btnAIN0 > 4.5) {
            lj_cue = AddRequest(lj_handle, LJ_ioDIGITAL_BIT_OUT, 4, 1, 0, 0);
            Go();
        }

        // Button 2 and amber/blue LEDs
        if (pu_btnAIN1 < 0.5) {
            lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);
            Go();
            printf("Button 2 pressed, amber LED is on and blue LED is off\n");
        } else if (pu_btnAIN1 > 4.5) {
            lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 5, 0, 0);
            Go();
        }

        // Button 3 and the dreaded buzzer
        if (pd_btnAIN2 > 4.5) {
            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 32768, 0, 0);
            Go();
            printf("Button 3 pressed, buzzer is on\n");
        } else if (pd_btnAIN2 < 0.5) {
            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 65536, 0, 0);
            Go();
        }

        Sleep(100);
        counter++;
    }

    Close();
    system("pause");
    return 0;
}

/* OUTPUT
➜ .\Lab4.exe
The serial number of the LabJack is: 320093113
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 3 pressed, buzzer is on
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 2 pressed, amber LED is on and blue LED is off
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
Button 1 pressed, red LED is on
*/