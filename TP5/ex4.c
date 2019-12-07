#include <stdio.h>
#include <string.h>
#include <ctype.h>

void rot13(char * input, char * output) {
    char c;
    for (int i = 0; i <= strlen(input); i++) {
        c = input[i];
        if (islower(c)) {
            output[i] = 'a' + (c-'a' + 13)%26;
        } else if (isupper(c)) {
            output[i] = 'A' + (c-'A' + 13)%26;
        } else {
            output[i] = c;
        }
        
    }
}

int main() {
    char * bjr = "Bonjour les e2i3 !";
    char encr[20];
    rot13(bjr, encr);
    printf(
        "Entree: %s\n"
        "Sortie: %s\n",
        bjr, encr
    );
    return 0;
}