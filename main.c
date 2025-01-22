

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

    lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &lj_handle);
    lj_cue = ePut(lj_handle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);

    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 6, 0, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 7, 1, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 4.5, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);
    lj_cue = Go();

    while (counter < 300)
    {
        lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 6, 1, 0, 0);
        lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 7, 0, 0, 0);
        lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 0, 0, 0);
        lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 4.5, 0, 0);
        lj_cue = Go();
        lj_cue = GetResult(lj_handle, LJ_ioPUT_DIGITAL_BIT, 6, &ledFIO6);
        lj_cue = GetResult(lj_handle, LJ_ioPUT_DIGITAL_BIT, 7, &ledFIO7);
        lj_cue = GetResult(lj_handle, LJ_ioPUT_DAC, 0, &ledDAC0);
        lj_cue = GetResult(lj_handle, LJ_ioPUT_DAC, 1, &ledDAC1);

        printf("The Amber LED is on FIO6 and should be ON. Output value is %.0lf.\n", ledFIO6);
        printf("The BLUE LED is on FIO7 and should be ON. Output value is %.0lf.\n", ledFIO7);
        printf("The Green LED is on DAC0 and should be OFF. Output value is %.0lf.\n", ledDAC0);
        printf("The Red LED is on DAC1 and should be ON. Output value is %.0lf.\n\n", ledDAC1);

        counter++;
        Sleep(250);

    }

    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 6, 0, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 7, 1, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 4.5, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);
    lj_cue = Go();

    system("pause");
    Close();
    return 0;
}



