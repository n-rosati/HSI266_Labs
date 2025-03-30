/* Name: Nicholas Rosati
 * Date: 2025-03-26
 * Purpose: The program will read a temperature sensor on AIN0, and automatically adjust the duty cycle of a PWM signal
 *          on FIO4 accordingly. Every second the program will output the current temperature reading and fan speed %
 *          to the terminal. Also every 15 seconds, the program will generate and upload an HTML file to the Seneca
 *          Matrix server containing the temperature and fan speed. When the button on AIN1 is pressed, the program will
 *          stop the fan and upload a new HTML file containing the date and time the program was ended.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

#define MAX_TEMP 27
#define MIN_TEMP 18

double clampDouble(double lower, double upper, double val);
const char* writeTime();
void updateHTML(double temp, double fanSpeed);

int main() {
    LJ_HANDLE ljHandle = 0;
    LJ_ERROR lj_cue = 0;
    double ljSN, btnAIN1pd, temperatureSens, temperature, fanOnPercentAsDecimal = 0, fanOffPercentAsDecimal, outputValue;
    int counter = 0;

    lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &ljHandle);

    if (lj_cue == LJE_DEVICE_ALREADY_OPEN) {
        printf("LabJack in use! Exiting\n");
        return 0;
    }
    if (ljHandle == 0) {
        printf("Invalid LabJack handle received. Exiting\n");
        return 0;
    }

    ePut(ljHandle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);
    eGet(ljHandle, LJ_ioGET_CONFIG, LJ_chSERIAL_NUMBER, &ljSN, 0);
    printf("Serial number: %.0lf\n", ljSN);

    // Timer setup
    AddRequest(ljHandle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 1, 0, 0);
    AddRequest(ljHandle, LJ_ioPUT_CONFIG, LJ_chTIMER_COUNTER_PIN_OFFSET, 4, 0, 0);
    AddRequest(ljHandle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc4MHZ, 0, 0);
    AddRequest(ljHandle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmPWM8, 0, 0);
    AddRequest(ljHandle, LJ_ioPUT_TIMER_VALUE, 0, 65535, 0, 0);
    Go();

    do {
        AddRequest(ljHandle, LJ_ioGET_AIN, 0, 0, 0, 0);
        AddRequest(ljHandle, LJ_ioGET_AIN, 1, 0, 0, 0);
        Go();
        GetResult(ljHandle, LJ_ioGET_AIN, 0, &temperatureSens);
        temperature = temperatureSens * 100;
        GetResult(ljHandle, LJ_ioGET_AIN, 1, &btnAIN1pd);

        if (counter % 10 == 0) {
            fanOnPercentAsDecimal = (temperature - MIN_TEMP) / (MAX_TEMP - MIN_TEMP);
            fanOnPercentAsDecimal = clampDouble(0.0, 1.0, fanOnPercentAsDecimal);
            fanOffPercentAsDecimal = 1.0 - fanOnPercentAsDecimal;
            outputValue = clampDouble(0, 65535, fanOffPercentAsDecimal * 65535);
            AddRequest(ljHandle, LJ_ioPUT_TIMER_VALUE, 0, (int) outputValue, 0, 0);
            Go();
            printf("Temperature: %.1f, Fan status: %.1f%%\n", temperature, fanOnPercentAsDecimal * 100);
        }

        if (counter % 150 == 0) updateHTML(temperature, fanOnPercentAsDecimal * 100);

        counter++;
        Sleep (100);
    } while (btnAIN1pd < 0.5);

    AddRequest(ljHandle, LJ_ioPUT_TIMER_VALUE, 0, 65535, 0, 0);
    Go();
    updateHTML(0, 0);
    Close();
    return 0;
}

/**
 * Clamps a given double value to a given bound
 * @param lower Lower bound
 * @param upper Upper bound
 * @param val Value to clamp
 * @return Clamped value (double)
 */
double clampDouble(double lower, double upper, double val) {
    if (val > upper) {
        return upper;
    }
    if (val < lower) {
        return lower;
    }
    return val;
}

const char* writeTime() {
    time_t curTime;
    time(&curTime);
    return ctime(&curTime);
}

void updateHTML(double temp, double fanSpeed)
{
    //Open a file as usual.
    FILE* fp;
    fopen_s(&fp, "index.html", "w");


    //Check to see if program should end (pass 0s for both arguments if pushbutton pressed in main()). If it should, write to html file the date/time program ended and do not include instruction to refresh page.
    if (temp == 0 && fanSpeed == 0) {
        fprintf(fp, "<h1>My Epic Lab 9</h1>\n"
                    "<h2>Program ended at: %s</h2>", writeTime());
    } else {
        //If button not pressed, write to file the current date/time (use writeTime()) temperature, status of fan (either a range of words or percentage). Include instruction to refresh page every 5 seconds for the user.
        fprintf(fp, "<meta http-equiv=\"refresh\" content=\"5\">\n"
                    "<h1>My Epic Lab 9</h1>\n"
                    "<h2>Time: %s</h2>\n"
                    "<p>Temperature: %.1f\n"
                    "Fan speed (%%): %.1f</p>", writeTime(), temp, fanSpeed);
    }

    //Close file.
    fclose(fp);

    //Execute batch file to transfer updated html file to matrix server.
    system("C:\\Users\\Nicholas\\Documents\\Coding\\HSI266_Lab9\\winscript.bat");
}


