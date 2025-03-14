/* Name: Nicholas Rosati
 * Program name: HSI266 Lab 7
 * Date 2025-03-13
 * Purpose: The program starts by printing the connected LabJack serial number to the console.
 *          Next, the program will run and do nothing until the ambient light sensor, connected to AIN0, detects darkness.
 *          When darkness is detected, FIO5 is set high which will activate a relay that energizes a solenoid.
 *          The solenoid will then block an optical sensor (connected to AIN1). When the optical sensor is blocked,
 *          FIO4 will output a 3Hz 50% duty cycle PWM signal to flash an LED.
 *          When the ambient light sensor detects light again, the solenoid is de-energized and the LED is turned off.
 *          This series of events can happen 3 times before the program ends.
 */

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
    AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_COUNTER_PIN_OFFSET, 4, 0, 0);
    AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc1MHZ_DIV, 0, 0);
    AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_DIVISOR, 5, 0, 0);
    AddRequest(lj_handle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmPWM16, 0, 0);
    AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 65535, 0, 0);
    Go();

    while (count < 3){
        AddRequest(lj_handle, LJ_ioGET_AIN, 0, 0, 0, 0);
        Go();
        GetResult(lj_handle, LJ_ioGET_AIN, 0, &ambientLightSens);

        // Detect the ambient light sensor to activate the solenoid
        if (ambientLightSens < 1.0 && stickyBit == 0) {
            stickyBit = 1;
            AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 5, 1, 0, 0);
            Go();
        } else if (ambientLightSens > 1.0 && stickyBit == 1) {
            count++;
            stickyBit = 0;
            AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 5, 0, 0, 0);
            Go();
        }

        // Get the state of the optical sensor AFTER the solenoid state is changed (and it finishes moving)
        Sleep(100);
        AddRequest(lj_handle, LJ_ioGET_AIN, 1, 0, 0, 0);
        Go();
        GetResult(lj_handle, LJ_ioGET_AIN, 1, &opticalSens);

        // Make the red LED blink when the optical sensor is not blocked
        if (opticalSens > 4.0) {
            AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 32768, 0, 0);
            Go();
        } else {
            AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 65535, 0, 0);
            Go();
        }
    }

    // Turn off the solenoid, in case it's still on
    AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 5, 0, 0, 0);
    Go();

    Close();
}

/* OUTPUT

Serial number: 320093113
*/