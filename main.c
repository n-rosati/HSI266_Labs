#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

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

    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_COUNTER_PIN_OFFSET, 4, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc1MHZ_DIV, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_DIVISOR, 5, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 1, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmPWM16, 0, 0);
    lj_cue = Go();

    while (counter < 300)
    {
        lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 32768, 0, 0);
        Sleep(100);
        counter++;
    }

    system("pause");
    Close();
    return 0;
}


/* OUTPUT
The serial number of the LabJack is: 320093113
*/