#include <stdio.h>
#include <math.h>

#define PRECISION 0.00001

void saisir(float *a, float *b, float *c);
float calcul_discriminant(float a, float b, float c);
int resoudre(float a, float b, float c, float *x1, float *x2);


int main() {
    float a, b, c, x1, x2;

    saisir(&a, &b, &c);
    printf("Finding roots of %fx^2+%fx+%f...\n", a, b, c);
    
    switch (resoudre(a, b, c, &x1, &x2)) {
        case 0:
            printf("No solutions found.\n");
            break;
        case 1:
            printf("One solution found: %f\n", x1);
            break;
        case 2:
            printf("Two solutions found: %f and %f\n", x1, x2);
            break;
        case 3:
            printf("Provided fonction is null.\n");
            break;
        default:
            fprintf(stderr, "Unknown error\n");
            return 1;
    }

    return 0;
}


void saisir(float *a, float *b, float *c) {
    printf("Enter a, b and c for f(x) = ax^2+bx+c...:\n");
    printf("a= ");
    scanf("%f", a);
    printf("b= ");
    scanf("%f", b);
    printf("c= ");
    scanf("%f", c);
}

float calcul_discriminant(float a, float b, float c) {
    return b*b-4*a*c;
}

int resoudre(float a, float b, float c, float *x1, float *x2) {
    if (a == 0 && b == 0) {
        // degre 0: fonction constante
        if (c == 0) return 3; // constante = 0  => solutions = R
        else return 0;      // constante != 0 => pas de col
    } else if (a == 0) {
        // degre 1: fonction affine
        *x1 = -c/b;
        return 1;
    } else {
        // degre 3 => on calcule delta et on regarde les differents cas
        float delta = calcul_discriminant(a, b, c);
        // comparaison des floats avec 0 => c'est le bordel
        if (delta < -PRECISION) {
            // delta < 0 => pas de sol
            return 0;
        } else if (delta > PRECISION) {
            // delta > 0 => 2 sols
            *x1 = (-b-sqrt(delta))/(2*a);
            *x2 = (-b+sqrt(delta))/(2*a);
            return 2;
        } else {
            // delta == 0 => 1 sol
            *x1 = -b/(2*a);
            return 1;
        }
    }
}
