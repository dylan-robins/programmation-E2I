#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* On utilise une liste chainée pour représenter un polynome. Chaque terme
 * est représenté par un élément de la chaine, et comporte 
 *   - un degré (le n de ax^n) (>= 0)
 *   - un coefficient (le a de ax^n) (supposition de l'énoncé: est entier)
 *   - la référence vers le coefficient suivant (NULL si fin de chaine)
 */
typedef struct coeff_s {
    unsigned int degree;
    int coeff;
    struct coeff_s *next;
} term_t;

/* On alias le type pointeur de coeff_t afin de pouvoir passer en argument à
 * des fonctions des polynomes_t directement. Les coeff_t sont la
 * représentation interne, le polynome_t la représentation abstraite.
 */
typedef term_t* polynome_t;

polynome_t creer_terme(int coeff, unsigned int degree) {
    polynome_t P = (polynome_t) malloc(sizeof(term_t));
    P->degree = degree;
    P->coeff = coeff;
    return P;
}

polynome_t creer_polynome(const int coeffs[], size_t nb_coeffs) {
    /* Remplir les données du 1e. Cas géré à part vu que comportement différent
     * pour la tête de liste
     */
    size_t first_term;
    for (first_term = 0; first_term < nb_coeffs && coeffs[first_term] == 0; first_term++) {
        // On saute les éléments potentiellements inutiles au debut de la liste
        continue; 
    }
    polynome_t P = creer_terme(coeffs[first_term], nb_coeffs-1-first_term);

    /* Parcourir la liste des coeffs en créant (si nécessaire) des coeffs en
     * les rajoutant dans la liste
     */
    term_t *courant = P;
    for (size_t i = first_term+1; i < nb_coeffs; i++) {
        if (coeffs[i] != 0) {
            courant->next = creer_terme(coeffs[i], nb_coeffs-1-i);
            courant = courant->next;
        }
    }
    return P;
}

void detruire_polynome(polynome_t P) {
    if (P != NULL) {
        detruire_polynome(P->next);
        free(P);
    }
}

void afficher_polynome(polynome_t P) {
    term_t *courant = P;
    if (P != NULL) {
        printf("%d*x^%d", P->coeff, P->degree);
        courant = courant->next;

        while (courant != NULL) {
            printf("+%d*x^%d", courant->coeff, courant->degree);
            courant = courant->next;
        }
        printf("\n");
    }
}

double calcul_polynome(polynome_t P, double x) {
    term_t *courant = P;
    double total = 0;
    while(courant != NULL) {
        total += courant->coeff * powf(x, courant->degree);
        courant = courant->next;
    }
    return total;
}

int calcul_polynome_rec(polynome_t P, int x) {
    if (P != NULL) {
        return P->coeff*pow(x, P->degree) + calcul_polynome_rec(P->next, x);
    } else {
        return 0;
    }
}

polynome_t deriver_polynome(polynome_t P) {
    // deg(p') = deg(p)-1
    int coeffs[P->degree];
    // Initialiser le tableau à taille variable à 0
    for (size_t i = 0; i < P->degree; i++) {
        coeffs[i] = 0;
    }
    // Calculer les coeffs du polynome dérivé
    for (term_t *courant = P; courant != NULL; courant = courant->next) {
        if (courant->degree != 0) {
            // ax^n => anx^(n-1)
            coeffs[P->degree - courant->degree] = courant->coeff * courant->degree;
        }
    }

    //  créer un polynome à partir de la liste des coeffs et le renvoyer
    return creer_polynome(coeffs, P->degree);
}

polynome_t copier_polynome(polynome_t P) {
    polynome_t Q = NULL;
    term_t *courantP = P;
    term_t *courantQ = NULL;

    if (P != NULL) {
        // Comme pour la creation, gestion du 1e à part
        Q = creer_terme(P->coeff, P->degree);

        courantQ = Q;
        courantP = P->next;

        while (courantP != NULL) {
            courantQ->next = creer_terme(courantP->coeff, courantP->degree);
            
            courantP = courantP->next;
            courantQ = courantQ->next;
        }
    }
    return Q;
}

polynome_t somme_polynomes(polynome_t P, polynome_t Q) {
    polynome_t S;
    unsigned int degree;

    // deg(P+Q) <= max(deg(P), deg(Q))
    if (P != NULL && Q != NULL) {
        degree = (P->degree > Q->degree)?P->degree:Q->degree;
    } else if (P != NULL) {
        degree = P->degree;
    } else if (Q != NULL) {
        degree = Q->degree;
    } else {
        // Les deux polynomes sont nuls
        return NULL;
    }

    // Allouer un tableau pour les coeffs de la somme
    // Initialiser à 0
    int coeffs[degree+1];
    for (size_t i = 0; i < degree+1; i++) {
        coeffs[i] = 0;
    }

    for (term_t *courant = P; courant != NULL; courant = courant->next) {
        coeffs[degree - courant->degree] += courant->coeff;
    }
    for (term_t *courant = Q; courant != NULL; courant = courant->next) {
        coeffs[degree - courant->degree] += courant->coeff;
    }
    S = creer_polynome(coeffs, degree+1);
    return S;
}

polynome_t produit_polynomes(polynome_t P, polynome_t Q) {
    polynome_t S;
    unsigned int degree;

    // deg(P+Q) = deg(P) + deg(Q)
    if (P == NULL || Q == NULL) return NULL;
    else degree = P->degree+Q->degree;

    // Allouer un tableau pour les coeffs de la somme
    // Initialiser à 0
    int coeffs[degree+1];
    for (size_t i = 0; i < degree+1; i++) {
        coeffs[i] = 0;
    }

    for (term_t *courantP = P; courantP != NULL; courantP = courantP->next) {
        for (term_t *courantQ = Q; courantQ != NULL; courantQ = courantQ->next) {
            coeffs[degree - (courantQ->degree + courantP->degree)] += courantQ->coeff * courantP->coeff;
        }
    }
    S = creer_polynome(coeffs, degree+1);
    return S;
}

double racine_particuliere(polynome_t P) {
    double yn, yn1;
    const double precision = 0.000001;
    
    printf("X value to search from:\n>>> ");
    while (scanf("%lf", &yn1) != 1) {
        printf("Please enter a double precision floating point number...\n>>> ");
        while (getchar()) {};
    }
    
    do {
        yn = yn1;
        yn1 = yn - calcul_polynome(P, yn) / calcul_polynome(deriver_polynome(P), yn);
    } while (fabs(yn1-yn) > precision);
    printf("X value found: %f. Value: %f\n", yn1, calcul_polynome(P, yn1));
    return yn1;
    
}

int main(void) {
    const int t1[6] = {1,0,0,4,0,3};
    polynome_t p1 = creer_polynome(t1, 6);
    printf("p1(x) = ");
    afficher_polynome(p1);
    printf("p1(5) = %f\n", calcul_polynome(p1, 5));
    printf("p1(5) = %d\n", calcul_polynome_rec(p1, 5));

    polynome_t p2 = deriver_polynome(p1);
    printf("p1'(x) = ");
    afficher_polynome(p2);

    polynome_t p3 = copier_polynome(p1);
    printf("p3(x) = ");
    afficher_polynome(p3);

    polynome_t p4 = somme_polynomes(p1, p2);
    printf("(p1+p1')(x) = ");
    afficher_polynome(p4);
    polynome_t p5 = somme_polynomes(p1, p3);
    printf("(p1+p3)(x) = ");
    afficher_polynome(p5);

    polynome_t p6 = produit_polynomes(p1, p3);
    printf("(p1*p3)(x) = ");
    afficher_polynome(p6);

    racine_particuliere(p1);

    detruire_polynome(p1);
    detruire_polynome(p2);
    detruire_polynome(p3);
    detruire_polynome(p4);
    detruire_polynome(p5);
    detruire_polynome(p6);
    return 0;
}