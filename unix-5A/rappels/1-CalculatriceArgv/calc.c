#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Fonction principale */
int main(int argc, char** argv) {
    // Tout d'abord, vérifier que l'utilisateur a fourni un calcul valide
    if (argc != 4) {
        printf("Erreur: veuillez fournir un calcul valide!\n");
        printf("Exemple: '%s 12 + 5'\n", argv[0]);
        printf("Exemple: '%s 12 \"*\" 5'\n", argv[0]);
        return 1;
    }

    // Parser les arguments: convertir les arguments 1 et 3 en nombres flottants
    // et vérifier que l'opération fournie est un symbole d'1 caractère.
    double terme1 = atof(argv[1]);
    char* operation = argv[2];
    double terme2 = atof(argv[3]);
    if (strlen(operation) != 1) {
        printf("Erreur: opération inconnue %s\n", operation);
        return 1;
    }

    // Calculer le résultat: en fonction de l'opération calculer le résultat différemment
    double resultat = 0.0;
    switch (operation[0]) {
        case '+':
            resultat = terme1 + terme2;
            break;
        case '-':
            resultat = terme1 - terme2;
            break;
        case '*':
            resultat = terme1 * terme2;
            break;
        case '/':
            resultat = terme1 / terme2;
            break;

        default:
            printf("Erreur: opération inconnue %s\n", operation);
            return 1;
            break;
    }

    printf("%f %s %f = %f\n", terme1, operation, terme2, resultat);

    return 0;
}