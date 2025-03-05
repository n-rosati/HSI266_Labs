#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

int main() {
    LJ_HANDLE lj_handle = 0;
    LJ_ERROR lj_cue = 0;
    double ljSN = 0;
    char userInputMenu1 = '3', userInputMenu2 = '7';
    double btnFIO4, potAIN0;

    lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &lj_handle);
    lj_cue = ePut(lj_handle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);

    lj_cue = eGet(lj_handle, LJ_ioGET_CONFIG, LJ_chSERIAL_NUMBER, &ljSN, 0);
    printf("Serial number: %.0lf\n", ljSN);

    // Set up timers
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 2, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_COUNTER_PIN_OFFSET, 5, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc12MHZ_DIV, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_DIVISOR, 3, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmPWM16, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 65535, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 1, 65535, 0, 0);
    lj_cue = Go();

    do {
        printf("1. Colour adjusts with potentiometer\n"
               "2. Manual colour choice.\n"
               "3. Exit\n"
               "Enter a number:\n");
        scanf_s("%d\n", &userInputMenu1);

        switch (userInputMenu1) {
            case '1':

                break;
            case '2':
                do {
                    printf("1. Red\n2. Green.\n3. Blue\n4. Violet\n5. Yellow\n6.White\n7. Back to main menu\nEnter a number:");
                    scanf_s("%d\n", &userInputMenu2);
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