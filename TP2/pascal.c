#include <stdio.h>
#include <math.h>

void pascal(const int n);
double cpq(const int p, const int q);
double fact(const int n);

int main() {
    int n;
    // Read the reference air pressure
    printf("Please enter the number f rows to generate: ");
    if (scanf("%d", &n) == 0) {
        fprintf(stderr, "Error, please enter a valid integer.");
    }
    pascal(n);
}

void pascal(const int n) {
    int i, j;
    for (j = 0; j < n; j++) {
        for (i = 0; i < j+1; i++) {
            printf("%4.0f ", cpq(j, i));
        }
        printf("\n");
    }
}

double cpq(const int p, const int q) {
    return fact(p)/(fact(q)*fact(p-q));
}

double fact(const int n) {
    if (n==0) {
        return 1;
    } else {
        return n*fact(n-1);
    }
}
