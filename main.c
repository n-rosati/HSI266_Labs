#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

int main() {
    LJ_HANDLE ljHandle = 0;
    LJ_ERROR lj_cue = 0;
    double ljSN;

    lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &ljHandle);

    if (lj_cue == LJE_DEVICE_ALREADY_OPEN) {
        printf("LabJack in use! Exiting\n");
        return 0;
    }
    if (ljHandle == 0) {
        printf("Invalid LabJack handle received. Exiting\n");
        return 0;
    }

    return 0;
}