/***********************************µ******/
/* Fichier dico.h à inclure               */
/* Contient les déclaration de structures */
/* constantes symboliques et prototypes   */
/* des fonctions                          */
/* Frédéric Rousseau le 20 avril 2010     */
/*                                        */
/*
 * Filename: /home/dylan/Documents/Cours/E2I/prog/projet/dico.h
 * Path: /home/dylan/Documents/Cours/E2I/prog/projet
 * Created Date: Monday, June 15th 2020, 9:25:53 am
 * Author: Dylan ROBINS
 */


/* Inclusion de bibliothèque */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Définition de macros pour coloriser l'affichage */
#define RED "\033[1;31m"
#define NRM "\033[0m"
#define BLU "\033[0;34m"

/* Definition des structures de données, des define et des prototypes... */
#define MAX_TABLE_ELEMENTS 500
#define MAX_TAILLE_MOT 50
#define MAX_LIGNE 256

/* Noeud pour la liste chainee simple 1ere partie de l'exam */
typedef struct tableElement {
    char mot[MAX_TAILLE_MOT];
    struct tableElement *suivant;
} NOEUD_DICO;

/***********************************************************************/
/* Fonctions donnees sous forme objet dans le fichier fonctions_prof.o */

/* A partir d'un fichier ouvert en lecture, construit la liste */
/* et retourne l'adresse du premier noeud (mot) */
NOEUD_DICO *_construire_liste(FILE *dic);
void detruire_liste(NOEUD_DICO *dicl);

/* Fonction _verifier_ligne - dicl represente la liste de mots */
/* ligne est une ligne de texte, num_ligne est le numero de la ligne dans le
 * fichier */
void _verifier_ligne_liste(NOEUD_DICO *dicl, char *ligne, int num_ligne);

/* A partir d'un fichier ouvert en lecture, construit un tableau de listes */
/* et retourne l'adresse du premier élément du tableau (adresse du 1er
  element de la 1ere liste */
NOEUD_DICO **_construire_hash(FILE *dic);
void detruire_table(NOEUD_DICO **table);

/* Calcule et rend l'entier correspondant à la valeur de hachage */
/* d'une chaine de caracteres */
uint32_t calculer_hash(const char* str, uint32_t mod);

/* Fonction _verifier_ligne - dicl represente la liste de lots */
/* ligne est une ligne de texte, num_ligne est le numero de la ligne dans le
 * fichier */
void _verifier_ligne_hash(NOEUD_DICO **table, char *ligne, int num_ligne);

/* Fonction _compter_mots_liste qui rend le nombre de mots du dictionnaire */
/* le dictionnaire étantune seule liste chainee */
unsigned int _compter_mots_liste(NOEUD_DICO *dicl);

/* Fonction _calculer_statistique_hash qui calcule certaines statistiques */
/* sur une table de hash passee en parametre */
void _calculer_statistique_hash(NOEUD_DICO **table, int *pmin, int *pmax, int *pmoy);

/* question 1 */
unsigned int compter_mots_liste(NOEUD_DICO *dicl);

/* question 2 */
int rechercher_mots_liste(NOEUD_DICO *dicl, char *mot);

/* question 3 */
void ajouter_mot_liste(NOEUD_DICO *dicl, char *mot);
/* NOEUD_DICO * ajouter_mot(NOEUD_DICO * dicl); */

/* question 4 */
int verifier_ligne_liste(NOEUD_DICO *dicl, char *ligne, int num_ligne);
int check_file_list(NOEUD_DICO *dicl, const char *filename);
/* question 6 */
void calculer_statistique_hash(NOEUD_DICO **table, int *pmin, int *pmax, int *pmoy);
/* question 7 */
int rechercher_mot_hash(NOEUD_DICO **table, char *mot);
/* question 8 */
int verifier_ligne_hash(NOEUD_DICO **table, char *ligne, int num_ligne);
int check_file_hash(NOEUD_DICO **table, const char *filename);

NOEUD_DICO **construire_hash(FILE *dic);
NOEUD_DICO *__expandFlags(char *mot, char *flags);
NOEUD_DICO *expandFlags(char *mot, char *flags);