#include <stdio.h>

int fact_1(int n);
void fact_2(int n, int *res);
void fact_3(int *n);

int main() {
    int n;
    int a, b, c;

    printf("Enter an integer:\n");
    scanf("%d", &n);
    printf("Calculating %d!...\n", n);

    a = n;
    b = n;
    c = n;

    a = fact_1(n);
    printf("Result from fact_1: %d\n", a);

    fact_2(n, &b);
    printf("Result from fact_2: %d\n", b);

    fact_3(&c);
    printf("Result from fact_3: %d\n", c);
    return 0;
}


int fact_1(int n) {
    int fact_n = 1;
    for (int i = 1; i <= n; i++) {
        fact_n *= i;
    }
    return fact_n;
}
void fact_2(int n, int *res) {
    *res = 1;
    for (int i = 1; i <= n; i++) {
        *res *= i;
    }
}
void fact_3(int *n) {
    for (int i = *n-1; i > 0; i--) {
        *n *= i;
    }
}
