#include <stdio.h>

int main() {
    printf("Starting echo_dollar!\n");
    char c = getc(stdin);
    while (c != '$'){
        putc(c, stdout);
        c = getc(stdin);
    }
    putc('\n', stdout);
}