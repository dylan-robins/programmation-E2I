#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lire_calcul(double* terme1, char* op, double* terme2) {
    // Lire une ligne au clavier
    char lineBuffer[1024];
    int status = -1;

    printf(">>> ");

    if (fgets(lineBuffer, 1024, stdin) != NULL) {
        // Découper la ligne en un calcul
        status = sscanf(lineBuffer, "%lf %c %lf", terme1, op, terme2);
        // res sera égal à 3 si l'extraction s'est bien déroulée:
        // Si ce n'est pas le cas, essayer autre chose
        if (status <= 0) {
            // Si la chaine est égale à quit, sortir proprement
            // Sinon renvoyer -1
            if (strcmp(lineBuffer, "quit\n") == 0) {
                status = 0;
            } else {
                status = -1;
            }
        }
    } // si la lecture a échoué on renvoie le -1 par défaut

    return status;
}

double faire_calcul(double terme1, char op, double terme2) {
    double resultat = 0.0;
    switch (op) {
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
            printf("Erreur: opération inconnue %c\n", op);
            exit(1);
    }
    return resultat;
}

/* Fonction principale */
int main(void) {
    double t1, t2;
    char op;
    int status;

    // Tant qu'on arrive à lire des lignes valides...
    while ((status = lire_calcul(&t1, &op, &t2)) > 0) {
        // Faire le calcul
        double res = faire_calcul(t1, op, t2);
        // Puis l'afficher
        printf("%lf %c %lf = %lf\n", t1, op, t2, res);
    }

    if (status == -1) {
        printf("Erreur fatale: calcul incompréhensible\n");
    }

    return status;
}