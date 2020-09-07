#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************/
/*                                 Question 1                                */
/*****************************************************************************/

typedef struct node_s {
    int elem_number;
    int value;
    struct node_s *next;
} node_t;

/*****************************************************************************/
/*                                 Question 2                                */
/*****************************************************************************/

/* Pour connaitre le nombre d'elements dans la liste, on peut parcourir la
 * liste tant que le numéro de l'élément courant est supérieur au précédent.
 * Etant donné que la liste est numérotée dans l'ordre croissant une fois que
 * l'on retombe sur l"élément numéroté 1 on sait que l'on est revenu au début.
 */

/*****************************************************************************/
/*                                 Question 3                                */
/*****************************************************************************/
node_t *init(int numbers[], size_t nb_numbers) {
    node_t *list = NULL;
    node_t *current = NULL;

    // Si le tableau est vide, ne rien faire
    if (nb_numbers <= 0) {
        return NULL;
    }

    // Créer le premier noeud de la liste
    list = (node_t *)malloc(sizeof(node_t));
    list->value = numbers[0];
    list->elem_number = 1;

    // Construire tous les elements suivants
    current = list;
    for (int i = 1; i < nb_numbers; i++) {
        current->next = (node_t *)malloc(sizeof(node_t));
        current = current->next;
        current->value = numbers[i];
        current->elem_number = i+1; // +1 car on compte à partir de 1
    }

    // Close the list
    current->next = list;

    return list;
}

// Par souci de propreté
void delete(node_t *list) {
    if (list->elem_number <= list->next->elem_number) {
        delete(list->next);
    }
    free(list);
}

/*****************************************************************************/
/*                                 Question 4                                */
/*****************************************************************************/
void display_list(node_t *list) {
    int prev_elem = 0; // la numerotation des noeuds commence à 1
    
    while (list->elem_number > prev_elem) {
        prev_elem = list->elem_number;
        printf("Element %d: %d\n", list->elem_number, list->value);
        list = list->next;
    }
}

/*****************************************************************************/
/*                                 Question 6                                */
/*****************************************************************************/
int get_nth_value(node_t *list, int n) {
    for (int i = 0; i < n; i++) {
        list = list->next;
    }
    return list->value;
}

/*****************************************************************************/
/*                                    Main                                   */
/*****************************************************************************/
int main(void) {
    // Question 5
    int nb[] = {15, 28, 12};
    int n = 3;
    node_t *list = init(nb, n);
    display_list(list);

    // Question 6
    // Demander un numéro à l'utilisateur
    char line[256];
    int i;
    do {
        printf("Entrez le numero du noeud que vous voulez afficher (0 < i < %d) : \n>>> ", n);
        fgets(line, 256, stdin);
    } while ((sscanf(line, "%d", &i) != 1) || (i < 0) || (n <= i));
    // Afficher le nombre obtenu + la valeur correspondante
    printf("Valeur du %d+%d-ieme noeud: %d\n", n, i, get_nth_value(list, n+i));

    delete(list);
    return 0;
}

/*****************************************************************************/
/*                                 Question 7                                */
/*****************************************************************************/

/* Autres options pour calculer la longueur de la liste après construction:
 *  - Construire un tableau trié avec les valeurs déjà rencontrées, et comparer
 *    à chaque noeud parcouru si la valeur est dans le tableau
 *      -> C'est long et inutilement compliqué, et a aucun avantage par rapport
 *         à la solution utilisée. Ne marche pas si on veut avoir plusieurs
 *         noeuds qui ont la même valeur.
 *  - Même genre de chose mais en stockant soit le numéro de l'élement soit
 *    l'addresse de la structure
 *      -> même problème, trop long et compliqué pour rien. Par contre permet
 *         d'avoir plusieurs noeuds avec la même valeur
 *  - Si l'on peut rajouter des choses au moment de la construction, on peut
 *    utiliser une structure faisant office d'en-tête contenant le pointeur du
 *    premier noeud et un entier représentant la longueur de la liste
 *      -> Mieux, pas besoin de reparcourir la liste à chaque fois que l'on
 *         veut sa longueur, mais nécessite d'adapter toutes les fonctions qui
 *         manipulent la liste pour aussi mettre à jour l'en-tête
 *         (ajout: +1, supression: -1...)
 *         Autre avantage: permet de représenter autrement qu'avec un pointeur
 *         NULL la liste vide.
 *         Dernier avantage: permet de rajouter facilement d'autres metadonnées
 *         à l'en-tête.
 */