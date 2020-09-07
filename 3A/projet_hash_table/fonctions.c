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

/* Compte le nombre de mots dans une liste chainée de NOEUD_DICO */
unsigned int compter_mots_liste(NOEUD_DICO *dicl) {
    int i = 0;
    // Tant qu'on est pas arrivé à la fin de la liste
    while (dicl != NULL) {
        i++;
        // Avancer dans la liste
        dicl = dicl->suivant;
    }
    return i;
}

/* Cherche un mot dans une liste chainée de NOEUD_DICO, renvoie si 1 présent 0
 * sinon */
int rechercher_mots_liste(NOEUD_DICO *dicl, char *mot) {
    while (dicl != 0) {

        // si le mot correspond au mot du NOEUD_DICO courant, renvoie 1
        if (strcmp(mot, dicl->mot) == 0) return 1;
        // Avancer
        dicl = dicl->suivant;
    }
    return 0;
}

/* Vérifie tous les mots d'une ligne de texte en cherchant les mots dans une
 * liste chainée de mots; renvoie le nombre d'erreurs */
int verifier_ligne_liste(NOEUD_DICO *dicl, char *ligne, int num_ligne) {
    char *token;
    int nbErr = 0;

    // Parcourir la ligne en enlevant toute la ponctuation (sauf les '), le 
    // whitespace bizarre, et en passant tout en minuscule
    for (int i = 0; i < strlen(ligne); i++) {
        if ((ispunct(ligne[i]) && ligne[i]!='\'') || isspace(ligne[i])) {
            // Si ponctuation ou espace, remplacer avec un espace
            ligne[i] = ' ';
        } else if (isupper(ligne[i])) {
            // Si majuscule, passer en minuscule
            ligne[i] = tolower(ligne[i]);
        }
    }

    // Parcourir chaque mot en cherchant chacun dans le dico.
    token = strtok(ligne, " ");
    while (token != NULL) {
        if (!rechercher_mots_liste(dicl, token)) {
            // Si mot pas dans la liste, incrémenter le nb d'erreur + afficher [ligne, caractère]
            nbErr++;
            printf("Erreur: \"%s\" inconnu [%d,%ld]\n", token, num_ligne, token-ligne);
        }
        // Passer au mot suivant
        token = strtok(NULL, " ");
    }
    return nbErr;
}

/* Ouvre un fichier en lecture et vérifie tous les mots dedans. Affiche les
 * erreurs et renvoie le nombre d'erreurs */
int check_file_list(NOEUD_DICO *dicl, const char *filename) {
    FILE *f_in = fopen(filename, "r");
    char buffer[256];
    int ligne = 0;
    int nbErr = 0;

    // Tant qu'on est pas à la fin du fichier
    while (!feof(f_in)) {
        // Lire une ligne
        fgets(buffer, 256, f_in);
        // Vérifier la ligne et accumuler le nombre d'erreurs
        nbErr += verifier_ligne_liste(dicl, buffer, ligne);
        ligne++;
    }

    fclose(f_in);
    return nbErr;
}

// Ajoute un mot dans une liste chainée
void ajouter_mot_liste(NOEUD_DICO *dicl, char *mot) {
    NOEUD_DICO *new = (NOEUD_DICO *) malloc(sizeof(NOEUD_DICO));
    strcpy(new->mot, mot);
    new->suivant = dicl->suivant;
    dicl->suivant = new;
}

// Détruit une liste
void detruire_liste(NOEUD_DICO *dicl) {
    NOEUD_DICO *a_suppr = dicl;
    while (a_suppr != NULL) {
        dicl = dicl->suivant;
        free(a_suppr);
        a_suppr = dicl;
    }
}

// Calcule les longueurs min, max, et moy des listes chainées d'une table de hachage
void calculer_statistique_hash(NOEUD_DICO **table, int *pmin, int *pmax, int *pmoy) {
    int len;
    *pmin = compter_mots_liste(table[0]);
    *pmax = 0;
    *pmoy = 0; // ne pas supposer que ca a déjà été initialisé
    
    // Pour chaque liste de la table de hachage
    for (int i = 0; i < MAX_TABLE_ELEMENTS; i++) {
        len = compter_mots_liste(table[i]);
        // Calculer les trucs
        *pmoy += len;
        *pmin = (len < *pmin)?len:*pmin;
        *pmax = (len > *pmax)?len:*pmax;
    }

    *pmoy /= MAX_TABLE_ELEMENTS;
}

// Cherche un mot dans la table de hachage
int rechercher_mot_hash(NOEUD_DICO **table, char *mot) {
    uint32_t hash = calculer_hash(mot, MAX_TABLE_ELEMENTS);
    return rechercher_mots_liste(table[hash], mot);
}

