// Program name: HSI266 Lab 3
// Name: Nicholas Rosati
// Date: 2025-01-29
// Program description: Program will run for 20 seconds. It uses FIO7 as output to control a FET.
//                      It first output the connected LabJack's serial number, hardware, and firmware versions.
//                      Next, it will set up timer 0 with a (almost) 1kHz frequency and 0% duty cycle.
//                      It will then gradually brighten the LED by smoothly raising the duty cycle to 100%

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

#define COUNTER_MAX 300

int main()
{
    LJ_ERROR lj_cue;
    LJ_HANDLE lj_handle = 0;
    double snLJ;
    double hwverLJ;
    double firmverLJ;
    int counter = 0;

    lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &lj_handle);
    lj_cue = ePut(lj_handle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);

    lj_cue = eGet(lj_handle, LJ_ioGET_CONFIG, LJ_chSERIAL_NUMBER, &snLJ, 0);
    lj_cue = eGet(lj_handle, LJ_ioGET_CONFIG, LJ_chHARDWARE_VERSION, &hwverLJ, 0);
    lj_cue = eGet(lj_handle, LJ_ioGET_CONFIG, LJ_chFIRMWARE_VERSION, &firmverLJ, 0);
    printf("The serial number of the LabJack is: %.0lf\n", snLJ);
    printf("The hardware version of the LabJack is: %.2lf\n", hwverLJ);
    printf("The firmware version of the LabJack is: %.2lf\n", firmverLJ);

    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_COUNTER_PIN_OFFSET, 7, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 1, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc1MHZ_DIV, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_DIVISOR, 4, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmPWM8, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 65535, 0, 0);
    lj_cue = Go();


    float nextOnPercent = 0.0;
    float currentOnPercent = 0.0;
    int outputValue = 0.0;
    while (counter <= COUNTER_MAX)
    {
        nextOnPercent = (float) counter / COUNTER_MAX;
        outputValue = (int) ((1 - nextOnPercent) * 65535);

        if ((int)(currentOnPercent * 100) != (int)(nextOnPercent * 100)) {
            printf("LED output power is now: %.0f\n", nextOnPercent * 100);

            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, outputValue, 0, 0);
            lj_cue = Go();
        }

        currentOnPercent = nextOnPercent;
        counter++;
        Sleep(50);
    }

    system("pause");
    Close();
    return 0;
}


/* OUTPUT BEFORE
The serial number of the LabJack is: 320093113
*/


/* OUTPUT AFTER
The serial number of the LabJack is: 320093113
The hardware version of the LabJack is: 1.30
The firmware version of the LabJack is: 1.46
LED output power is now: 1
LED output power is now: 2
LED output power is now: 3
LED output power is now: 4
LED output power is now: 5
LED output power is now: 6
LED output power is now: 7
LED output power is now: 8
LED output power is now: 9
LED output power is now: 10
LED output power is now: 11
LED output power is now: 12
LED output power is now: 13
LED output power is now: 14
LED output power is now: 15
LED output power is now: 16
LED output power is now: 17
LED output power is now: 18
LED output power is now: 19
LED output power is now: 20
LED output power is now: 21
LED output power is now: 22
LED output power is now: 23
LED output power is now: 24
LED output power is now: 25
LED output power is now: 26
LED output power is now: 27
LED output power is now: 28
LED output power is now: 29
LED output power is now: 30
LED output power is now: 31
LED output power is now: 32
LED output power is now: 33
LED output power is now: 34
LED output power is now: 35
LED output power is now: 36
LED output power is now: 37
LED output power is now: 38
LED output power is now: 39
LED output power is now: 40
LED output power is now: 41
LED output power is now: 42
LED output power is now: 43
LED output power is now: 44
LED output power is now: 45
LED output power is now: 46
LED output power is now: 47
LED output power is now: 48
LED output power is now: 49
LED output power is now: 50
LED output power is now: 51
LED output power is now: 52
LED output power is now: 53
LED output power is now: 54
LED output power is now: 55
LED output power is now: 56
LED output power is now: 57
LED output power is now: 58
LED output power is now: 59
LED output power is now: 60
LED output power is now: 61
LED output power is now: 62
LED output power is now: 63
LED output power is now: 64
LED output power is now: 65
LED output power is now: 66
LED output power is now: 67
LED output power is now: 68
LED output power is now: 69
LED output power is now: 70
LED output power is now: 71
LED output power is now: 72
LED output power is now: 73
LED output power is now: 74
LED output power is now: 75
LED output power is now: 76
LED output power is now: 77
LED output power is now: 78
LED output power is now: 79
LED output power is now: 80
LED output power is now: 81
LED output power is now: 82
LED output power is now: 83
LED output power is now: 84
LED output power is now: 85
LED output power is now: 86
LED output power is now: 87
LED output power is now: 88
LED output power is now: 89
LED output power is now: 90
LED output power is now: 91
LED output power is now: 92
LED output power is now: 93
LED output power is now: 94
LED output power is now: 95
LED output power is now: 96
LED output power is now: 97
LED output power is now: 98
LED output power is now: 99
LED output power is now: 100
*/