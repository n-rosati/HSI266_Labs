#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

int main(void) {
    printf("Driver version: %f\n", GetDriverVersion());
    return 0;
}