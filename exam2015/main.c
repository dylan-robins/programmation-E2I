#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct child_s {
    char name[20];
    uint8_t number;
    struct child_s *next;
} child_t;

child_t *init(char names[][20], size_t nb_names) {
    child_t *circle = NULL;
    child_t *current = NULL;

    // If there aren't any kids, don't do anything
    if (nb_names <= 0) {
        return NULL;
    }

    // Create first child of circle
    circle = (child_t *)malloc(sizeof(child_t));
    strcpy(circle->name, names[0]);
    circle->number = 0;

    // Loop over all following ones adding them to the circle
    current = circle;
    for (int i = 1; i < nb_names; i++) {
        current->next = (child_t *)malloc(sizeof(child_t));
        current = current->next;
        strcpy(current->name, names[i]);
        current->number = i;
    }

    // Close the circle
    current->next = circle;

    return circle;
}

void display_circle(child_t *circle, uint8_t nb_children) {
    uint8_t nb_displayed = 0;
    // Don't go over the same ones multiple times...
    while (nb_displayed < nb_children) {
        printf("Child %d: %s\n", circle->number, circle->name);
        circle = circle->next;
        nb_displayed++;
    }
}

child_t *delete_nth(child_t *circle, uint8_t n) {
    uint8_t i = 0;
    child_t *tmp = NULL;

    while (i < n - 1) {
        circle = circle->next;
        i++;
    }

    tmp = circle->next;
    printf("Child %d: %s sings\n", tmp->number, tmp->name);
    circle->next = tmp->next;
    if (circle == tmp) {
        free(tmp);
        return NULL;
    } else {
        free(tmp);
        return circle->next;
    }
}

int main(void) {
    char names[12][20] = {"Claire",  "Karine",    "Paul",  "Carole",
                          "Jacques", "Christine", "Alain", "Anne",
                          "Andre",   "Beatrice",  "Denis", "Laurence"};

    child_t *circle = init(names, 12);
    display_circle(circle, 12);

    printf("_________________\n");
    circle = delete_nth(circle, 7);
    while (circle != NULL) {
        circle = delete_nth(circle, 6);
    }
    return 0;
}