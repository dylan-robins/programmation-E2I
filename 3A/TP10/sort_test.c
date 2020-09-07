#include <stdbool.h>
#include "sort.h"

int main() {
    list_t *tab = list_from_arr((const int []){5, 10, 2, 9, 1, 79, 2, 8, 1}, 9);
    bubbleSort(tab, true);
    delete(tab);

    tab = list_from_arr((const int []){5, 10, 2, 9, 1, 79, 2, 8, 1}, 9);
    insertionSort(tab, true);
    delete(tab);

    tab = list_from_arr((const int []){5, 10, 2, 9, 1, 79, 2, 8, 1}, 9);
    quickSort(tab, true);
    delete(tab);
    return 0;
}