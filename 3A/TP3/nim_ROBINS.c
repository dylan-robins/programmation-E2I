/*
 * Filename: nim_ROBINS.c
 * Path: /mnt/usb/uni/e2i/prog/TP3
 * Last Modified Date: Monday, November 4th 2019, 8:06:59 pm
 * Author: Dylan ROBINS
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Initialise les paramètres du jeu selon les valeurs fournies par l'utilisateur
void initialiser(int *nbCa, int *jo);
// Fait jouer l'utilisateur
int utilisateur_joue(int nbCa);
// Fait jouer la machine
int machine_joue(int nbCa);

int main() {
    // initialiser nos variables d'etat
    int nb_cailloux = 0;
    int joueur_courant;
    // initialiser le rng
    srand(time(NULL));

    // Demander a l'utilisateur le nombre initial de cailloux et le joueur qui commence
    initialiser(&nb_cailloux, &joueur_courant);

    // BOUCLE PRINCIPALE
    while (nb_cailloux > 0) {
        // afficher un entete
        printf("__________\n");
        printf("Il reste %d cailloux.\n", nb_cailloux);
        printf("Tour de l'%s\n", joueur_courant==1?"utilisateur":"ordinateur");
        
        // faire jouer le bon joueur et passer au suivant
        if (joueur_courant == 1) {
            // tour du joueur
            nb_cailloux = utilisateur_joue(nb_cailloux);
            joueur_courant = 2;
        } else {
            // tour de l'ordinateur
            nb_cailloux = machine_joue(nb_cailloux);
            joueur_courant = 1;
        }
    }

    // affichage du gagnant
    printf("__________\n\n\n");
    if (joueur_courant == 1) {
        // L'utilisateur a gagne

        // C'est pas parce qu'on est en cours qu'on ne peut pas s'amuser un tout petit peu :)
        char * trophy = "  ___________\n"
                        " '._==_==_=_.'\n"
                        " .-\\:      /-.\n"
                        "| (|:.     |) |\n"
                        " '-|:.     |-'\n"
                        "   \\::.    /\n"
                        "    '::. .'\n"
                        "      ) (\n"
                        "    _.' '._\n"
                        "   `\"\"\"\"\"\"\"`";
        printf("%s\n", trophy);
        printf("Felicitations, vous avez gagne!\n");
    } else {
        // La machine a gagne: l'utilisateur a donc perdu.
        printf("Vous avez perdu...\n");
    }
    return 0;
}

// Demande le nombre de cailloux et le numero du joueur qui commence (1=user, 2=ordi)
void initialiser(int *nbCa, int *jo) {
    char c;

    // demander a l'utilisateur le nombre de cailloux
    printf("Entrez le nombre de cailloux: (nombre entier > 0)\n>>> ");
    scanf("%d", nbCa);
    // verifier que l'entree etait valide
    while (*nbCa <= 0){
        // vider le buffer stdin avant de reprompter
        // (evite d'afficher plusieurs fois le message d'erreur)
        while ((c = getchar()) != '\n' && c != EOF);

        // redemander une entree
        printf("Entree invalide!\n");
        printf("Entrez le nombre de cailloux: (nombre entier > 0)\n>>> ");
        scanf("%d", nbCa);
    }
    // vider le buffer stdin avant de continuer
    while ((c = getchar()) != '\n' && c != EOF);

    // demander le numero du joueur qui commence
    printf("Entrez le numero du joueur qui commence: (1=user, 2=ordi)\n>>> ");
    scanf("%d", jo);
    while (*jo != 1 && *jo != 2) {
        // vider le buffer stdin avant de reprompter
        while ((c = getchar()) != '\n' && c != EOF);
        // redemander une entree
        printf("Entree invalide!\n");
        printf("Entrez le numero du joueur qui commence: (1=user, 2=ordi)\n>>> ");
        scanf("%d", jo);
    }
    // vider le buffer stdin avant de continuer
    while ((c = getchar()) != '\n' && c != EOF);
}

int utilisateur_joue(int nbCa) {
    char c;
    int nb_cailloux_pris;

    // demander le nombre de cailloux a retirer de la pile
    printf("Entrez le nombre de cailloux a retirer de la pile: (1, 2 ou 3)\n>>> ");
    scanf("%d", &nb_cailloux_pris);
    // verifier que la valeur fournie est valide
    while (nb_cailloux_pris < 1 || nb_cailloux_pris > 3 || nb_cailloux_pris > nbCa) {
        // vider le buffer stdin avant de reprompter
        while ((c = getchar()) != '\n' && c != EOF);
        // redemander une entree
        printf("Entree invalide!\n");
        printf("Entrez le nombre de cailloux a retirer de la pile: (1, 2 ou 3)\n>>> ");
        scanf("%d", &nb_cailloux_pris);
    }
    // vider le buffer stdin avant de continuer
    while ((c = getchar()) != '\n' && c != EOF);

    // renvoyer le nombre restant de cailloux
    return nbCa - nb_cailloux_pris;
}

int machine_joue(int nbCa) {
    int nb_cailloux_pris;
    switch (nbCa % 4) {
        case 0:
            // il y a un nombre de cailloux multiple de 4
            // si on en enleve 3, on tombe sur un multiple de 4 + 1
            nb_cailloux_pris = 3;
            break;
        case 1:
            // il y a un nombre de cailloux multiple de 4 + 1
            // quoi qu'on fasse, on ne tombera pas sur un multiple de 4 + 1
            // on choisit un nombre entre 1 et 3 au hasard
            nb_cailloux_pris = rand()%3 + 1;
            break;
        case 2:
            // il y a un nombre de cailloux multiple de 4 + 2
            // si on en enleve 1, on tombe sur un multiple de 4 + 1
            nb_cailloux_pris = 1;
            break;
        case 3:
            // il y a un nombre de cailloux multiple de 4 + 3
            // si on en enleve 2, on tombe sur un multiple de 4 + 1
            nb_cailloux_pris = 2;
            break;
    }
    printf("L'ordinateur retire %d cailloux de la pile.\n", nb_cailloux_pris);
    // renvoyer le nombre restant de cailloux
    return nbCa - nb_cailloux_pris;
}
