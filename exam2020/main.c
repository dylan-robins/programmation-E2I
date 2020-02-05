#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *tab;
    int dim;
} TabDim;

/* PARTIE 1 - PREMIERS PAS */

/*
    Affiche un tableau dimensionne. Pas de '\n' a la fin pour faciliter la
    construction de logs de test
*/
void affichage(int *tab) {
    printf("[ ");
    for (int i = 1; i <= tab[0]; i++) {
        printf("%d ", tab[i]);
    }
    printf("]");
}

/*
    Remplit un tableau dimensionne avec la valeur val
*/
void remplissage(int *tab, int val) {
    for (int i = 1; i <= tab[0]; i++) {
        tab[i] = val;
    }
}

/*
   Remplit un tableau dimensionne avec la suite d'entiers partant de val 
*/
void remplissage_sequence(int *tab, int val) {
    for (int i = 1; i <= tab[0]; i++) {
        tab[i] = val;
        val++;
    }
}

/*
    renvoie la somme des elements d'un tableau dimensionne
*/
int somme(int *tab) {
    int s = 0; // accumulateur
    for (int i = 1; i <= tab[0]; i++) {
        s += tab[i];
    }
    return s;
}

/* PARTIE 2 - CREATION, DESTRUCTION */

/*
    Alloue un tableau dimensionne de taille N et initialise ses valeurs a 0
*/
int *creation(int N) {
    // allouer la memoire
    int *tab = (int *)malloc((N+1)*sizeof(int));
    // stocker la taille du tableau
    tab[0] = N;
    // remplir le reste avec des 0
    remplissage(tab, 0);
    return tab;
}

/*
    libere la memoire prise par un tableau dimensionne alloue dynamiquement
*/
void destruction(int *tab) {
    free(tab);
}

/*
    Compare le resultat de notre fonction somme avec le resultat de la fonction
    generale N(N+1)/2
*/
void verification_somme_entiers(int N) {
    int *tab = creation(N);
    remplissage_sequence(tab, 1);
    printf(
        "somme des entiers 1..%d : prevue %d obtenue %d\n",
        N, (N*(N+1)/2), somme(tab)
    );
    destruction(tab);

}

/* PARTIE 3 - COPIE, CONCATENATION, DECOUPAGE, COMPARAISON */

/*
    Cree un nouveau tableau dimensionne et copie tab dedans
*/
int *copie(int *tab) {
    // cree un nouveau tableau de meme taille que tab
    int *new_tab = creation(tab[0]);

    // remplir le nouveau tableau
    for (int i = 1; i <= tab[0]; i++) {
        new_tab[i] = tab[i];
    }
    // renvoyer le pointeur vers le nouveau tableau
    return new_tab;
}

/*
    Concatene tab1 et tab2 ensemble dans un nouveau tableau dont on renvoie
    un pointeur
*/
int *concatenation(int *tab1, int *tab2) {
    // creer un tableau assez grand pour contenir les donnees de tab1 et tab2
    int *new_tab = creation(tab1[0] + tab2[0]);
    // copier tab1 dans new_tab
    int i = 1;
    while (i <= tab1[0]) {
        new_tab[i] = tab1[i];
        i++;
    }
    // copier tab2 dans new_tab a la suite
    while (i <= new_tab[0]) {
        new_tab[i] = tab2[i-tab1[0]];
        i++;
    }
    return new_tab;
}

/*
    Decoupe tab en deux sous-tableaux qui sont alloues dans ptab1 et ptab2
*/
void decoupage(int *tab, int index, int **ptab1, int **ptab2) {
    if (tab[0] < index) {
        // cas ou index est apres la fin du tableau
        *ptab1 = copie(tab);
        *ptab2 = creation(0);
    } else if (index < 1) {
        // cas ou index est avant le debut du tableau
        *ptab1 = creation(0);
        *ptab2 = copie(tab);
    } else {
        // cas ou l'index est au milieu du tableau
        *ptab1 = creation(index);
        *ptab2 = creation(tab[0] - index);

        for (int i = 1; i <= index; i++) {
            (*ptab1)[i] = tab[i];
        }
        for (int i = index+1; i <= tab[0]; i++) {
            (*ptab2)[i-index] = tab[i];
        }

    }
}

/*
    compare deux tableaux et renvoie 1 si ce sont les memes
*/
int comparaison(int *tab1, int *tab2) {
    if (tab1[0] != tab2[0]) {
        // si tailles differentes, c'est mort
        return 0;
    }
    for (int i = 1; i <= tab1[0]; i++) {
        // si on trouve un element qui est different, c'est mort
        if (tab1[i] != tab2[i]) {
            return 0;
        }
    }
    // sinon ok
    return 1;
}