// Vérifie les mots d'une ligne de texte en les cherchant dans la table de hachage 
int verifier_ligne_hash(NOEUD_DICO **table, char *ligne, int num_ligne) {
    char *token;
    int nbErr = 0;

    // Enlever toute la ponctuation, le whitespace et les majuscules
    for (int i = 0; i < strlen(ligne); i++) {
        if ((ispunct(ligne[i]) && ligne[i]!='\'') || isspace(ligne[i])) {
            ligne[i] = ' ';
        } else if (isupper(ligne[i])) {
            ligne[i] = tolower(ligne[i]);
        }
    }

    // Parcourir chaque mot de la ligne
    token = strtok(ligne, " ");
    while (token != NULL) {
        if (!rechercher_mot_hash(table, token)) {
            // Si le mot n'est pas dans la table de hachage, afficher l'erreur
            nbErr++;
            printf("Erreur: \"%s\" inconnu [%d,%ld]\n", token, num_ligne, token-ligne);
        }
        token = strtok(NULL, " ");
    }
    return nbErr;
}

// Ouvrir un fichier en lecture et vérifier tous les mots dedans avec une table
// de hachage. Renvoie le nombre d'erreurs
int check_file_hash(NOEUD_DICO **table, const char *filename) {
    FILE *f_in = fopen(filename, "r");
    char buffer[256];
    int ligne = 0;
    int nbErr = 0;

    // lire ligne par ligne et tester chaque ligne
    while (!feof(f_in)) {
        fgets(buffer, 256, f_in);
        nbErr += verifier_ligne_hash(table, buffer, ligne);
        ligne++;
    }

    fclose(f_in);
    return nbErr;
}

// Détruit une table de hachage
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
    free(table);
}

// Rotation à gauche de 5 d'une chaine de caractères
static uint32_t rotate5l(uint32_t number) {
    uint8_t lsb5 = number >> 27;
    number = (number << 5) | lsb5;
    return number;
}

// Calcule le hash d'un mot passé en paramètres
uint32_t calculer_hash(const char* str, uint32_t mod) {
    uint32_t hashed = 0;
    // Concaténer les 4 premiers caractères
    for (int i = 0; i < 4 && i < strlen(str); i++) {
        hashed |= (str[i] << 8*i);
    }
    // Pour tous les caractères suivants
    for (int i = 4; i < strlen(str); i++) {
        // Faire une rotation gauche de 5
        hashed = rotate5l(hashed);
        // Ou excusif entre le hash et le cararctère courant
        hashed ^= str[i];
    }
    // Renvoyer le hash modulo la taille du tableau
    return hashed % mod;
}

// Ajouter un mot au début d'une liste chainée
static void ajouter_mot_debut_liste(NOEUD_DICO **list, const char *mot) {
    NOEUD_DICO *new = (NOEUD_DICO *)malloc(sizeof(NOEUD_DICO));
    strcpy(new->mot, mot);
    new->suivant = *list;
    *list = new;
}

//  Construire une table de hachage à partir d'un fichier dico ouvert en lecture
NOEUD_DICO **construire_hash(FILE *dic) {
    NOEUD_DICO **table = (NOEUD_DICO **) calloc(MAX_TABLE_ELEMENTS, sizeof(NOEUD_DICO*));
    char line[256];
    char *base_word = 0;
    char *flags = 0;
    NOEUD_DICO *words_to_add = NULL;
    NOEUD_DICO *poubelle;
    uint32_t hash;

    // Pour chaque ligne du fichier
    while (!feof(dic)) {
        fgets(line, 256, dic);
        line[strlen(line)-1] = '\0'; // strip trailing newline
        
        // Séparer le mot de base et les flags
        base_word = strtok(line, "/");
        flags = strtok(NULL, "/");

        // Si le mot de base existe, construire les mots dérivés
        if (base_word != NULL) {
            words_to_add = expandFlags(base_word, flags);
        }
        // POur chaque mot dérivé, le rajouter dans la table de hachage
        while (words_to_add != NULL) {
            // Calculer le hash du mot
            hash = calculer_hash(words_to_add->mot, MAX_TABLE_ELEMENTS);
            // L'ajouter à la tabke
            ajouter_mot_debut_liste(&(table[hash]), words_to_add->mot);
            // Supprimer le noeud de la liste temporaire
            poubelle = words_to_add;
            words_to_add = words_to_add->suivant;
            free(poubelle);
        }
    }
    return table;
}

