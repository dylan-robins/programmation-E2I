#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint32_t rotate5l(uint32_t number) {
    uint8_t lsb5 = (number & 0xF8000000) >> 27;
    number = (number << 5) | lsb5;
    return number;
}

uint32_t hash(const char* str) {
    uint32_t hashed = 0;
    for (int i = 0; i < 4 && i < strlen(str); i++) {
        hashed |= (str[i] << 8*i);
    }
    for (int i = 4; i < strlen(str); i++) {
        hashed = rotate5l(hashed);
        hashed ^= str[i];
    }
    return hashed;
}