/*
    Verifie si nos fonctions de decoupage et de concatenation fonctionnent
    correcement : decoupe puis recolle un tableau et compare avec celui de base
*/
void verification_decoupage(int *tab, int index) {
    int *p1;
    int *p2;
    int *recolle;
    // decouper tab et mettre les deux morceaux dans p1 et p2
    decoupage(tab, index, &p1, &p2);
    // recoller les morceaux dans recolle
    recolle = concatenation(p1, p2);

    printf("verification_decoupage(");
    affichage(tab);
    printf(", %d ) => comparaison(...) == %d\n", index, comparaison(tab, recolle));

    free(p1);
    free(p2);
    free(recolle);
}

/* PARTIE 4 - REPRESENTATION AVEC STRUCTURE */

/*
    Convertit un tableau dimensionne en une structure TabDim
*/
TabDim *conversion(int *tab) {
    // allouer une structure
    TabDim *tab_s = (TabDim *) malloc(sizeof(TabDim));

    // renseigner la taille
    tab_s->dim = tab[0];

    // allouer un tableau pour stocker les elements
    tab_s->tab = (int *)malloc(tab_s->dim * sizeof(int));
    // copier les elements
    for (int i = 0; i < tab_s->dim; i++) {
        tab_s->tab[i] = tab[i+1];
    }

    // renvoyer le pointeur de la structure
    return tab_s;
}

/*
    Affiche le contenu d'une structure TabDim de facon lisible
*/
void affichage_TabDim(TabDim *T) {
    printf("{ dim = %d; tab = [", T->dim);
    for (int i = 0; i<T->dim; i++) {
        printf(" %d", T->tab[i]);
    }
    printf(" ]}\n");
}

void destruction_TabDim(TabDim *T) {
    free(T->tab);
    free(T);
}

