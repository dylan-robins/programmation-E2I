#include "ttyGraphics.h"

#include <errno.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

void enable_raw_mode() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON | ECHO);  // Disable echo as well
    tcsetattr(0, TCSANOW, &term);
}

void disable_raw_mode() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &term);
}

int kbhit() {
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    return byteswaiting > 0;
}

void setRealtimeMode() {
    enable_raw_mode();
    setvbuf(stdout, NULL, _IONBF, 0);
    hideCursor();
}
void unsetRealtimeMode() {
    displayCursor();
    disable_raw_mode();
    putc('\n', stdout);
}

struct winsize getTermSize() {
    struct winsize ws;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
    return ws;
}

int msleep(long msec) {
    struct timespec ts;
    int res;

    if (msec < 0) {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}
