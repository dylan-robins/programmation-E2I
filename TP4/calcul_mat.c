#include <stdio.h>

#define MAX_LEN 3

void saisir(int tab[MAX_LEN][MAX_LEN], int len);
void afficher(int tab[MAX_LEN][MAX_LEN], int len);

/**
 *  Les fonctions de manipulation prennent deux matrices en entree et mettent
 * le resultat dans la 1e.
**/
void somme(int A[MAX_LEN][MAX_LEN], int B[MAX_LEN][MAX_LEN], int C[MAX_LEN][MAX_LEN], int len);
/**
 *  Les fonctions de manipulation prennent deux matrices en entree et mettent
 * le resultat dans la 1e.
**/
void mult(int A[MAX_LEN][MAX_LEN], int B[MAX_LEN][MAX_LEN], int C[MAX_LEN][MAX_LEN], int len);

int main() {
    // creer des matrices
    int A[MAX_LEN][MAX_LEN];
    int B[MAX_LEN][MAX_LEN];
    int C[MAX_LEN][MAX_LEN];

    // remplir A
    saisir(A, MAX_LEN);

    printf("Matrice de depart: A=\n");
    afficher(A, MAX_LEN);
    
    // faire l'addition de mat avec elle meme
    printf("Test addition: A+A=B=\n");
    somme(A, A, B, MAX_LEN);
    afficher(B, MAX_LEN);

    // faire la multiplication de mat avec elle meme
    printf("Test multiplication: A*A=C=\n");
    mult(A, A, C, MAX_LEN);
    afficher(C, MAX_LEN);

    return 0;
}

void saisir(int tab[MAX_LEN][MAX_LEN], int len) {
    printf("Veuillez rentrer %d entiers:\n", len*len);
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            printf(">>> ");
            scanf("%d", &(tab[i][j]));
        }
    }

}

void afficher(int tab[MAX_LEN][MAX_LEN], int len) {
    for (int y = 0; y < len; y++) {
        for (int x = 0; x < len; x++) {
            printf("%d\t", tab[y][x]);
        }
        printf("\n");
    }
}

void somme(int A[MAX_LEN][MAX_LEN], int B[MAX_LEN][MAX_LEN], int C[MAX_LEN][MAX_LEN], int len) {
    for (int y = 0; y<len; y++) {
        for (int x = 0; x<len; x++) {
            C[y][x] = A[y][x] + B[y][x];
        }
    }
}

void mult(int A[MAX_LEN][MAX_LEN], int B[MAX_LEN][MAX_LEN], 
          int res[MAX_LEN][MAX_LEN], int len) {
    int combi_lin;
    // pour chaque element de la matrice, calculer sa valeur
    for (int y = 0; y<len; y++) {
        for (int x = 0; x<len; x++) {
            // combinaison lineaire de la ligne de A avec la colonne de B
            combi_lin = 0;
            for (int i = 0; i < len; i++) {
                combi_lin += A[y][i] * B[i][x];
            }
            res[y][x] = combi_lin;
        }
    }
}
