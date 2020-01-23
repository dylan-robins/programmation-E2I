#include <stdio.h>  /* Fonctions d'entrée/sortie */
#include <stdlib.h> /* Fonctions utiles en tout genre */
#include <time.h>   /* Sert à générer des nombres aléatoires à chaque lancement du programme */
#include <math.h>

#include "joueur.h"

/*
    Fonction principale, exécutée au lancement du programme.
    Paramètres :
        - argc : le nombre d'arguments fournis au programme
        - argv : le tableau des arguments sous la forme de chaines de caractères

    Valer de renvoi : code d'erreur du programme (0 = succes)
*/
int main(int argc, char *argv[]) {
    /* Définition des variables locales */
    int nb_joueurs; /* Nombre de joueurs participant */
    joueur *joueurs; /* Tableau contenant les données des joueurs */
    int fini = 0; /* Flag qui passera à 1 une fois que le jeu est terminé */
    int cible; /* Nombre aléatoire qui changera à chaque tour de table */
    int gagnant; /* Numéro du joueur qui a gagné le tour courant */
    int perdant; /* Numéro du joueur qui a perdu */

    /*
        Si on a pas le bon nombre d'arguments, afficher un message d'aide et
        quitter en donnant le code d'erreur 1
    */
    if (argc != 2) {
        fprintf(stderr, "Erreur: nombre d'arguments incorrect.\n");
        fprintf(stderr, "Usage: %s <nombre de joueurs>\n", argv[0]);
        return 1;
    }
    
    /*
        Initialiser le générateur de nombres aléatoires pour qu'il nous sorte
        des nombres différents à chaque fois
    */
    srand(time(NULL));

    /*
        L'argument de ligne de commande n°1 contient le nombre de joueurs
        sous la forme d'une chaine de caractères. atoi() (array to integer)
        permet de convertir une chaine en entier.
    */ 
    nb_joueurs = atoi(argv[1]);

    /*
        On va créer un tableau de taille dynamique pour contenir les données des
        joueurs. L'adresse du tableau sera mise dans le pointeur "joueurs", qui
        est de type "joueur *". Chaque élément du tableau occupe sizeof(joueur)
        octets, et le tableau est de longueur nb_joueurs.
        Chaque élément est ensuite initialisé avec la fonction qui va bien.
    */
    joueurs = (joueur *) malloc(nb_joueurs * sizeof(joueur));
    for (int i = 0; i < nb_joueurs; i++) {
        printf("Entrez le nom du joueur %d :\n>>> ", i);
        init_joueur(&joueurs[i]); /* prend l'adresse du i-ème joueur */
    }

    /* Boucle principale du jeu. Ceci est répété jusqu'à ce que fini != 1 */
    while (!fini) {
        printf("__________\nNouveau tour !\n");
        /* Choisir un nombre entre 0 et 100 au hasard */
        cible = floor((float)rand() / RAND_MAX * 101);

        /* Faire miser chaque joueur */
        for (int i = 0; i < nb_joueurs; i++) {
            printf("Tour de %s :\n", joueurs[i].nom);
            faire_miser_joueur(&joueurs[i]);

            /* Calculer le delta du joueur i */
            joueurs[i].delta = abs(cible-joueurs[i].nb_devine);
        }

        /*
            Fin du tour de table. On va regarder les deltas de chaque joueur,
            et celui qui a le plus petit gagne les mises des autres.
        */
        gagnant = 0;
        for (int i = 0; i < nb_joueurs; i++) {
            /*
                Si le joueur i a un delta plus petit que le joueur gagnant, bah
                le gagnant sera i. S'ils ont le même delta, celui qui a misé le plus
                remporte. Sinon, je gère pas le cas parce que j'ai la flemme
            */
            if ((joueurs[i].delta < joueurs[gagnant].delta) ||
                (joueurs[i].delta == joueurs[gagnant].delta && joueurs[i].mise > joueurs[gagnant].mise)) {
                gagnant = i;
            }
        }

        printf("Le nombre était %d, %s gagne!\n", cible, joueurs[gagnant].nom);

        /*
            Soustraire les mises de tous les perdants à leur solde,
            et y tranférer dans le solde du gagnant
        */
        for (int i = 0; i < nb_joueurs; i++) {
            if (i == gagnant) {continue;} /* Sauter le gagnant */
            transferer_mise(&joueurs[i], &joueurs[gagnant]);
        }

        /* vérifier si quequ'un a fait banqueroute, et mettre à jour fini */
        for (int i = 0; i < nb_joueurs; i++) {
            if (joueurs[i].solde <= 0) {
                perdant = i;
                fini = 1;
                break;
            }
        }
    }

    printf("__________\nTerminé, %s a fait banqueroute!\n", joueurs[perdant].nom);

    /* Libérer la mémoire occupée par le tableau de joueurs */
    free(joueurs);

    /* Renvoyer code succès */
    return 0;
}

/*
    Fonction qui initialise les données d'un joueur.
    Récupère son nom sur stdin (longueur maximale 1024 caractères), et lui
    donne $100 pour commencer à jouer.
    Prend un joueur * pour pouvoir écrire directement dedans sans devoir renvoyer
    quoi que ce soit.
*/
void init_joueur(joueur *j) {
    /* Mémoire tampon pour stocker les trucs qu'on écrit (taille max 1024) */
    char buffer[1024] = "";
    /* Lire une ligne et la stocker dans buffer */
    fgets(buffer, 1024, stdin);
    /* Extraire le premier bout de la ligne et y mettre dans le nom du joueur j */
    sscanf(buffer, "%s", j->nom); 
    /* Lui donner $100 */
    j->solde = 100;
}

void faire_miser_joueur(joueur *j) {
    /* Mémoire tampon pour stocker les trucs qu'on écrit (taille max 1024) */
    char buffer[1024] = "";

    printf("Sur quel nombre misez-vous ?\n>>> ");

    /* Lire une ligne et la stocker dans buffer */
    fgets(buffer, 1024, stdin);

    /*
        Extraire le premier truc qui ressemble à un entier dans la ligne lue,
        le convertir en entier, et y stocker dans la structure du joueur j
    */
    sscanf(buffer, "%d", &j->nb_devine); 

    printf("Vous avez $%d. Combien misez-vous ?\n>>> ", j->solde);

    /* Lire une ligne et la stocker dans buffer */
    fgets(buffer, 1024, stdin);

    /*
        Extraire le premier truc qui ressemble à un entier dans la ligne lue,
        le convertir en entier, et y stocker dans la structure du joueur j
    */
    sscanf(buffer, "%d", &j->mise); 
}

void transferer_mise(joueur *perdant, joueur *gagnant) {
    gagnant->solde += abs(perdant->mise);
    perdant->solde -= abs(perdant->mise);
}