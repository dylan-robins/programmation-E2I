#include <stdio.h>

void permutation1(int a, int b);
void permutation2(int* a, int* b);

int main() {
    int a, b;

    printf("Enter 2 integers:\n");
    scanf("%d", &a);
    scanf("%d", &b);
    printf("Initial state: a = %d, b = %d\n", a, b);

    permutation1(a, b);
    printf("After permutation1: a = %d, b = %d\n", a, b);
    permutation2(&a, &b);
    printf("After permutation2: a = %d, b = %d\n", a, b);
    return 0;
}


void permutation1(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void permutation2(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
