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
    for (int i = 0; i < 9; i++) {
        printf("Test sequence: <%s>,\thash = %d\n", strings[i], hash(strings[i], 500));
    }

    hash_table *table = new_hash_table(500);
    set(table, "toto", 0);
    set(table, "meaning of life", 69);
    set(table, "meaning of life", 42);
    printf("toto: %d; meaning of life: %d\n", search(table, "toto"), search(table, "meaning of life"));
    delete(table, "toto");
    delete_hash_table(table);

    return 0;
}