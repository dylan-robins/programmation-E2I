/*
    On ne veut charger ce fichier que s'il n'a pas déjà été chargé. Pour faire
    ça on va définir un truc (__JOUEUR_H__) quand on le charge, et si on réessaye
    de charger le fichier plus tard ce sera déjà défini, donc on fera rien.
*/
#ifndef __JOUEUR_H__
#define __JOUEUR_H__


/* Définition d'un type structure appelé joueur */
#define TAILLE_MAX_NOM 128
typedef struct {
    char nom[TAILLE_MAX_NOM]; /* Nom du joueur */
    int solde; /* Quantité d'argent qu'il a */
    int nb_devine; /* Nombre sur lequel il mise */
    int mise; /* Somme misée */
    int delta; /* Différence entre le nombre deviné et la cible */
} joueur;

/* Fonction qui initialise un joueur */
void init_joueur(joueur *);

/* Fonction qui faire miser un joueur */
void faire_miser_joueur(joueur *);
void transferer_mise(joueur *perdant, joueur *gagnant);

#endif