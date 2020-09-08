#include <iostream>

using namespace std;

typedef struct {
    int N;
    int M;
} dimensions;

// EXERCICE 2

dimensions lire_dimensions() {
    dimensions dim;
    
    cout << "Entrez la valeur de N :" << endl << ">>> ";
    cin >> dim.N;

    cout << "Entrez la valeur de M :" << endl << ">>> ";
    cin >> dim.M;
    
    return dim;
}

int ** allouer_matrice(dimensions taille) {
    // allouer la matrice
    int **matrice = new int*[taille.N];
    for (int i = 0; i < taille.N; i++) {
        matrice[i] = new int[taille.M];
    }
    return matrice;
}

int ** lire_matrice(dimensions taille_matrice) {
    int **matrice = allouer_matrice(taille_matrice);

    cout << "Entrez les valeurs à mettre dans la matrice :" << endl;
    for (int i = 0; i < taille_matrice.N; i++) {
        for (int j = 0; j < taille_matrice.M; j++) {
            cout <<  ">>> ";
            cin >> matrice[i][j];
        }
    }

    return matrice;
}

void detruire_matrice(int ** mat, dimensions taille) {
    for (int i = 0; i < taille.N; i++) {
        delete mat[i];
    }
    delete mat;
}

int ** transposer_matrice(int **matrice_A, dimensions taille) {
    int **matrice_B = allouer_matrice(taille);

    // transposer A dans B
    for (int i = 0; i < taille.N; i++) {
        for (int j = 0; j < taille.M; j++) {
            matrice_B[i][j] = matrice_A[j][i];
        }
    }
    return matrice_B;
}

void afficher_matrice(int **matrice, dimensions taille) {
    for (int i = 0; i < taille.N; i++) {
        for (int j = 0; j < taille.M; j++) {
            cout << matrice[i][j] << " ";
        }
        cout << endl;
    }
}

int * serialiser_matrice(int **matrice, dimensions taille) {
    int *tab = new int[taille.N * taille.M];
    for (int i = 0; i < taille.N; i++) {
        for (int j = 0; j < taille.M; j++) {
            tab[i*taille.M + j] = matrice[i][j];
        }
    }
    return tab;
}

// EXERCICE 3

int ** mult_matrices(int ** A, dimensions dim_A, int ** B, dimensions dim_B) {
    // planter si les dimensions des matrices ne collent pas
    if (dim_A.M != dim_B.N) {
        cout << "Erreur: dimensions des matrices incompatibles" << endl;
        exit(EXIT_FAILURE);
    }

    // allouer la nouvelle matrice
    dimensions dim_C = {dim_A.N, dim_B.M};
    int **C = allouer_matrice(dim_C);

    // effectuer la multiplication
    for (int i = 0; i < dim_C.N; i++) {
        for (int j = 0; j < dim_C.M; j++) {
            C[i][j] = 0;
            for (int k = 0; k < dim_A.M; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

int main(void) {
    // exercice 2
    dimensions dim = lire_dimensions();
    int ** A = lire_matrice(dim);
    cout << "Matrice A :" << endl;
    afficher_matrice(A, dim);

    int ** B = transposer_matrice(A, dim);
    cout << "Matrice B :" << endl;
    afficher_matrice(B, dim);

    int *tab = serialiser_matrice(A, dim);
    cout << "Matrice A sérialisée :" << endl;
    for (int i = 0; i < dim.N*dim.M; i++) {
        cout << tab[i] << " ";
    }
    cout << endl;

    detruire_matrice(A, dim);
    detruire_matrice(B, dim);
    delete tab;

    // exercice 3
    dimensions dim_A = lire_dimensions();
    A = lire_matrice(dim_A);
    cout << "Matrice A :" << endl;
    afficher_matrice(A, dim_A);

    dimensions dim_B = lire_dimensions();
    B = lire_matrice(dim_B);
    cout << "Matrice B :" << endl;
    afficher_matrice(B, dim_B);

    int ** C = mult_matrices(A, dim_A, B, dim_B);
    dimensions dim_C = {dim_A.N, dim_B.M};
    cout << "Matrice C = A*B :" << endl;
    afficher_matrice(C, dim_C);

    detruire_matrice(A, dim_A);
    detruire_matrice(B, dim_B);
    detruire_matrice(C, dim_C);

    return 0;
}