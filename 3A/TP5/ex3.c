#include <stdio.h>
#include <math.h>

typedef struct
{
    double x;
    double y;
} cmplx;

double p_re(cmplx z) {
    return z.x;
}

double p_im(cmplx z) {
    return z.y;
}

void affiche_cmplx(cmplx z) {
    printf("%.2f+%.2fi\n", p_re(z), p_im(z));
}

cmplx somme_cmplx (cmplx z1, cmplx z2) {
    cmplx somme;
    somme.x = z1.x + z2.x;
    somme.y = z1.y + z2.y;
    return somme;
}

cmplx produit_cmplx (cmplx z1, cmplx z2) {
    cmplx prod;
    prod.x = z1.x*z2.x - z1.y*z2.y;
    prod.y = z1.x*z2.y + z1.y*z2.x;
    return prod;
}

double module_cmplx (cmplx z) {
    return sqrt(z.x*z.x + z.y*z.y);
}

int main() {
    cmplx z1 = {1,0};
    cmplx z2 = {0,1};
    cmplx z3 = {1,1};
    cmplx z4 = {-1, -1};
    cmplx z5 = {15,1};

    printf("z1 = ");
    affiche_cmplx(z1);
    printf("z2 = ");
    affiche_cmplx(z2);
    printf("z3 = ");
    affiche_cmplx(z3);
    printf("z4 = ");
    affiche_cmplx(z4);
    printf("z5 = ");
    affiche_cmplx(z5);

    printf("--------------------\n");

    printf("z1 + z2 = ");
    affiche_cmplx(somme_cmplx(z1, z2));

    printf("z1 * z2 = ");
    affiche_cmplx(produit_cmplx(z1, z2));

    printf("|z1| = %.2f\n", module_cmplx(z1));
    
    printf("--------------------\n");

    printf("z2 + z3 = ");
    affiche_cmplx(somme_cmplx(z2, z3));

    printf("z2 * z3 = ");
    affiche_cmplx(produit_cmplx(z2, z3));

    printf("|z2| = %.2f\n", module_cmplx(z2));
    
    printf("--------------------\n");
    
    printf("z3 + z4 = ");
    affiche_cmplx(somme_cmplx(z3, z4));

    printf("z3 * z4 = ");
    affiche_cmplx(produit_cmplx(z3, z4));

    printf("|z3| = %.2f\n", module_cmplx(z3));
    
    printf("--------------------\n");
    
    printf("z4 + z5 = ");
    affiche_cmplx(somme_cmplx(z4, z5));

    printf("z4 * z5 = ");
    affiche_cmplx(produit_cmplx(z4, z5));

    printf("|z4| = %.2f\n", module_cmplx(z4));
    printf("|z5| = %.2f\n", module_cmplx(z5));
    
    return 0;
}