// Renvoie un nouveau noeud contenant le mot passé en paramètres
static NOEUD_DICO* new_noeud(const char *mot, NOEUD_DICO* suivant) {
    NOEUD_DICO *new = malloc(sizeof(NOEUD_DICO));
    strcpy(new->mot, mot);
    new->suivant = NULL;
    return new;
}

// Fonction auxiliaire qui construit dans un buffer le mot composé d'un préfixe, le mot principal et d'un suffixe
static void concat(char buffer[MAX_TAILLE_MOT], const char prefix, const char* word, const char suffix) {
    // Si le préfixe est non nul
    if (prefix != '\0') {
        // Ajouter le préfixe
        buffer[0] = prefix;
        // Ajouter un apostrophe
        buffer[1] = '\'';
        buffer[2] = '\0';
        // Rajouter le mot principal
        strcat(buffer, word);
    } else {
        // Si le préfixe est nul, simplement copier le mot
        strcpy(buffer, word);
    }
    // Si le suffixe est non nul, rajouter le suffixe
    if (suffix != '\0') {
        buffer[strlen(buffer)+1] = '\0';
        buffer[strlen(buffer)] = suffix;
    }
}

// Développer la liste des mots dérivés à partir d'un mot principal et d'une liste de flags
NOEUD_DICO *expandFlags(char *mot, char *flags) {
    NOEUD_DICO *liste = NULL;
    char buffer[MAX_TAILLE_MOT];
    char *ptr_suffixe = NULL; // Servira pour le flag G

    // Si le mot n'existe pas, ne rien faire
    if (strlen(mot) == 0) {
        return NULL;
    }
    // Rajouter le mot de base dans la liste
    liste = new_noeud(mot, NULL);

    if (flags != NULL) {
        for (int i = 0; i < strlen(flags); i++) {
            switch (flags[i]) {
                case 'S':
                case 'X':
                    // Construire le mot pluriel (soit un s soit un x)
                    concat(buffer, 0, mot, tolower(flags[i]));
                    // rajouter le mot dérivé
                    ajouter_mot_debut_liste(&liste, buffer);
                    break;
                case 'n':
                    // Construire le mot avec le préfixe n'
                    concat(buffer, 'n', mot, 0);
                    // rajouter le mot dérivé
                    ajouter_mot_debut_liste(&liste, buffer);
                    // Construire le mot avec le préfixe qu'
                    strcpy(buffer, "qu'");
                    strcat(buffer, mot);
                    // rajouter le mot dérivé
                    ajouter_mot_debut_liste(&liste, buffer);
                    
                    // Si les mots dérivés peuvent avoir un pluriel en s
                    if (strchr(flags, 'S') != NULL) {
                        // Construire le pluriel en s avec le préfixe n'
                        concat(buffer, 'n', mot, 's');
                        // rajouter le mot dérivé
                        ajouter_mot_debut_liste(&liste, buffer);
                        // Construire le pluriel en s avec le préfixe qu'
                        strcpy(buffer, "qu'");
                        strcat(buffer, mot);
                        strcat(buffer, "s");
                        // rajouter le mot dérivé
                        ajouter_mot_debut_liste(&liste, buffer);

                    // Si les mots dérivés peuvent avoir un pluriel en x
                    } else if (strchr(flags, 'X') != NULL) {
                        // Construire le pluriel en x avec le préfixe n'
                        concat(buffer, 'n', mot, 'x');
                        // rajouter le mot dérivé
                        ajouter_mot_debut_liste(&liste, buffer);
                        // Construire le pluriel en x avec le préfixe qu'
                        strcpy(buffer, "qu'");
                        strcat(buffer, mot);
                        strcat(buffer, "x");
                        // rajouter le mot dérivé
                        ajouter_mot_debut_liste(&liste, buffer);
                    }
                    break;
                case 'm':
                case 't':
                case 'l':
                    // Construire le mot préfixé de m, t ou l
                    concat(buffer, flags[i], mot, 0);
                    // rajouter le mot dérivé
                    ajouter_mot_debut_liste(&liste, buffer);

                    // Si le mot dérivé peut avoir un pluriel en s
                    if (strchr(flags, 'S') != NULL) {
                        // Construire le pluriel en s avec le préfixe
                        concat(buffer, flags[i], mot, 's');
                        // rajouter le mot dérivé
                        ajouter_mot_debut_liste(&liste, buffer);
                    // Si le mot dérivé peut avoir un pluriel en x
                    } else if (strchr(flags, 'X') != NULL) {
                        // Construire le pluriel en x avec le préfixe
                        concat(buffer, flags[i], mot, 'x');
                        // rajouter le mot dérivé
                        ajouter_mot_debut_liste(&liste, buffer);
                    }
                    break;
                    
                case 's':
                case 'j':
                case 'L':
                    // Construire le mot préfixé de s, j ou l
                    concat(buffer, tolower(flags[i]), mot, 0);
                    // rajouter le mot dérivé
                    ajouter_mot_debut_liste(&liste, buffer);
                    break;
                case 'M':
                    // Construire le mot préfixé de d
                    concat(buffer, 'd', mot, 0);
                    // rajouter le mot dérivé
                    ajouter_mot_debut_liste(&liste, buffer);

                    // Si le mot dérivé peut avoir un pluriel en s
                    if (strchr(flags, 'S') != NULL) {
                        // Construire le pluriel en s avec le préfixe
                        concat(buffer, 'd', mot, 's');
                        // rajouter le mot dérivé
                        ajouter_mot_debut_liste(&liste, buffer);

                    // Si le mot dérivé peut avoir un pluriel en x
                    } else if (strchr(flags, 'X') != NULL) {
                        // Construire le pluriel en x avec le préfixe
                        concat(buffer, 'd', mot, 'x');
                        // rajouter le mot dérivé
                        ajouter_mot_debut_liste(&liste, buffer);
                    }
                    break;
                case 'G':
                    strcpy(buffer, mot);

                    // Chercher le suffixe EUSE
                    ptr_suffixe = strstr(buffer, "euse");
                    // Si suffixe présent et "e" final de "euse" est le dernire char du mot
                    if (ptr_suffixe != NULL&& (&ptr_suffixe[3] == &buffer[strlen(buffer)-1])) {
                        // Remplacer le suffixe par le masculin singulier
                        strcpy(ptr_suffixe, "eur");
                        ajouter_mot_debut_liste(&liste, buffer);
                        // Remplacer le suffixe par le masculin pluriel
                        strcpy(ptr_suffixe, "eurs");
                        ajouter_mot_debut_liste(&liste, buffer);
                    }

                    // Chercher le suffixe RICE
                    ptr_suffixe = strstr(buffer, "rice");
                    // Si suffixe présent et "e" final de "rice" est le dernire char du mot
                    if (ptr_suffixe != NULL&& (&ptr_suffixe[3] == &buffer[strlen(buffer)-1])) {
                        // Remplacer le suffixe par le masculin singulier
                        strcpy(ptr_suffixe, "eur");
                        ajouter_mot_debut_liste(&liste, buffer);
                        // Remplacer le suffixe par le masculin pluriel
                        strcpy(ptr_suffixe, "eurs");
                        ajouter_mot_debut_liste(&liste, buffer);
                    }

                    // Chercher le suffixe ERESSE
                    ptr_suffixe = strstr(buffer, "eresse");
                    // Si suffixe présent et "e" final de "eresse" est le dernire char du mot
                    if (ptr_suffixe != NULL&& (&ptr_suffixe[5] == &buffer[strlen(buffer)-1])) {
                        // Remplacer le suffixe par le masculin singulier
                        strcpy(ptr_suffixe, "eur");
                        ajouter_mot_debut_liste(&liste, buffer);
                        // Remplacer le suffixe par le masculin pluriel
                        strcpy(ptr_suffixe, "eurs");
                        ajouter_mot_debut_liste(&liste, buffer);
                    }

                    // Chercher le suffixe ORESSE
                    ptr_suffixe = strstr(buffer, "oresse");
                    // Si suffixe présent et "e" final de "oresse" est le dernire char du mot
                    if (ptr_suffixe != NULL && (&ptr_suffixe[5] == &buffer[strlen(buffer)-1])) {
                        // Remplacer le suffixe par le masculin singulier
                        strcpy(ptr_suffixe, "eur");
                        ajouter_mot_debut_liste(&liste, buffer);
                        // Remplacer le suffixe par le masculin pluriel
                        strcpy(ptr_suffixe, "eurs");
                        ajouter_mot_debut_liste(&liste, buffer);
                    }

                    // Chercher le suffixe ALE
                    ptr_suffixe = strstr(buffer, "ale");
                    // Si suffixe présent et "e" final de "ale" est le dernire char du mot
                    if (ptr_suffixe != NULL && (&ptr_suffixe[2] == &buffer[strlen(buffer)-1])) {
                        // Remplacer le suffixe par le masculin singulier
                        strcpy(ptr_suffixe, "al");
                        ajouter_mot_debut_liste(&liste, buffer);
                        // Remplacer le suffixe par le masculin pluriel
                        strcpy(ptr_suffixe, "als");
                        ajouter_mot_debut_liste(&liste, buffer);
                    }
            }
        }
    }
    return liste;
}