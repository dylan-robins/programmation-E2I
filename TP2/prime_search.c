#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int prime(const int n);
void find_all_primes(const int n);

int main() {
    int n;
    // Read an integer
    printf("Please enter the upper limit for the prime number search: ");
    if (scanf("%d", &n) == 0) {
        fprintf(stderr, "Error, please enter a valid integer.");
    }
    find_all_primes(n);
}

int prime(const int n) {
    int i;
    for (i = 2; i <= sqrt(n); i++) {
        if (n%i == 0) {
            // if n is divisible by any number from 2 to sqrt(n), then it isn't prime
            return 0;
        }
    }
    // if n isn't divisible by anything, then it's a prime!
    return 1;
}

void find_all_primes(const int n) {
    int i;
    printf("List of all primes in interval [0,%d]:\n", n);
    // loop over all numbers in [0,n] and print those that are prime
    for (i = 1; i <= n; i++) {
        if (prime(i)) {
            printf("%d ", i);
        }
    }
    // print trailing newline
    printf("\n");
}
