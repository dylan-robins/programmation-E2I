#include <stdio.h>

void display(int tab[], size_t n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", tab[i]);
    }
    printf("]\n");
}

void bubbleSort(int tab[], size_t n) {
    int tmp;
    int sorted = 0;
    int iteration = 0;

    printf("Initial list:");
    display(tab, n);
    
    while (!sorted) {
        printf("    Iteration %d: ", iteration);
        display(tab, n);

        sorted = 1; // stays 1 if we loop right through without moving anything
        for (int i = 1; i < n-iteration; i++) {
            if (tab[i-1] > tab[i]) {
                printf("        Swapping %d and %d: ", tab[i], tab[i-1]);
                tmp = tab[i];
                tab[i] = tab[i-1];
                tab[i-1] = tmp;
                display(tab, n);
                sorted = 0;
            }
        }
        iteration++;
    }
    
    printf("\nSorted list:");
    display(tab, n);
}

int main() {
    int tab[] = {5, 10, 2, 9, 1, 79, 2, 8, 1};
    bubbleSort(tab, 9);
    return 0;
}