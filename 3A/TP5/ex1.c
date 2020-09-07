#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t myLen(char * string) {
    int i = 0;
    char c = string[0];
    while (c != '\0') {
        i++;
        c = string[i];
    }
    return i;
}

void inverseChaine(char * string) {
    size_t len = strlen(string);
    for (int i = 0; i <= (len-1)/2; i++) {
        char c = string[len-1-i];
        string[len-1-i] = string[i];
        string[i] = c;
    }
}

int palindrome(char * string) {
    char * rev = (char *) malloc(strlen(string)*sizeof(char));
    strcpy(rev, string);
    inverseChaine(rev);
    int is_palindrome = strcmp(string, rev) == 0;
    free(rev);
    return is_palindrome;
}

int main() {
    char * c1 = "Bonjour!";
    printf(
        "strlen(%s): %ld\n"
        "myLen(%s):  %ld\n",
        c1, strlen(c1),
        c1, myLen(c1)
    );

    char c2[10];
    strncpy(c2, c1, 10);
    inverseChaine(c2);
    printf(
        "Chaine de base:  <%s>\n"
        "Chaine inversée: <%s>\n",
        c1, c2
    );

    char * c3 = "kayak";
    strncpy(c2, c3, 10);
    inverseChaine(c2);
    printf(
        "Chaine de base:  <%s>\n"
        "Chaine inversée: <%s>\n",
        c3, c2
    );

    printf(
        "<%s> est un palindrome: %d\n"
        "<%s> est un palindrome: %d\n",
        c1, palindrome(c1),
        c3, palindrome(c3)
    );
    return 0;
}