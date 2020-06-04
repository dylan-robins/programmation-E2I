#include <stdio.h>
#include <stdint.h>

#include "hash_table.h"

int main(void) {
    char strings[][20] = {
        "ABCDEF",
        "abcdef",
        "travaux",
        "pratiques",
        "de",
        "programmation",
        "en",
        "langage",
        "C"
    };
    uint32_t table_size = 500;
    for (int i = 0; i < 9; i++) {
        printf("Test sequence: <%s>,\thash = %d\n", strings[i], hash(strings[i]) % table_size);
    }
    return 0;
}