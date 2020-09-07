#include <stdio.h>

#define MAX_LEN 14

void saisir(int tab[], int len);
void affiche_2D(int tab[], int len, int h);


int main() {
    int h;
    int tab[MAX_LEN];
    
    // remplir le tableau
    saisir(tab, MAX_LEN);

    // demander le nombre de lignes h
    printf("Combien de lignes voulez-vous?\n>>> ");
    scanf("%d", &h);

    // afficher le tableau en 2D
    affiche_2D(tab, MAX_LEN, h);

    return 0;
}

void saisir(int tab[], int len) {
    int i = 0;

    printf("Veuillez rentrer %d entiers:\n", len);

    while (i < len) {
        printf(">>> ");
        scanf("%d", &(tab[i]));
        i++;
    }
}
void affiche_2D(int tab[], int len, int h) {
    for (int i = 0; i < h; i++) {
        for (int j = i; j< len; j+=h) {
            printf("%d\t", tab[j]);
        }
        printf("\n");
    }
}
