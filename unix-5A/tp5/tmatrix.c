/********************************************************
 * Programme de multiplication de matrices
 * (version sans processus léger)
 * (Matrice_A X Matrice_B) => Matrice_C
 ********************************************************/
#include <stdio.h>
#include <pthread.h>

#define TAILLE_TABLEAU 300
typedef int matrice_t[TAILLE_TABLEAU][TAILLE_TABLEAU];

pthread_mutex_t lock_A = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_B = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_C = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    pthread_t tid;           /*Identifiant du processus en cours*/
    int id;                  /*Numéro du processus en cours*/
    int taille;              /*Taille de la matrice*/
    int ligneA;              /*Ligne courante de la matrice A*/
    int colonneB;            /*Colonne courante de la matrice B*/
    matrice_t *MA, *MB, *MC; /*Pointeurs sur les matrices*/
} info_t;

/* Fonction effectuant la multiplication d’un ligne et d’une colonne pour placer
 * le resultat dans l’element de la matrice resultante
 */
void multiplication(int taille, int ligne, int colonne, matrice_t MA, matrice_t MB, matrice_t MC) {
    int position;
    MC[ligne][colonne] = 0;
    for (position = 0; position < taille; position++) {
        MC[ligne][colonne] += (MA[ligne][position] * MB[position][colonne]);
    }
}

void * multiplication_thread(void *arg) {
    info_t *info = arg;
    matrice_t *MA = info->MA;
    matrice_t *MB = info->MB;
    matrice_t *MC = info->MC;

    int coeff = 0;

    // Matrices MA et MB sont immutables: pas besoin de mutex
    for (int position = 0; position < TAILLE_TABLEAU; position++) {
        pthread_mutex_lock(&lock_A);
        int cA = (*MA)[info->ligneA][position];
        pthread_mutex_unlock(&lock_A);

        pthread_mutex_lock(&lock_B);
        int cB = (*MB)[position][info->colonneB];
        pthread_mutex_unlock(&lock_B);
        coeff += (cA * cB);
    }


    pthread_mutex_lock(&lock_C);
    (*MC)[info->ligneA][info->colonneB] = coeff;
    pthread_mutex_unlock(&lock_C);

    return NULL;
}

void disp_matrix_info(matrice_t M) {
    printf("Size: %d x %d", TAILLE_TABLEAU, TAILLE_TABLEAU);
    printf("= %ld bytes\n", TAILLE_TABLEAU*TAILLE_TABLEAU*sizeof(int));
}

void disp_matrix(matrice_t M) {
    for (size_t ligne = 0; ligne < TAILLE_TABLEAU; ligne++) {
        for (size_t colonne = 0; colonne < TAILLE_TABLEAU; colonne++) {
            printf("%5d ", M[ligne][colonne]);
        }
        printf("\n");
    }
}

int main(void) {
    /*Initialisation des matrices MA et MB*/

    // MA = 1
    matrice_t MA;
    for (size_t ligne = 0; ligne < TAILLE_TABLEAU; ligne++) {
        for (size_t colonne = 0; colonne < TAILLE_TABLEAU; colonne++) {
            MA[ligne][colonne] = 1;
        }
    }
    matrice_t MB;
    // MB = diag(3)
    for (size_t ligne = 0; ligne < TAILLE_TABLEAU; ligne++) {
        for (size_t colonne = 0; colonne < TAILLE_TABLEAU; colonne++) {
            if (ligne == colonne) 
                MB[ligne][colonne] = 2;
            else
                MB[ligne][colonne] = 0;
        }
    }
    matrice_t MC;

    printf("MATRICE: resultat de la matrice A;\n");
    disp_matrix_info(MA);
    printf("MATRICE: resultat de la matrice B;\n");
    disp_matrix_info(MB);


    /*Calcul de la matrice resultante*/
    info_t tid[TAILLE_TABLEAU*TAILLE_TABLEAU];

    for (size_t ligne = 0; ligne < TAILLE_TABLEAU; ligne++) {
        for (size_t colonne = 0; colonne < TAILLE_TABLEAU; colonne++) {
            // multiplication(TAILLE_TABLEAU, ligne, colonne, MA, MB, MC);
            int id = ligne*TAILLE_TABLEAU+colonne;
            tid[id].id = id;
            tid[id].ligneA = ligne;
            tid[id].colonneB = colonne;
            tid[id].taille = TAILLE_TABLEAU;
            tid[id].MA = &MA;
            tid[id].MB = &MB;
            tid[id].MC = &MC;
            pthread_create(&(tid[id].tid), NULL, multiplication_thread, &(tid[id]));
        }
    }
    for (int id = 0; id < TAILLE_TABLEAU*TAILLE_TABLEAU; id++) {
        pthread_join(tid[id].tid, NULL);
    }

    /*Affichage du resultat*/
    printf("MATRICE: resultat de la matrice C;\n");
    disp_matrix_info(MC);
    return 0;
}