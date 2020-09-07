#include <stdio.h>

#define MAX_SIZE 1025

int fibo_n(int n);

int main() {
    int rg_max;
    int suite[MAX_SIZE];
    int somme[MAX_SIZE] = {0};
    double rapports[MAX_SIZE];

    printf("Rang maximal a calculer?\n>>> ");
    scanf("%d", &rg_max);

    for (int i = 0; i < rg_max; i++) {
        suite[i] = fibo_n(i);
        for (int j = 0; j <= i; j++) {
            somme[i] += suite[j];
        }
        if (i > 0) rapports[i] = (double) suite[i] / suite[i-1];
    }

    printf("Fibonacci sequence:\n");
    for (int i = 0; i < rg_max; i++) {
        printf("%d ", suite[i]);
    }
    printf("\n");

    printf("\nSums of the elements:\n");
    for (int i = 0; i < rg_max; i++) {
        printf("%d ", somme[i]);
    }
    printf("\n");
    
    printf("\nSums of the ratios:\n");
    for (int i = 0; i < rg_max; i++) {
        printf("%.3f ", rapports[i]);
    }
    printf("\n");
    
    return 0;
}

int fibo_n(int n) {
    // u_0 = 1
    int u_i2 = 1;
    // u_1 = 1
    int u_i1 = 1;
    // u_i reste a calculer
    int u_i;

    switch (n) {
        case 0:
            return 1;
        case 1:
            return 1;
        default:
            for (int i = 2; i <= n; i++) {
                u_i = u_i1 + u_i2;
                // passer au terme suivant: decaler les indices
                u_i2 = u_i1;
                u_i1 = u_i;
            }
            return u_i;
    }
}
