#include <stdio.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

int main() {
    printf("Driver version: %f\n", GetDriverVersion());
    return 0;
}