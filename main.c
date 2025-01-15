#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

int main() {
    LJ_ERROR lj_cue;
    LJ_HANDLE lj_handle = 0;
    double btnAIN0, btnAIN1, btnFIO4, btnFIO5;
    int counter=0;

    lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &lj_handle);
    lj_cue = ePut(lj_handle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);

    while (counter < 200)
    {
        lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 0, 0, 0, 0);
        lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 1, 0, 0, 0);
        lj_cue = AddRequest(lj_handle, LJ_ioGET_DIGITAL_BIT, 4, 0, 0, 0);
        lj_cue = AddRequest(lj_handle, LJ_ioGET_DIGITAL_BIT, 5, 0, 0, 0);
        lj_cue = Go();
        lj_cue = GetResult(lj_handle, LJ_ioGET_AIN, 0, &btnAIN0);
        lj_cue = GetResult(lj_handle, LJ_ioGET_AIN, 1, &btnAIN1);
        lj_cue = GetResult(lj_handle, LJ_ioGET_DIGITAL_BIT, 4, &btnFIO4);
        lj_cue = GetResult(lj_handle, LJ_ioGET_DIGITAL_BIT, 5, &btnFIO5);

        printf("The voltage reading of PB1 is: %.2lfV\n", btnAIN0);
        printf("The voltage reading of PB2 is: %.2lfV\n", btnAIN1);
        printf("The state reading of PB3 is: %.0lfV\n", btnFIO4);
        printf("The state reading of PB4 is: %.0lfV\n\n", btnFIO5);

        counter++;
        Sleep(100);

    }
    system("pause");
    Close();
    return 0;
}
