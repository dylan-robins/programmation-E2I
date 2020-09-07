#include <stdio.h>
#include <stdlib.h>

typedef struct MAILLON {
    int info;
    int parcourue; // sert à la destruction, non utilisée dans le reste
    struct MAILLON *suivant;
} MAILLON;

MAILLON *nouveau_maillon(int info) {
    // créé un maillon qui va continuer à exister une fois sorti de la fonction
    MAILLON *mon_maillon = (MAILLON *)malloc(sizeof(MAILLON));

    // remplir les champs de la structure créée
    mon_maillon->info = info;
    mon_maillon->suivant = NULL;
    mon_maillon->parcourue = 0; // sert à la destruction, non utilisée ailleurs

    // renvoyer l'adresse du nouveau maillon
    return mon_maillon;
}

void print_list(const char *list_name, MAILLON *head) {
    int nb_elems = 0;

    MAILLON *courant = head;
    
    printf("%s: ", list_name);
    while (courant != NULL) {
        nb_elems++;
        printf("->%d", courant->info);
        courant = courant->suivant;

        // protection liste infinie
        if (nb_elems > 15) {
            printf("...");
            break;
        }
    }
    printf("\n");
}

void print_list_rec(MAILLON *list) {
    if (list != NULL) {
        printf("%d", list->info);
        print_list_rec(list->suivant);
    }
}

void print_list_rec_rev(MAILLON *list) {
    if (list != NULL) {
        print_list_rec(list->suivant);
        printf("%d", list->info);
    }
}

MAILLON *arr_to_list(const int arr[], const size_t len) {
    MAILLON *tete = nouveau_maillon(arr[0]);
    MAILLON *courant = tete;
    for (size_t i = 1; i < len; i++) {
        courant->suivant = nouveau_maillon(arr[i]);
        courant = courant->suivant;
    }
    return tete;
}

void inserer_maillon(MAILLON *precedent, int val) {
    // enregistrer la fin de la liste pour pouvoir la recoller après l'élément inséré
    MAILLON *suivant = precedent->suivant;
    // insérer le nouvel élément
    precedent->suivant = nouveau_maillon(val);
    // recoller la fin de la liste
    precedent->suivant->suivant = suivant;
}


// modifies list in place, or creates new one if empty and returns ptr to head
MAILLON *push_back(MAILLON *list, int new_val) {
    MAILLON *courant = list;
    if (list == NULL) {
        return nouveau_maillon(new_val);
    }
    // move ptr to end of list
    while (courant->suivant != NULL) {
        courant = courant->suivant;
    }
    courant->suivant = nouveau_maillon(new_val);
    return list;
}

MAILLON *push_front(MAILLON *list, int new_val) {
    MAILLON *new_list = nouveau_maillon(new_val);
    new_list->suivant = list;
    return new_list;
}

MAILLON *pop_front(MAILLON **list) {
    MAILLON *first = *list;
    *list = (*list)->suivant;
    return first;
}

MAILLON *pop_back(MAILLON *list) {
    MAILLON *courant = list;
    MAILLON *precedent = NULL;
    while (courant->suivant != NULL) {
        precedent = courant;
        courant = courant->suivant;
    }
    precedent->suivant = NULL;
    return courant;
}

MAILLON *copie_list(MAILLON *list) {
    MAILLON *new_list = nouveau_maillon(list->info);
    MAILLON *courant = list;
    MAILLON *new_courant = new_list;
    while (courant->suivant != NULL) {
        courant = courant->suivant;
        new_courant->suivant = nouveau_maillon(courant->info);
        new_courant = new_courant->suivant;
    }
    return new_list;
}

void supprimer_maillon(MAILLON *precedent) {
    // si l'élément qu'on supprime existe
    if (precedent->suivant != NULL) {
        MAILLON *suivant = precedent->suivant->suivant;
        // recoller la fin de la liste (ou NULL s'il n'y a rien à la suite)
        precedent->suivant = suivant;
        // supprimer l'élément
        free(precedent->suivant);
    }
}

int taille_liste(MAILLON *list) {
    MAILLON *courant = list;
    int i = 0;
    while (courant != NULL) {
        courant = courant->suivant;
        i++;
    }
    return i;
}

void detruire_liste(MAILLON *list) {
    if (list != NULL && list->parcourue == 0) {
        list->parcourue = 1;
        detruire_liste(list->suivant);
        free(list);
    }
}

int main() {
    ///////////////////////////////////////////////////////////////////////////
    // QUESTION 9
    ///////////////////////////////////////////////////////////////////////////
    MAILLON *l1 = arr_to_list((const int []){2,3,5,4,1}, 5);
    print_list("l1", l1);

    MAILLON *l2 = arr_to_list((const int []){2,3,5}, 3);
    print_list("l2", l2);
    
    MAILLON *l3 = arr_to_list((const int []){1,4}, 2);
    print_list("l3", l3);
    
    MAILLON *l4 = arr_to_list((const int []){2,1,3,4}, 4);
    print_list("l4", l4);
    
    MAILLON *l5 = arr_to_list((const int []){5,1,3,4}, 4);
    print_list("l5", l5);

    MAILLON *l6 = arr_to_list((const int []){2,3,5,4,1}, 5);

    // trouver la fin de l6
    MAILLON *courant = l6;
    while (courant->suivant != NULL) {
        courant = courant->suivant;
    }
    // remettre la fin sur le 3e élément de la liste (5)
    courant->suivant = l6->suivant->suivant;

    print_list("l6", l6);

    ///////////////////////////////////////////////////////////////////////////
    // QUESTION 10
    ///////////////////////////////////////////////////////////////////////////
    MAILLON *l7 = arr_to_list((const int []){1,3,5,4}, 4);
    print_list("l7", l7);

    MAILLON *l7_copied = copie_list(l7);
    print_list("l7_copied", l7_copied);

    detruire_liste(l1);
    detruire_liste(l2);
    detruire_liste(l3);
    detruire_liste(l4);
    detruire_liste(l5);
    detruire_liste(l6);
    detruire_liste(l7);
    detruire_liste(l7_copied);

    return 0;
}