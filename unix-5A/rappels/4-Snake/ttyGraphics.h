#ifndef __TTYGRAPHICS__
#define __TTYGRAPHICS__

#include <sys/ioctl.h>

#define clear() printf("\033[H\033[J")
#define gotoxy(x, y) printf("\033[%d;%dH", (y), (x))
#define displayCursor() printf("\033[?25h")
#define hideCursor() printf("\033[?25l")

int kbhit();
struct winsize getTermSize();
void disable_raw_mode();
void enable_raw_mode();
void setRealtimeMode();
void unsetRealtimeMode();

int msleep(long msec);

#endif