#include <stdio.h>
#include <string.h>

int main(void) {
    //unsigned indice;
    int indice;
    // On change ça en un signed int afin que la condition >= ait du sens.
    // En unsigned, 0-- donne 4 millions et quelques, ce qui est forcément > 0
    char Titre[] = "TP de Programmation des e2i3 numero 5";
    char TitreEnvers[38];
    printf("La chaine %s a pour taille : %zu\n", Titre, strlen(Titre));
    for (indice = strlen(Titre) - 1; indice >= 0; indice--) {
        TitreEnvers[strlen(Titre) - 1 - indice] = Titre[indice];
    }
    printf("%s\n", TitreEnvers);
    return 0;
}