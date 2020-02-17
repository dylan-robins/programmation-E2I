#include <stdio.h>

void readAndPrint(void) {
    char c = getchar();
    if (c == '.') {
        return;
    } else {
        readAndPrint();
        putchar(c);
    }
}

int main(void) {
    readAndPrint();
    putchar('\n');
    return 0;
}