/* TERMINAL OUTPUT

➜ .\Lab9.exe
Serial number: 320093113
Temperature: 22.5, Fan status: 49.7%

C:\Users\Nicholas\Documents\Coding\HSI266_Lab9\cmake-build-debug>"C:\Users\Nicholas\AppData\Local\Programs\WinSCP\WinSCP.com" /script="C:\Users\Nicholas\Documents\Coding\HSI266_Lab9\scpscript.txt"
Searching for host...
Connecting to host...
Authenticating...
Using username "nrosati1".
Authenticating with pre-entered password.
Authenticated.
Starting the session...
Session started.
Active session: [1] nrosati1@matrix.senecapolytechnic.ca
C:\...\index.html         |          153 B |    0.0 KB/s | binary | 100%
Upload of file 'index.html' was successful, but error occurred while setting the permissions and/or timestamp.
If the problem persists, turn off setting permissions or preserving timestamp. Alternatively you can turn on 'Ignore permission errors' option.
Permission denied.
Error code: 3
Error message from server: Permission denied
(A)bort, (R)etry, (S)kip, Ski(p) all: Abort
Temperature: 23.5, Fan status: 61.0%
Temperature: 23.5, Fan status: 61.0%
Temperature: 24.0, Fan status: 66.6%
Temperature: 23.5, Fan status: 61.0%
Temperature: 23.5, Fan status: 61.0%
Temperature: 23.5, Fan status: 61.0%
Temperature: 24.0, Fan status: 66.6%
Temperature: 23.5, Fan status: 61.0%
Temperature: 23.5, Fan status: 61.0%
Temperature: 23.5, Fan status: 61.0%
Temperature: 24.0, Fan status: 66.6%
Temperature: 24.0, Fan status: 66.6%
Temperature: 24.0, Fan status: 66.6%
Temperature: 24.0, Fan status: 66.6%
Temperature: 25.5, Fan status: 83.6%

C:\Users\Nicholas\Documents\Coding\HSI266_Lab9\cmake-build-debug>"C:\Users\Nicholas\AppData\Local\Programs\WinSCP\WinSCP.com" /script="C:\Users\Nicholas\Documents\Coding\HSI266_Lab9\scpscript.txt"
Searching for host...
Connecting to host...
Authenticating...
Using username "nrosati1".
Authenticating with pre-entered password.
Authenticated.
Starting the session...
Session started.
Active session: [1] nrosati1@matrix.senecapolytechnic.ca
C:\...\index.html         |          153 B |    0.0 KB/s | binary | 100%
Temperature: 27.6, Fan status: 100.0%
Temperature: 28.1, Fan status: 100.0%
Temperature: 28.6, Fan status: 100.0%
Temperature: 29.1, Fan status: 100.0%
Temperature: 29.6, Fan status: 100.0%
Temperature: 29.1, Fan status: 100.0%
Temperature: 28.6, Fan status: 100.0%
Temperature: 28.1, Fan status: 100.0%
Temperature: 27.0, Fan status: 100.0%
Temperature: 27.0, Fan status: 100.0%
Temperature: 27.0, Fan status: 100.0%
Temperature: 27.0, Fan status: 100.0%
Temperature: 27.0, Fan status: 100.0%
Temperature: 27.0, Fan status: 100.0%
Temperature: 26.5, Fan status: 94.9%

C:\Users\Nicholas\Documents\Coding\HSI266_Lab9\cmake-build-debug>"C:\Users\Nicholas\AppData\Local\Programs\WinSCP\WinSCP.com" /script="C:\Users\Nicholas\Documents\Coding\HSI266_Lab9\scpscript.txt"
Searching for host...
Connecting to host...
Authenticating...
Using username "nrosati1".
Authenticating with pre-entered password.
Authenticated.
Starting the session...
Session started.
Active session: [1] nrosati1@matrix.senecapolytechnic.ca
C:\...\index.html         |          153 B |    0.0 KB/s | binary | 100%
Temperature: 26.0, Fan status: 89.2%
Temperature: 26.0, Fan status: 89.2%
Temperature: 25.5, Fan status: 83.6%
Temperature: 25.5, Fan status: 83.6%
Temperature: 25.5, Fan status: 83.6%
Temperature: 25.0, Fan status: 77.9%
Temperature: 25.5, Fan status: 83.6%
Temperature: 25.5, Fan status: 83.6%
Temperature: 25.5, Fan status: 83.6%
Temperature: 25.0, Fan status: 77.9%
Temperature: 25.0, Fan status: 77.9%
Temperature: 25.0, Fan status: 77.9%
Temperature: 25.0, Fan status: 77.9%

C:\Users\Nicholas\Documents\Coding\HSI266_Lab9\cmake-build-debug>"C:\Users\Nicholas\AppData\Local\Programs\WinSCP\WinSCP.com" /script="C:\Users\Nicholas\Documents\Coding\HSI266_Lab9\scpscript.txt"
Searching for host...
Connecting to host...
Authenticating...
Using username "nrosati1".
Authenticating with pre-entered password.
Authenticated.
Starting the session...
Session started.
Active session: [1] nrosati1@matrix.senecapolytechnic.ca
C:\...\index.html         |           77 B |    0.0 KB/s | binary | 100%
*/