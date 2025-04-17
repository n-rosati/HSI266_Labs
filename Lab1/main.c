/* Name: Nicholas Rosati
 * Program name: HSI266 Lab 1
 * Date: 2025-01-15
 * Purpose: The program runs for 20 seconds and constantly outputs the states of physical buttons.
 *          The program will read button states from the connected LabJack on ports AIN0, AIN1, FIO4, FIO5 then
 *          output to the terminal if the corresponding button (PB1, PB2, etc.) is pressed or released.
 *          When the program is finished, it will close the LabJack device and exit the program.
 */

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

        // Clears the current line in the terminal
        printf("\33[2K\r");

        if (btnAIN0 > 4.5) {
            printf("PB1 pressed.\t");
        } else if (btnAIN0 < 0.5){
            printf("PB1 released.\t");
        }

        if (btnAIN1 > 4.5) {
            printf("PB2 released.\t");
        } else if (btnAIN1 < 0.5) {
            printf("PB2 pressed.\t");
        }

        if (btnFIO4 == 0) {
            printf("PB3 released.\t");
        } else if (btnFIO4 == 1) {
            printf("PB3 pressed.\t");
        }

        if (btnFIO5 == 0) {
            printf("PB4 pressed.\t");
        } else if (btnFIO5 == 1) {
            printf("PB4 released.\t");
        }

        counter++;
        Sleep(100);

    }
    system("pause");
    Close();
    return 0;
}



// Output

/*
 * Before
  Nicholas2025-01-15 14:37:16  C:/Users/Nicholas/Documents/Coding/HSI/Lab1/cmake-build-debug  fbdbe6f   
➜ .\Lab1.exe
The voltage reading of PB1 is: 0.04V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.05V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.05V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.04V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.04V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.05V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.07V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.05V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.05V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.04V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.05V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.05V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 5.06V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 5.06V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 5.06V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 5.06V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.00V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.02V
The voltage reading of PB2 is: 0.01V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.02V
The voltage reading of PB2 is: 0.01V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 0.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.03V
The voltage reading of PB2 is: 0.01V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.01V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.05V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 1V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.08V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 1V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.06V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 1V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.05V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 1V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.10V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 1V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.01V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.04V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 0V

The voltage reading of PB1 is: 0.06V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 0V

The voltage reading of PB1 is: 0.09V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 0V

The voltage reading of PB1 is: 0.08V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 0V

The voltage reading of PB1 is: 0.11V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 0V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.01V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.01V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.01V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.01V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.01V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.01V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.01V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.06V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 1V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.07V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 1V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.07V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 1V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.07V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 1V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.02V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.00V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.03V
The voltage reading of PB2 is: 0.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.03V
The voltage reading of PB2 is: 0.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.04V
The voltage reading of PB2 is: 0.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.03V
The voltage reading of PB2 is: 0.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 5.05V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 5.06V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 5.06V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 5.06V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 5.06V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.02V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.02V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.02V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.02V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.02V
The voltage reading of PB2 is: 5.02V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

The voltage reading of PB1 is: 0.01V
The voltage reading of PB2 is: 5.03V
The state reading of PB3 is: 0V
The state reading of PB4 is: 1V

Press any key to continue . . .
 */

/* After
 * ➜ .\Lab1.exe
 * PB1 released.   PB2 released.   PB3 released.   PB4 released.
 */