#include <stdio.h>

void readAndPrint(void) {
    // read a char
    char c = getchar();
    // if it's the end just return, otherwise read another
    if (c == '.') {
        return;
    } else {
        readAndPrint();
        // once we've reached the end, print each char while moving back down the call stack
        putchar(c);
    }
}

int main(void) {
    readAndPrint();
    // add a newline at the end of the reversed string
    putchar('\n');
    return 0;
}