#include <stdio.h>
#include <math.h>

int sum_dividors(const int n);
int are_amicable(const int a, const int b);

int main() {
    int n, a, b;
    // Read the reference air pressure
    printf("Please enter the upper limit of the range of numbers to test: ");
    if (scanf("%d", &n) == 0) {
        fprintf(stderr, "Error, please enter a valid integer.");
    }
    
    for (a = 1; a < n; a++) {
        for (b = a+1; b < n; b++) {
            if (are_amicable(a,b)) {
                printf("(%d, %d)\n", a, b);
            }
        }
    }

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

int are_amicable(const int a, const int b) {
    return (sum_dividors(a) == b && sum_dividors(b) == a);
}
