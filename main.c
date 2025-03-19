#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

const char* writeTime(void);

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



    Close();
    return 0;
}

const char* writeTime(void) {
    time_t curTime;
    time(&curTime);
    return ctime(&curTime);
}