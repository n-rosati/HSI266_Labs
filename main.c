#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "C:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

const char* writeTime();
void updateHTML(int wasTipped);

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
                    "<h2>The garbage bin was tipped over at %s!</h2>\n"
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