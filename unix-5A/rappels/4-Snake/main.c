#include <stdio.h>
#include <unistd.h>

#include "map.h"
#include "ttyGraphics.h"

direction getKey() {
    char firstchar = getc(stdin);
    if (firstchar == '\033') {  // if the first value is esc
        getc(stdin);            // skip the [
        switch (getc(stdin)) {  // the real value
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

    while (1) {
        moveSnake(&s);
        drawMap(m, s);
        //printSnake(s);

        if (kbhit()) {
            nextDirection = getKey();
            if (nextDirection == NONE) break;
            s.heading = nextDirection;
        }
        msleep(200);
    }

    unsetRealtimeMode();

    deleteMap(m);
    deleteSnake(s);
    return 0;
}