/*
    Fonction de test : execute toutes les fonctions ci-dessus et affiche
    leurs resultat
*/
void tests() {
    /* VARIABLES LOCALES */

    // tableaux de base
    int exemple1[6] = {5,42,42,42,42,42};
    int exemple2[1] = {0};
    // Contiendront des tableaux alloues dynamiquement
    int *ex_t0;
    int *ex_t1;
    int *ex_t2;
    int *ex_t3;
    int *ex_t4;
    int *ex_t5;
    // Contiendront les copies des tableaux de base
    int *cp_1;
    int *cp_2;
    // Exemples pour tester la concatenation
    int un[2] = {1, 1};
    int deux[3] = {2, 2, 2};
    int *res_ccat;
    // Contiendront les deux sous-tableaux rendus par la decoupe
    int *p1;
    int *p2;
    // exemple en plus pour la comparaison
    int troistroistrois[6] = {5, 333, 333, 333, 333, 333};
    // Servira a tester la conversion tableau->TabDim
    TabDim *T;
    

    /* TEST AFFICHAGE */
    printf("== affichage(exemples) ==\n");
    affichage(exemple1);
    printf(", ");
    affichage(exemple2);
    printf("\n");

    /* TEST REMPLISSAGE */
    printf("== remplissage(exemples,42) ==\n");
    remplissage(exemple1, 42);
    remplissage(exemple2, 42);
    affichage(exemple1);
    printf(", ");
    affichage(exemple2);
    printf("\n");

    /* TEST REMPLISSAGE_SEQUENCE */
    printf("== remplissage_sequence(exemples,42) ==\n");
    remplissage_sequence(exemple1, 42);
    remplissage_sequence(exemple2, 42);
    affichage(exemple1);
    printf(", ");
    affichage(exemple2);
    printf("\n");

    /* TEST SOMME */
    printf("== somme(exemples) ==\n");
    printf("somme1 == %d , somme2 == %d\n", somme(exemple1), somme(exemple2));

    /* TEST CREATION */
    printf("== creation(0..5) ==\n");
    ex_t0 = creation(0);
    ex_t1 = creation(1);
    ex_t2 = creation(2);
    ex_t3 = creation(3);
    ex_t4 = creation(4);
    ex_t5 = creation(5);
    affichage(ex_t0);
    printf("\n");
    affichage(ex_t1);
    printf("\n");
    affichage(ex_t2);
    printf("\n");
    affichage(ex_t3);
    printf("\n");
    affichage(ex_t4);
    printf("\n");
    affichage(ex_t5);
    printf("\n");

    /* TEST DESTRUCTION - (lancer Valgrind pour voir si ca a bien ete fait)*/
    destruction(ex_t0);
    destruction(ex_t1);
    destruction(ex_t2);
    destruction(ex_t3);
    destruction(ex_t4);
    destruction(ex_t5);

    /* TEST VERIFICATION_SOMME_ENTIERS */
    printf("== verification_somme_entiers(38..42) ==\n");
    verification_somme_entiers(38);
    verification_somme_entiers(39);
    verification_somme_entiers(40);
    verification_somme_entiers(41);
    verification_somme_entiers(42);

    /* TEST COPIE */
    printf("== copie(exemples) ==\n");
    cp_1 = copie(exemple1);
    cp_2 = copie(exemple2);
    affichage(cp_1);
    printf(", ");
    affichage(cp_2);
    printf("\n");

    printf("== remplissage(copie1,7) et affichage(copie1,exemple1) ==\n");
    remplissage(cp_1, 7);
    affichage(cp_1);
    printf(", ");
    affichage(exemple1);
    printf("\n");

    printf("== remplissage_sequence(exemple1,13) et affichage(copie1,exemple1) ==\n");
    remplissage_sequence(exemple1, 13);
    affichage(cp_1);
    printf(", ");
    affichage(exemple1);
    printf("\n");

    /* TEST DESTRUCTION - (lancer Valgrind pour voir si ca a bien ete fait)*/
    destruction(cp_1);
    destruction(cp_2);


    /* TEST CONCATENATION */
    printf("== concatenation([1], [2,2]) et concatenation([2,2], [1]) ==\n");
    res_ccat = concatenation(un, deux);
    affichage(res_ccat);
    printf("\n");
    destruction(res_ccat);

    res_ccat = concatenation(deux, un);
    affichage(res_ccat);
    destruction(res_ccat);

    printf("== concatenation(exemple1, exemple2) et concatenation(exemple2, exemple1) ==\n");
    res_ccat = concatenation(exemple1, exemple2);
    affichage(res_ccat);
    printf("\n");
    destruction(res_ccat);

    res_ccat = concatenation(exemple2, exemple1);
    affichage(res_ccat);
    printf("\n");
    destruction(res_ccat);

    /* TEST DECOUPEAGE */
    printf("== decoupage(exemple1,0..6) ==\n");
    // decoupage index 0
    decoupage(exemple1, 0, &p1, &p2);

    printf("decoupage(");
    affichage(exemple1);
    printf(", 0) =>");
    affichage(p1);
    printf(", ");
    affichage(p2);
    printf("\n");
    destruction(p1);
    destruction(p2);

    // decoupage index 1
    decoupage(exemple1, 1, &p1, &p2);

    printf("decoupage(");
    affichage(exemple1);
    printf(", 1) =>");
    affichage(p1);
    printf(", ");
    affichage(p2);
    printf("\n");
    destruction(p1);
    destruction(p2);

    decoupage(exemple1, 2, &p1, &p2);

    // decoupage index 2
    printf("decoupage(");
    affichage(exemple1);
    printf(", 2) =>");
    affichage(p1);
    printf(", ");
    affichage(p2);
    printf("\n");
    destruction(p1);
    destruction(p2);

    decoupage(exemple1, 3, &p1, &p2);

    printf("decoupage(");
    affichage(exemple1);
    printf(", 3) =>");
    affichage(p1);
    printf(", ");
    affichage(p2);
    printf("\n");
    destruction(p1);
    destruction(p2);

    decoupage(exemple1, 4, &p1, &p2);

    printf("decoupage(");
    affichage(exemple1);
    printf(", 4) =>");
    affichage(p1);
    printf(", ");
    affichage(p2);
    printf("\n");
    destruction(p1);
    destruction(p2);

    decoupage(exemple1, 5, &p1, &p2);

    printf("decoupage(");
    affichage(exemple1);
    printf(", 5) =>");
    affichage(p1);
    printf(", ");
    affichage(p2);
    printf("\n");
    destruction(p1);
    destruction(p2);

    /* TEST COMPARAISON */
    printf("== comparaisons ==\n");

    printf("comparaison(");
    affichage(exemple1);
    printf(", ");
    affichage(exemple2);
    printf(") == %d\n", comparaison(exemple1, exemple2));

    printf("comparaison(");
    affichage(exemple1);
    printf(", ");
    affichage(troistroistrois);
    printf(") == %d\n", comparaison(exemple1, troistroistrois));

    printf("comparaison(");
    affichage(exemple1);
    printf(", ");
    affichage(exemple1);
    printf(") == %d\n", comparaison(exemple1, exemple1));

    /* TEST VERIFICATION_DECOUPAGE */
    printf("== verification_decoupage ==\n");

    verification_decoupage(exemple1, 0);
    verification_decoupage(exemple1, 1);
    verification_decoupage(exemple1, 2);
    verification_decoupage(exemple1, 3);
    verification_decoupage(exemple1, 4);
    verification_decoupage(exemple1, 5);

    /* TEST CONVERSION TAB->STRUCT */
    printf("== conversion int*->TabDim ==\n");
    T = conversion(exemple1);
    printf("conversion(");
    affichage(exemple1);
    printf(") = ");
    affichage_TabDim(T);
    destruction_TabDim(T);

    T = conversion(exemple2);
    printf("conversion(");
    affichage(exemple2);
    printf(") = ");
    affichage_TabDim(T);
    destruction_TabDim(T);

    T = conversion(troistroistrois);
    printf("conversion(");
    affichage(troistroistrois);
    printf(") = ");
    affichage_TabDim(T);
    destruction_TabDim(T);
}

int main() {
    tests();
    return 0;
}
