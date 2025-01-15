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

        if (btnAIN0 > 4.5) {
            printf("PB1 pressed.\n");
        } else if (btnAIN0 < 0.5){
            printf("PB1 released.\n");
        }

        if (btnAIN1 > 4.5) {
            printf("PB2 pressed.\n");
        } else if (btnAIN1 < 0.5) {
            printf("PB2 released.\n");
        }

        if (btnFIO4 == 0) {
            printf("PB3 pressed.\n");
        } else if (btnFIO4 == 1) {
            printf("PB3 released.\n");
        }

        if (btnFIO5 == 0) {
            printf("PB4 pressed.\n");
        } else if (btnFIO5 == 1) {
            printf("PB4 released.\n");
        }

        printf("\n\n");

        counter++;
        Sleep(100);

    }
    system("pause");
    Close();
    return 0;
}
