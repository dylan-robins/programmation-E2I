#include <stdio.h>
#include <unistd.h>

#include "map.h"
#include "ttyGraphics.h"

direction getKey() {
    char firstchar = getc(stdin);
    if (firstchar == '\033') { // if the first value is esc
        getc(stdin);           // skip the [
        switch (getc(stdin)) { // the real value
        case 'A':
            // code for arrow up
            return NORTH;
        case 'B':
            // code for arrow down
            return SOUTH;
        case 'C':
            // code for arrow right
            return EAST;
        case 'D':
            // code for arrow left
            return WEST;
        default:
            // else return nothing
            return NONE;
        }
    } else {
        return NONE;
    }
}

int main() {
    struct winsize ws = getTermSize();
    map m = newMap(ws.ws_col, ws.ws_row);
    snake s = newSnake(ws.ws_col / 2, ws.ws_row / 2);

    setRealtimeMode();

    direction nextDirection;
    int status = 0;
    int exitFlag = 0;

    while (!exitFlag) {
        moveSnake(&s);
        status = checkCollision(s, m);

        switch (status) {
        case 1:
            lengthenSnake(&s);
            break;
        case -1:
            exitFlag = 1;
            break;
        default:
            if (kbhit()) {
                nextDirection = getKey();
                if (nextDirection == NONE)
                    break;
                s.heading = nextDirection;
            }
            drawMap(m, s);
            msleep(150);

            break;
        }
    }

    unsetRealtimeMode();

    deleteMap(m);
    deleteSnake(s);
    return 0;
}