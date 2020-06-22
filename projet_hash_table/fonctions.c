/*
 * Filename: /home/dylan/Documents/Cours/E2I/prog/projet/fonctions.c
 * Path: /home/dylan/Documents/Cours/E2I/prog/projet
 * Created Date: Tuesday, June 16th 2020, 2:32:37 pm
 * Author: Dylan ROBINS
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include "dico.h"

unsigned int compter_mots_liste(NOEUD_DICO *dicl) {
    int i = 0;
    while (dicl != NULL) {
        i++;
        dicl = dicl->suivant;
    }
    return i;
}

int rechercher_mots_liste(NOEUD_DICO *dicl, char *mot) {
    while (dicl != 0) {
        if (strcmp(mot, dicl->mot) == 0) return 1;
        dicl = dicl->suivant;
    }
    return 0;
}

int verifier_ligne_liste(NOEUD_DICO *dicl, char *ligne, int num_ligne) {
    char *token;
    int nbErr = 0;

    for (int i = 0; i < strlen(ligne); i++) {
        if ((ispunct(ligne[i]) && ligne[i]!='\'') || isspace(ligne[i])) {
            ligne[i] = ' ';
        } else if (isupper(ligne[i])) {
            ligne[i] = tolower(ligne[i]);
        }
    }

    token = strtok(ligne, " ");
    while (token != NULL) {
        if (!rechercher_mots_liste(dicl, token)) {
            nbErr++;
            printf("Erreur: \"%s\" inconnu [%d,%ld]\n", token, num_ligne, token-ligne);
        }
        token = strtok(NULL, " ");
    }
    return nbErr;
}

int check_file_list(NOEUD_DICO *dicl, const char *filename) {
    FILE *f_in = fopen(filename, "r");
    char buffer[256];
    int ligne = 0;
    int nbErr = 0;

    while (!feof(f_in)) {
        fgets(buffer, 256, f_in);
        nbErr += verifier_ligne_liste(dicl, buffer, ligne);
        ligne++;
    }

    fclose(f_in);
    return nbErr;
}

void ajouter_mot_liste(NOEUD_DICO *dicl, char *mot) {
    NOEUD_DICO *new = (NOEUD_DICO *)malloc(sizeof(NOEUD_DICO));
    strcpy(new->mot, mot);
    new->suivant = dicl->suivant;
    dicl->suivant = new;
}

void detruire_liste(NOEUD_DICO *dicl) {
    NOEUD_DICO *a_suppr = dicl;
    while (a_suppr != NULL) {
        dicl = dicl->suivant;
        free(a_suppr);
        a_suppr = dicl;
    }
}

void calculer_statistique_hash(NOEUD_DICO **table, int *pmin, int *pmax, int *pmoy) {
    int len;
    *pmin = compter_mots_liste(table[0]);
    *pmax = 0;
    *pmoy = 0; // ne pas supposer que ca a déjà été initialisé
    
    for (int i = 0; i < MAX_TABLE_ELEMENTS; i++) {
        len = compter_mots_liste(table[i]);
        *pmoy += len;
        *pmin = (len < *pmin)?len:*pmin;
        *pmax = (len > *pmax)?len:*pmax;
    }

    *pmoy /= MAX_TABLE_ELEMENTS;
}

int rechercher_mot_hash(NOEUD_DICO **table, char *mot) {
    uint32_t hash = calculer_hash(mot, MAX_TABLE_ELEMENTS);
    return rechercher_mots_liste(table[hash], mot);
}

int verifier_ligne_hash(NOEUD_DICO **table, char *ligne, int num_ligne) {
    char *token;
    int nbErr = 0;

    for (int i = 0; i < strlen(ligne); i++) {
        if ((ispunct(ligne[i]) && ligne[i]!='\'') || isspace(ligne[i])) {
            ligne[i] = ' ';
        } else if (isupper(ligne[i])) {
            ligne[i] = tolower(ligne[i]);
        }
    }

    token = strtok(ligne, " ");
    while (token != NULL) {
        if (!rechercher_mot_hash(table, token)) {
            nbErr++;
            printf("Erreur: \"%s\" inconnu [%d,%ld]\n", token, num_ligne, token-ligne);
        }
        token = strtok(NULL, " ");
    }
    return nbErr;
}

int check_file_hash(NOEUD_DICO **table, const char *filename) {
    FILE *f_in = fopen(filename, "r");
    char buffer[256];
    int ligne = 0;
    int nbErr = 0;

    while (!feof(f_in)) {
        fgets(buffer, 256, f_in);
        nbErr += verifier_ligne_hash(table, buffer, ligne);
        ligne++;
    }

    fclose(f_in);
    return nbErr;
}

void detruire_table(NOEUD_DICO **table) {
    NOEUD_DICO *a_suppr;
    for (int i = 0; i < MAX_TABLE_ELEMENTS; i++) {
        a_suppr = table[i];
        while (a_suppr != NULL) {
            table[i] = table[i]->suivant;
            free(a_suppr);
            a_suppr = table[i];
        }
    }
}

static uint32_t rotate5l(uint32_t number) {
    uint8_t lsb5 = number >> 27;
    number = (number << 5) | lsb5;
    return number;
}

uint32_t calculer_hash(const char* str, uint32_t mod) {
    uint32_t hashed = 0;
    for (int i = 0; i < 4 && i < strlen(str); i++) {
        hashed |= (str[i] << 8*i);
    }
    for (int i = 4; i < strlen(str); i++) {
        hashed = rotate5l(hashed);
        hashed ^= str[i];
    }
    return hashed % mod;
}

static void ajouter_mot_debut_liste(NOEUD_DICO **list, const char *mot) {
    NOEUD_DICO *new = (NOEUD_DICO *)malloc(sizeof(NOEUD_DICO));
    strcpy(new->mot, mot);
    new->suivant = *list;
    *list = new;
}

NOEUD_DICO **construire_hash(FILE *dic) {
    NOEUD_DICO **table = (NOEUD_DICO **) calloc(MAX_TABLE_ELEMENTS, sizeof(NOEUD_DICO*));
    char line[256];
    char *base_word = 0;
    char *flags = 0;
    NOEUD_DICO *words_to_add = NULL;
    NOEUD_DICO *poubelle;
    uint32_t hash;

    while (!feof(dic)) {
        fgets(line, 256, dic);
        line[strlen(line)-1] = '\0'; // strip trailing newline
        base_word = strtok(line, "/");
        flags = strtok(NULL, "/");
        if (base_word != NULL) {
            words_to_add = expandFlags(base_word, flags);
        }
        while (words_to_add != NULL) {
            hash = calculer_hash(words_to_add->mot, MAX_TABLE_ELEMENTS);
            ajouter_mot_debut_liste(&(table[hash]), words_to_add->mot);
            poubelle = words_to_add;
            words_to_add = words_to_add->suivant;
            free(poubelle);
        }
    }
    return table;
}

static NOEUD_DICO* new_noeud(const char *mot, NOEUD_DICO* suivant) {
    NOEUD_DICO *new = malloc(sizeof(NOEUD_DICO));
    strcpy(new->mot, mot);
    new->suivant = NULL;
    return new;
}

static void concat(char buffer[MAX_TAILLE_MOT], const char prefix, const char* word, const char suffix) {
    if (prefix != '\0') {
        buffer[0] = prefix;
        buffer[1] = '\'';
        buffer[2] = '\0';
        strcat(buffer, word);
    } else {
        strcpy(buffer, word);
    }
    if (suffix != '\0') {
        buffer[strlen(buffer)+1] = '\0';
        buffer[strlen(buffer)] = suffix;
    }
}

NOEUD_DICO *expandFlags(char *mot, char *flags) {
    NOEUD_DICO *liste = NULL;
    NOEUD_DICO *endOfList = NULL;
    char buffer[MAX_TAILLE_MOT];

    if (strlen(mot) == 0) {
        return NULL;
    }
    // put base word in list
    liste = new_noeud(mot, NULL);

    endOfList = liste;
    if (flags != NULL) {
        for (int i = 0; i < strlen(flags); i++) {
            switch (flags[i]) {
                case 'S':
                case 'X':
                    // build word and populate new element
                    concat(buffer, 0, mot, tolower(flags[i]));
                    // add element at end of list
                    endOfList->suivant = new_noeud(buffer, NULL);
                    endOfList = endOfList->suivant;
                    break;
                case 'n':
                    // build word and populate new element
                    concat(buffer, 'n', mot, 0);
                    // add element at end of list
                    endOfList->suivant = new_noeud(buffer, NULL);
                    endOfList = endOfList->suivant;
                    // build word and populate new element
                    strcpy(buffer, "qu'");
                    strcat(buffer, mot);
                    // add element at end of list
                    endOfList->suivant = new_noeud(buffer, NULL);
                    endOfList = endOfList->suivant;

                    if (strchr(flags, 'S') != NULL) {
                        // build word and populate new element
                        concat(buffer, 'n', mot, 's');
                        // add element at end of list
                        endOfList->suivant = new_noeud(buffer, NULL);
                        endOfList = endOfList->suivant;
                        // build word and populate new element
                        strcpy(buffer, "qu'");
                        strcat(buffer, mot);
                        strcat(buffer, "s");
                        // add element at end of list
                        endOfList->suivant = new_noeud(buffer, NULL);
                        endOfList = endOfList->suivant;
                    } else if (strchr(flags, 'X') != NULL) {
                        // build word and populate new element
                        concat(buffer, 'n', mot, 'x');
                        // add element at end of list
                        endOfList->suivant = new_noeud(buffer, NULL);
                        endOfList = endOfList->suivant;
                        // build word and populate new element
                        strcpy(buffer, "qu'");
                        strcat(buffer, mot);
                        strcat(buffer, "x");
                        // add element at end of list
                        endOfList->suivant = new_noeud(buffer, NULL);
                        endOfList = endOfList->suivant;
                    }
                    break;
                case 'm':
                case 't':
                case 'l':
                    // build word and populate new element
                    concat(buffer, flags[i], mot, 0);
                    // add element at end of list
                    endOfList->suivant = new_noeud(buffer, NULL);
                    endOfList = endOfList->suivant;

                    if (strchr(flags, 'S') != NULL) {
                        // build word and populate new element
                        concat(buffer, flags[i], mot, 's');
                        // add element at end of list
                        endOfList->suivant = new_noeud(buffer, NULL);
                        endOfList = endOfList->suivant;
                    } else if (strchr(flags, 'X') != NULL) {
                        // build word and populate new element
                        concat(buffer, flags[i], mot, 'x');
                        // add element at end of list
                        endOfList->suivant = new_noeud(buffer, NULL);
                        endOfList = endOfList->suivant;
                    }
                    break;
                    
                case 's':
                case 'j':
                case 'L':
                    // build word and populate new element
                    concat(buffer, tolower(flags[i]), mot, 0);
                    // add element at end of list
                    endOfList->suivant = new_noeud(buffer, NULL);
                    endOfList = endOfList->suivant;
                    break;
                case 'M':
                    // build word and populate new element
                    concat(buffer, 'd', mot, 0);
                    // add element at end of list
                    endOfList->suivant = new_noeud(buffer, NULL);
                    endOfList = endOfList->suivant;

                    if (strchr(flags, 'S') != NULL) {
                        // build word and populate new element
                        concat(buffer, 'd', mot, 's');
                        // add element at end of list
                        endOfList->suivant = new_noeud(buffer, NULL);
                        endOfList = endOfList->suivant;
                    } else if (strchr(flags, 'X') != NULL) {
                        // build word and populate new element
                        concat(buffer, 'd', mot, 'x');
                        // add element at end of list
                        endOfList->suivant = new_noeud(buffer, NULL);
                        endOfList = endOfList->suivant;
                    }
                    break;
            }
        }
    }
    return liste;
}