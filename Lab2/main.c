// Program name: HSI266 Lab 2
// Name: Nicholas Rosati
// Date: 2024-01-22
// Program description: Program will run for about 15 seconds. It uses FIO6, FIO7, DAC0, and DAC1 to turn on four LEDs.
//                      It will turn on the LEDs, one at a time, in sequence of amber, blue, green, red using the previously mentioned IO channels.
//                      It will also cycle which LED is on every 1 second, while outputting to the console the status
//                      of the LEDs every 250ms.

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

int main()
{
    LJ_ERROR lj_cue;
    LJ_HANDLE lj_handle = 0;
    double ledFIO6, ledFIO7, ledDAC0, ledDAC1;
    int counter=0;
    int quarterSeconds = 0;
    int nextScene = 0;

    lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &lj_handle);
    lj_cue = ePut(lj_handle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);

    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 6, 0, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 7, 1, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 0, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);
    lj_cue = Go();

    while (counter < 60) // 15 seconds / 0.25s per screen update
    {
        if (quarterSeconds == 4) {
            switch (nextScene) {
                case 0:
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 6, 1, 0, 0);
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 7, 1, 0, 0);
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 0, 0, 0);
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);
                    lj_cue = Go();
                    nextScene = 1;
                    break;
                case 1:
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 6, 0, 0, 0);
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 7, 0, 0, 0);
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 0, 0, 0);
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);
                    lj_cue = Go();
                    nextScene = 2;
                    break;
                case 2:
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 6, 0, 0, 0);
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 7, 1, 0, 0);
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 0, 0, 0);
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 4.5, 0, 0);
                    lj_cue = Go();
                    nextScene = 3;
                    break;
                case 3:
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 6, 0, 0, 0);
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 7, 1, 0, 0);
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 4.5, 0, 0);
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);
                    lj_cue = Go();
                    nextScene = 0;
                    break;
            }

            quarterSeconds = 0;
        }

        lj_cue = GetResult(lj_handle, LJ_ioPUT_DIGITAL_BIT, 6, &ledFIO6);
        lj_cue = GetResult(lj_handle, LJ_ioPUT_DIGITAL_BIT, 7, &ledFIO7);
        lj_cue = GetResult(lj_handle, LJ_ioPUT_DAC, 0, &ledDAC0);
        lj_cue = GetResult(lj_handle, LJ_ioPUT_DAC, 1, &ledDAC1);

        printf("The Amber LED is on FIO6 and should be %s.\n", ledFIO6 == 0 ? "off" : "on");
        printf("The BLUE LED is on FIO7 and should be %s.\n", ledFIO7 == 1 ? "off" : "on");
        printf("The Green LED is on DAC0 and should be %s.\n", ledDAC1 > 4 && ledDAC0 < 0.5 ? "on" : "off");
        printf("The Red LED is on DAC1 and should be %s.\n\n", ledDAC0 > 4 && ledDAC1 < 0.5 ? "on" : "off");

        Sleep(250);
        quarterSeconds++;
        counter++;
    }

    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 6, 0, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 7, 1, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 0, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);
    lj_cue = Go();

    system("pause");
    Close();
    return 0;
}


/** OUTPUT **/
/* Before

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.

The Amber LED is on FIO6 and should be ON. Output value is 1.
The BLUE LED is on FIO7 and should be ON. Output value is 0.
The Green LED is on DAC0 and should be OFF. Output value is 0.
The Red LED is on DAC1 and should be ON. Output value is 4.
*/

/* After
The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be on.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be on.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be on.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be on.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be on.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be on.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be on.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be on.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be on.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be on.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be on.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be on.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be on.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be on.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be on.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be on.

The Amber LED is on FIO6 and should be on.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be on.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be on.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be on.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be on.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be on.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be on.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be on.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be on.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be on.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be on.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be on.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be on.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be on.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be on.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be on.

The Amber LED is on FIO6 and should be on.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be on.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be on.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be on.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be on.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be on.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be on.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be on.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be on.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be on.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be on.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be on.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be on.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be on.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be on.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be on.

The Amber LED is on FIO6 and should be on.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be on.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be on.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be on.
The BLUE LED is on FIO7 and should be off.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be on.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be on.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be on.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.

The Amber LED is on FIO6 and should be off.
The BLUE LED is on FIO7 and should be on.
The Green LED is on DAC0 and should be off.
The Red LED is on DAC1 and should be off.*/
