/* Sujet d'exam 3i3 - Polytech Grenoble - avril 2010 */
/* Version originale : Anthony Fleury --  */
/* Version modifiee : Frederic Rousseau --
 * Frederic.Rousseau@univ-grenoble-alpes.fr */

/*
 * Filename: /home/dylan/Documents/Cours/E2I/prog/projet/dico.c
 * Path: /home/dylan/Documents/Cours/E2I/prog/projet
 * Created Date: Monday, June 15th 2020, 9:25:16 am
 * Author: Dylan ROBINS
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "dico.h"


int main(int argc, char *argv[]) {
    /* programme de test du correcteur d'orthographe */
    FILE *dic;
    NOEUD_DICO *tete;
    NOEUD_DICO **Table;
    char dico_filename[256] = "fr_FR.dic";
    int tmp;
    int min, max, moy;
    int ref_min = 700000, ref_max = 0, ref_moy = 0;
    clock_t timer;

    if (argc == 2) {
        strcpy(dico_filename, argv[1]);
    }
    /*************************************************************************/
    /*                     PARTIE 1 - DICO LISTE CHAINEE                     */
    /*************************************************************************/

    /************************ CONSTRUCTION DE LA LISTE ***********************/
    printf("*** Dictionnaire : 1ere partie ***\n");
    printf("*** Construction d'une liste chainee simple ***\n\n");
    dic = fopen("fr_FR.dic", "r");
    tete = _construire_liste(dic);

    /************************ COMPTE DU NOMBRE DE MOTS ***********************/
    printf("Nombre de noeuds de la liste (iteratif) : %d\n", compter_mots_liste(tete));
    if (compter_mots_liste(tete)==_compter_mots_liste(tete)) {
        printf("\t> %sPASS%s\n", BLU, NRM);
    } else {
        printf("\t> %sFAIL%s\n", RED, NRM);
    }

    /******************** RECHERCHE D'UN MOT DANS LA LISTE *******************/
    printf("<chien> est dans la liste : %s\n", rechercher_mots_liste(tete, "chien")?"Oui":"Non");
    if (rechercher_mots_liste(tete, "chien")) {
        printf("\t> %sPASS%s\n", BLU, NRM);
    } else {
        printf("\t> %sFAIL%s\n", RED, NRM);
    }

    /********************* AJOUT D'UN MOT DANS LA LISTE **********************/
    printf("<microcontrolleur> est dans la liste : %s\n", rechercher_mots_liste(tete, "microcontrolleur")?"Oui":"Non");
    tmp = rechercher_mots_liste(tete, "microcontrolleur");
    printf("Ajout du mot <microcontrolleur>\n");
    ajouter_mot_liste(tete, "microcontrolleur");
    if ((!tmp && rechercher_mots_liste(tete, "microcontrolleur"))) {
        printf("\t> %sPASS%s\n", BLU, NRM);
    } else {
        printf("\t> %sFAIL%s\n", RED, NRM);
    }

    /*********************** VERIFICATION D'UN FICHIER ***********************/
    timer = clock();
    tmp = check_file_list(tete, "texte.txt");
    timer = clock() - timer;

    printf("file checked in %ld ms\n", timer*1000/CLOCKS_PER_SEC);
    if (tmp == 5) {
        printf("\t> %sPASS%s\n", BLU, NRM);
    } else {
        printf("\t> %sFAIL%s\n", RED, NRM);
    }

    // cleanup
    detruire_liste(tete);
    fclose(dic);

    /*************************************************************************/
    /*                    PARTIE 2 - DICO TABLE DE HACHAGE                   */
    /*************************************************************************/

    dic = fopen("fr_FR.dic", "r");

    /****************** CONSTRUCTION DE LA TABLE DE HACHAGE ******************/
    printf("\n\n*** Dictionnaire : 2ieme partie ***\n");
    printf("*** Construction d'une table de hachage ***\n\n");
    Table = construire_hash(dic);

    /********************* CALCUL DES STATS DE LA TABLE **********************/
    calculer_statistique_hash(Table, &min, &max, &moy);
    printf("Longueur de la liste la plus courte : %d\n", min);
    printf("Longueur de la liste la plus longue : %d\n", max);
    printf("Moyenne des longueurs des listes : %d\n", moy);
    _calculer_statistique_hash(Table, &ref_min, &ref_max, &ref_moy);
    if (ref_min==min && ref_max==max && ref_moy==moy) {
        printf("\t> %sPASS%s\n", BLU, NRM);
    } else {
        printf("\t> %sFAIL%s\nmin: %d==%d; max: %d==%d; moy: %d==%d\n", RED, NRM, ref_min, min, ref_max, max, ref_moy, moy);
    }

    /******************* RECHERCHE D'UN MOT DANS LA TABLE ********************/
    tmp = rechercher_mot_hash(Table, "chien");
    printf("<chien> est dans la table : %s\n", tmp?"Oui":"Non");
    if (tmp) {
        printf("\t> %sPASS%s\n", BLU, NRM);
    } else {
        printf("\t> %sFAIL%s\n", RED, NRM);
    }
    
    /*********************** VERIFICATION D'UN FICHIER ***********************/
    timer = clock();
    tmp = check_file_hash(Table, "texte.txt");
    timer = clock() - timer;
    
    printf("file checked in %ld ms\n", timer*1000/CLOCKS_PER_SEC);
    if (tmp == 5) {
        printf("\t> %sPASS%s\n", BLU, NRM);
    } else {
        printf("\t> %sFAIL%s\n", RED, NRM);
    }

    // cleanup
    detruire_table(Table);
    fclose(dic);

    return 0;
}
