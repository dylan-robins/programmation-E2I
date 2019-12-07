#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int perfect(const int n);
void find_all_perfects(const int n);
int sum_dividors(const int n);

int main() {
    int n;
    // Read an integer
    printf("Please enter the upper limit for the perfect number search: ");
    if (scanf("%d", &n) == 0) {
        fprintf(stderr, "Error, please enter a valid integer.");
    }
    find_all_perfects(n);
}

int perfect(const int n) {
    // a number is perfect if it's equal to the sum of it's dividors
    int truc = sum_dividors(n);
    return n == truc;
}

void find_all_perfects(const int n) {
    int i;
    printf("List of all perfect numbers in interval [0,%d]:\n", n);
    // loop over all numbers in [0,n] and print those that are perfect
    for (i = 1; i <= n; i++) {
        if (perfect(i)) {
            printf("%d ", i);
        }
    }
    // print trailing newline
    printf("\n");
}

int sum_dividors(const int n) {
    int i;
    int sum = 0;
    // loop over all potential dividors and accumulate them in sum
    for (i = 1; i < n; i++) {
        if (n%i == 0) {
            // i divides n
            sum += i;
        }
    }
    return sum;
}
