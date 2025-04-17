/* Name: Nicholas Rosati
* Program name: HSI266 Lab 10
 * Date 2025-04-02
 * Purpose: The program will continuously monitor a rolling ball sensor and IR sensor on channels FIO7 and AIN0 respectively.
 *          When he IR sensor is triggered, it will actuate a servo motor on FIO6 to the 90 degree position, and hold it
 *          there for 3 seconds. It will also update the HTML to say when the last time the IR sensor was triggered.
 *          After three seconds, it will return to the 0 degree position.
 *          If the rolling ball sensor is triggered, the program will end and update the HTML to say when the program ended.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

#define PIN_RB_SENS     7
#define PIN_IR_SENS     5
#define PIN_SERVO       6

#define SERVO_90    63000
#define SERVO_0     60250

const char* writeTime();
void updateHTML(int wasTipped);

int main() {
    LJ_HANDLE ljHandle = 0;
    LJ_ERROR lj_cue = 0;
    double ljSN, irSensor, rbSensor;
    int loopCounter = 0, servoCounter = 0;

    lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &ljHandle);

    if (lj_cue == LJE_DEVICE_ALREADY_OPEN) {
        printf("LabJack in use! Exiting\n");
        return 0;
    }

    if (ljHandle == 0) {
        printf("Invalid LabJack handle received. Exiting\n");
        return 0;
    }

    lj_cue = eGet(ljHandle, LJ_ioGET_CONFIG, LJ_chSERIAL_NUMBER, &ljSN, 0);
    printf("Serial number: %.0lf\n", ljSN);

    // set up PWM
    AddRequest(ljHandle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 1, 0, 0);
    AddRequest(ljHandle, LJ_ioPUT_CONFIG, LJ_chTIMER_COUNTER_PIN_OFFSET, PIN_SERVO, 0, 0);
    AddRequest(ljHandle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc1MHZ_DIV, 0, 0);
    AddRequest(ljHandle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_DIVISOR, 78, 0, 0);
    AddRequest(ljHandle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmPWM8, 0, 0);
    AddRequest(ljHandle, LJ_ioPUT_TIMER_VALUE, 0, SERVO_0, 0, 0);
    Go();

    // Get initial sensor states
    AddRequest(ljHandle, LJ_ioGET_DIGITAL_BIT, PIN_RB_SENS, 0, 0, 0);
    AddRequest(ljHandle, LJ_ioGET_DIGITAL_BIT, PIN_IR_SENS, 0, 0, 0);
    Go();
    GetResult(ljHandle, LJ_ioGET_DIGITAL_BIT, PIN_RB_SENS, &rbSensor);
    GetResult(ljHandle, LJ_ioGET_DIGITAL_BIT, PIN_IR_SENS, &irSensor);

    do {
        if (servoCounter != 0) {
            servoCounter--;
        } else {
            AddRequest(ljHandle, LJ_ioPUT_TIMER_VALUE, 0, SERVO_0, 0, 0);
            Go();
        }

        if (!irSensor && servoCounter == 0) {
            servoCounter = 30;

            AddRequest(ljHandle, LJ_ioPUT_TIMER_VALUE, 0, SERVO_90, 0, 0);
            Go();

            updateHTML(rbSensor);
        }

        if (loopCounter % 10 == 0) {
            printf("The bin lid is currently: %s\n", servoCounter == 0 ? "closed" : "open");
        }

        loopCounter++;
        Sleep(100);

        AddRequest(ljHandle, LJ_ioGET_DIGITAL_BIT, PIN_RB_SENS, 0, 0, 0);
        AddRequest(ljHandle, LJ_ioGET_DIGITAL_BIT, PIN_IR_SENS, 0, 0, 0);
        Go();
        GetResult(ljHandle, LJ_ioGET_DIGITAL_BIT, PIN_RB_SENS, &rbSensor);
        GetResult(ljHandle, LJ_ioGET_DIGITAL_BIT, PIN_IR_SENS, &irSensor);
    } while (rbSensor == 0);

    updateHTML(rbSensor);
    Close();
    return 0;
}

const char* writeTime() {
    time_t curTime;
    time(&curTime);
    return ctime(&curTime);
}


void updateHTML(int wasTipped) {
    //Open a file as usual.
    FILE* fp;
    fopen_s(&fp, "index.html", "w");

    //Check to see if program should end (pass 0s for both arguments if pushbutton pressed in main()). If it should, write to html file the date/time program ended and do not include instruction to refresh page.
    if (wasTipped) {
        fprintf(fp, "<h1>My Epic Lab <s>9</s> 10</h1>\n"
                    "<h2>The garbage bin was tipped over on %s!</h2>\n"
                    "<h3>Program is currently NOT running</h3>", writeTime());
    } else {
        //If button not pressed, write to file the current date/time (use writeTime()) temperature, status of fan (either a range of words or percentage). Include instruction to refresh page every 5 seconds for the user.
        fprintf(fp, "<meta http-equiv=\"refresh\" content=\"5\">\n"
                    "<h1>My Epic Lab <s>9</s> 10</h1>\n"
                    "<h2>Lid was last opened at: %s</h2>", writeTime());
    }

    //Close file.
    fclose(fp);

    //Execute batch file to transfer updated html file to matrix server.
    system("C:\\Users\\Nicholas\\Documents\\Coding\\HSI266_Lab10\\winscript.bat");
}


/* PROGRAM OUTPUT

C:\Users\Nicholas\Documents\Coding\HSI266_Lab10\cmake-build-debug\Lab10.exe
Serial number: 320093113
The bin lid is currently: closed
The bin lid is currently: closed
The bin lid is currently: closed
The bin lid is currently: closed

C:\Users\Nicholas\Documents\Coding\HSI266_Lab10\cmake-build-debug>"C:\Users\Nicholas\AppData\Local\Programs\WinSCP\WinSC
P.com" /script="C:\Users\Nicholas\Documents\Coding\HSI266_Lab10\scpscript.txt"
Searching for host...
Connecting to host...
Authenticating...
Using username "nrosati1".
Authenticating with pre-entered password.
Authenticated.
Starting the session...
Session started.
Active session: [1] nrosati1@matrix.senecapolytechnic.ca
C:\...\index.html         |            0 B |    0.0 KB/s | binary |   0%
C:\...\index.html         |          134 B |    0.0 KB/s | binary | 100%
Upload of file 'lab10.html' was successful, but error occurred while setting the permissions and/or timestamp.
If the problem persists, turn off setting permissions or preserving timestamp. Alternatively you can turn on 'Ignore per
mission errors' option.
Permission denied.
Error code: 3
Error message from server: Permission denied
(A)bort, (R)etry, (S)kip, Ski(p) all: Abort
The bin lid is currently: open
The bin lid is currently: open
The bin lid is currently: open
The bin lid is currently: closed
The bin lid is currently: closed
The bin lid is currently: closed

C:\Users\Nicholas\Documents\Coding\HSI266_Lab10\cmake-build-debug>"C:\Users\Nicholas\AppData\Local\Programs\WinSCP\WinSC
P.com" /script="C:\Users\Nicholas\Documents\Coding\HSI266_Lab10\scpscript.txt"
Searching for host...
Connecting to host...
Authenticating...
Using username "nrosati1".
Authenticating with pre-entered password.
Authenticated.
Starting the session...
Session started.
Active session: [1] nrosati1@matrix.senecapolytechnic.ca
C:\...\index.html         |          148 B |    0.0 KB/s | binary | 100%

Process finished with exit code 0
*/