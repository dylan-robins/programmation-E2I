#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// pythonic string struct
typedef struct {
    char *s;
    size_t len;
    size_t capacity;
} string;

string *initString(size_t capacity, size_t len) {
    string *str = (string *) malloc(sizeof(string));
    str->s = (char *) malloc(capacity * sizeof(char));
    str->s[0] = '\0';
    str->capacity = capacity;
    str->len = len;
    return str;
}

void deleteString(string *str) {
    free(str->s);
    free(str);
}

int getLine(string *str, FILE *f) {
    char c = 0;
    while (c != '\n' && !feof(f)) {
        if (str->len >= str->capacity) {
            // If string has maxed out it's capacity, reallocate it with more space
            str->s = realloc(str->s, 1.5*str->capacity);
            if (str->s == NULL) {
                // Error: out of memory
                return 1;
            }
        }
        // get a char from f and put it at the end of s
        c = getc(f);
        str->s[str->len] = c;
        str->len++;
    }
    // strip \n from end of string and make it a proper string.h-compatible string.
    str->len--;
    str->s[str->len] = '\0';
    return 0;
}

void removeSpaces(string *str) {
    for (size_t i = 0; i < str->len; i++) {
        if (isspace(str->s[i])) {
            // shift left everything after the space
            for (size_t j = i; j < str->len-1; j++) {
                str->s[j] = str->s[j+1];
            }
            str->len--;
        }
    }
}

int palindrome(string *str, size_t n) {
    if (n >= str->len/2) {
        // if we got to here then it IS a palindrome
        return 1;
    } else if (str->s[n] != str->s[str->len-n-1]) {
        // if the nth char isn't the same as the len-1-nth char, then it ISN'T a palindrome
        return 0;
    } else {
        // maybe it is? check the next char.
        return palindrome(str, n+1);
    }
}

int main(void) {
    string *buffer = initString(256, 0);
    // read a line, strip all the whitespace from it
    getLine(buffer, stdin);
    removeSpaces(buffer);
    
    printf("__________\nString %s a palindome\n", (palindrome(buffer, 0))?"IS":"ISN'T");

    deleteString(buffer);

    return 0;
}