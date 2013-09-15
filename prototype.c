
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

char *display = "HALFTENTIMEACQUARTERTOTWENTYLFIVEPASTOMAFOUREIGHTWONEGOTENINEATSIXATHREELEVENTWELVENWAKESEVENFIVEUPSLEEPOCLOCK";
char light[10][11];
int force_hour = 0;
int force_minute = 0;

void illuminate(int x, int y, int length) {
    for (int i = 0; i < length; i++) {
        light[y][x] = 1;
        x++;
    }
}

void update(void) {
    memset(light, 0, sizeof(light));

    //illuminate(7, 0, 4); // time
    //illuminate(9, 1, 2); // to
    //illuminate(7, 7, 4); // wake
    //illuminate(9, 8, 2); // up
    //illuminate(0, 9, 5); // sleep
    //illuminate(9, 4, 2); // go
    //illuminate(5, 5, 3); // eat
    //return;

    time_t ts;
    time(&ts);
    struct tm * now;
    now = localtime(&ts);

    //now->tm_hour = force_hour++;
    //now->tm_min = force_minute++;

    //if (force_hour > 23) force_hour = 0;
    //if (force_minute > 59) force_minute = 0;

    if (now->tm_min > 34) {
        // show the time *to* the next hour
        now->tm_hour++;
    }

    switch (now->tm_hour) {

        case 1:
        case 13:
            illuminate(6, 4, 3);
            break;

        case 2:
        case 14:
            illuminate(4, 4, 3);
            break;

        case 3:
        case 15:
            illuminate(1, 6, 5);
            break;

        case 4:
        case 16:
            illuminate(7, 3, 4);
            break;

        case 5:
        case 17:
            illuminate(5, 8, 4);
            break;

        case 6:
        case 18:
            illuminate(8, 5, 3);
            break;

        case 7:
        case 19:
            illuminate(0, 8, 5);
            break;

        case 8:
        case 20:
            illuminate(0, 4, 5);
            break;

        case 9:
        case 21:
            illuminate(2, 5, 4);
            break;

        case 10:
        case 22:
            illuminate(0, 5, 3);
            break;

        case 11:
        case 23:
            illuminate(5, 6, 6);
            break;

        case 12:
        case 0:
            illuminate(0, 7, 6);
            break;

    }

    if (now->tm_min > 4){
        if (now->tm_min < 35) {
            illuminate(0, 3, 4);
        }
        else {
            illuminate(3, 3, 2);
        }
    }

    switch (now->tm_min / 5) {
        case 0: // oclock
            illuminate(5, 9, 6);
            break;

        case 1: // five
        case 11:
            illuminate(7, 2, 4);
            break;

        case 2: // ten
        case 10:
            illuminate(4, 0, 3);
            break;

        case 3: // quarter
        case 9:
            illuminate(0, 1, 1);
            illuminate(2, 1, 7);
            break;

        case 4: // twenty
        case 8:
            illuminate(0, 2, 6);
            break;

        case 5: // twenty five
        case 7:
            illuminate(0, 2, 6);
            illuminate(7, 2, 4);
            break;

        case 6: // half
            illuminate(0, 0, 4);
            break;

    }
}

void draw(void) {

    puts("\e[1;30;30m\e[2J\e[0;0H");

    for (int y = 0; y < 10; y++) {
        putchar(' ');
        for (int x = 0; x < 11; x++) {
            putchar(' ');
            if (light[y][x]) {
                printf("\e[37m");
            }
            else {
                printf("\e[30m");
            }
            putchar(display[(11 * y) + x]);
        }
        putchar('\n');
    }

    puts("\n\e[0m");

}

int main(int argc, char **argv) {

    while (1) {
        update();
        draw();
        sleep(1);
    }

    return 0;
}
