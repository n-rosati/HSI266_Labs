/* Name: Nicholas Rosati
 * Program name: HSI266 Lab 6
 * Date 2025-03-06
 * Purpose: Program will present a menu to control the RGB LED in different ways.
 *          Menu item 1 will control the RGB LED using potentiometer input (pin AIN0) and
 *          output accordingly to timer 0, timer 1, and DAC0 to control the LED.
 *          The program will continuously read the potentiometer, set the LED colour, and output to the terminal
 *          every 100ms.
 *          Menu item 2 will allow the user to pick colours from a list and will set the LED to that colour.
 */

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

double clampDouble(double lower, double upper, double val);
double clampInt(int lower, int upper, int val);

int main() {
    LJ_HANDLE lj_handle = 0;
    LJ_ERROR lj_cue = 0;
    double ljSN = 0;
    char userInputMenu1 = '3', userInputMenu2 = '7';
    double btnFIO4, potAIN0;
    double potPercent, redPercent, greenPercent, bluePercent;
    int redValue, greenValue, blueValue;

    lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &lj_handle);
    lj_cue = ePut(lj_handle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);

    lj_cue = eGet(lj_handle, LJ_ioGET_CONFIG, LJ_chSERIAL_NUMBER, &ljSN, 0);
    printf("Serial number: %.0lf\n", ljSN);

    // Set up timers
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 2, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_COUNTER_PIN_OFFSET, 5, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc48MHZ, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmPWM8, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_MODE, 1, LJ_tmPWM8, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 65535, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 1, 65535, 0, 0);
    lj_cue = Go();

    do {
        printf("1. Colour adjusts with potentiometer\n"
               "2. Manual colour choice.\n"
               "3. Exit\n"
               "Enter a number:\n");
        scanf_s("%c", &userInputMenu1, 1);

        switch (userInputMenu1) {
            case '1':
                do {
                    // Get pot value
                    lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 0, 0, 0, 0);
                    lj_cue = Go();
                    lj_cue = GetResult(lj_handle, LJ_ioGET_AIN, 0, &potAIN0);

                    potPercent = potAIN0 / 4.5;
                    redPercent = clampDouble(0.0, 1.0, potPercent / 0.33);
                    greenPercent = clampDouble(0.0, 1.0, (potPercent - 0.33) / 0.33);
                    bluePercent = clampDouble(0.0, 1.0, (potPercent - 0.66) / 0.33);

                    redValue = clampInt(0, 65535, (1.0 - redPercent) * 65535);
                    greenValue = clampInt(0, 65535, (1.0 - greenPercent) * 65535);
                    blueValue = clampInt(0, 5, (1.0 - bluePercent) * 5);

                    // Set colours
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, redValue, 0, 0);
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 1, greenValue, 0, 0);
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, blueValue, 0, 0);
                    lj_cue = Go();

                    // Output state
                    printf("Red LED DC value: %d\tGreen LED DC value: %d\tBlue LED DAC value: %d\n", redValue, greenValue, blueValue);

                    // Get button state
                    lj_cue = AddRequest(lj_handle, LJ_ioGET_DIGITAL_BIT, 4, 0, 0, 0);
                    lj_cue = Go();
                    lj_cue = GetResult(lj_handle, LJ_ioGET_DIGITAL_BIT, 4, &btnFIO4);
                    Sleep(100);
                } while (btnFIO4 < 0.5);
                break;
            case '2':
                do {
                    printf("1. Red\n2. Green\n3. Blue\n4. Violet\n5. Yellow\n6. White\n7. Back to main menu\nEnter a number:\n");
                    scanf_s("%c", &userInputMenu2, 1);
                    switch (userInputMenu2) {
                        case '1': // Red
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 0, 0, 0);
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 1, 65535, 0, 0);
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 0, 0, 0);
                            lj_cue = Go();
                            break;
                        case '2': // Green
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 65535, 0, 0);
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 1, 0, 0, 0);
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 0, 0, 0);
                            lj_cue = Go();
                            break;
                        case '3': // Blue
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 65535, 0, 0);
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 1, 65535, 0, 0);
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 3.3, 0, 0);
                            lj_cue = Go();
                            break;
                        case '4': // Violet
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 0, 0, 0);
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 1, 65535, 0, 0);
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 3.3, 0, 0);
                            lj_cue = Go();
                            break;
                        case '5': // Yellow
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 0, 0, 0);
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 1, 65535, 0, 0);
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 0, 0, 0);
                            lj_cue = Go();
                            break;
                        case '6': // White
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 0, 0, 0);
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 1, 0, 0, 0);
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 3.3, 0, 0);
                            lj_cue = Go();
                            break;
                        default:
                            break;
                    }
                } while (userInputMenu2 != '7');
                break;
            default:
                break;
        }
    } while (userInputMenu1 != '3');

    // Turn off the LED and quit
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 65535, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 1, 65535, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 0, 0, 0);
    lj_cue = Go();
    Close();
    system("pause");
    return 0;
}

/**
 * Clamps a given double value to a given bound
 * @param lower Lower bound
 * @param upper Upper bound
 * @param val Value to clamp
 * @return Clamped value
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

/**
 * Clamps a given int value to a given bound
 * @param lower Lower bound
 * @param upper Upper bound
 * @param val Value to clamp
 * @return Clamped value
 */
double clampInt(int lower, int upper, int val) {
    if (val > upper) {
        return upper;
    }
    if (val < lower) {
        return lower;
    }
    return val;
}