#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "sort.h"

list_t *list(size_t n) {
    list_t *new_list = (list_t *) malloc(sizeof(list_t));
    new_list->len = n;
    new_list->capacity = n;
    new_list->t = (T *) malloc(n * sizeof(T));
    return new_list;
}

list_t *list_from_arr(const T* l, size_t n) {
    // construct a new list
    list_t *new_list = list(n);
    // fill it with items from the const array
    memcpy(new_list->t, l, n * sizeof(T));
    return new_list;
}

void delete(list_t *l) {
    free(l->t);
    free(l);
}

inline void swap(list_t *list, size_t i, size_t j) {
    T tmp = list->t[i];
    list->t[i] = list->t[j];
    list->t[j] = tmp;
}

void insert(list_t *list, T new_elem, size_t n) {
    // incr size of list & extend allocated area if necessary
    list->len++;
    if (list->len > list->capacity) {
        list->t = realloc(list->t, list->capacity*2*sizeof(T));
    }
    // move after index n everything right
    for (int i = list->len-1; i > n; i--) {
        swap(list, i-1, i);
    }

    // insert new element in newly freed slot
    list->t[n] = new_elem;

}

T pop(list_t *list, size_t i) {
    T tmp = list->t[i];
    list->len--;
    for (int j = i; j < list->len; j++) {
        list->t[j] = list->t[j+1];
    }
    return tmp;
}

void display(list_t *tab) {
    printf("[ ");
    for (int i = 0; i < tab->len; i++) {
        printf("%d ", tab->t[i]);
    }
    printf("]");
}

void bubbleSort(list_t *tab, bool debug) {
    int sorted = 0;
    int iteration = 0;

    if (debug) {
        printf("################\n");
        printf("# Bubble sort: #\n");
        printf("################\n");

        printf("Initial list:\t\t\t\t");
        display(tab);
        printf("\n");
    
    }

    while (!sorted) {
        if (debug) {
            printf("    Iteration %d: \t\t\t", iteration);
            display(tab);
            printf("\n");
        }

        sorted = 1; // stays 1 if we loop right through without moving anything
        for (int i = 1; i < tab->len-iteration; i++) {
            if (tab->t[i-1] > tab->t[i]) {
                if (debug) printf("        Swapping positions %d and %d: \t", tab->t[i], tab->t[i-1]);

                swap(tab, i, i-1);
                
                if (debug) {
                    display(tab);
                    printf("\n");
                }
                sorted = 0;
            }
        }
        iteration++;
    }
    
    if (debug) {
        printf("\nSorted list:");
        display(tab);
        printf("\n");
    }
}

void move(list_t *list, size_t init_pos, size_t dest_pos) {
    if (init_pos > dest_pos) {
        for (size_t i = init_pos; i > dest_pos; i--) {
            swap(list, i-1, i);
        }
    } else {
        for (size_t i = init_pos; i > dest_pos; i++) {
            swap(list, i, i+1);
        }
    }
}

void insertionSort(list_t *tab, bool debug) {
    size_t j=0;

    if (debug) {
        printf("###################\n");
        printf("# Insertion sort: #\n");
        printf("###################\n");

        printf("Initial list:");
        display(tab);
        printf("\n");
    }

    for (size_t i = 1; i < tab->len; i++) {
        // find index in sorted section of list at which to insert i-th element
        j = 0;
        while (tab->t[j] < tab->t[i]) {
            j++;
        }
        // insert i-th element at correct index of list
        if (i != j) {
            if (debug) {
                printf("    Iteration %ld:  inserting element %d at index %ld\t", i, tab->t[i], j);
                display(tab);
            }

            move(tab, i, j);

            if (debug) {
                printf(" -> ");
                display(tab);
                printf("\n");
            }
        } else if (debug) {
            printf("    Iteration %ld:  element %d in correct place     \t", i, tab->t[i]);
            display(tab);
            printf(" -> ");
            display(tab);
            printf("\n");
        }
    }

    if (debug) {
        printf("\nSorted list:");
        display(tab);
        printf("\n");
    }
}

void quicksort_rec(list_t *tab, long start, long end, int up_indent, bool debug) {
    long pivot = start;
    char *indent = NULL;
    char *pad = NULL;

    if (debug) {
        // build indent string
        indent = malloc(up_indent+5);
        for (int i = 0; i < up_indent+4; i++) {
            indent[i] = ' ';
        }
        indent[up_indent+4] = 0;

        // build padding string
        pad = malloc(25-up_indent);
        for (int i = 0; i < 25-up_indent-1; i++) {
            pad[i] = ' ';
        }
        pad[25-up_indent-1] = 0;

        printf("%sSorting list: start %ld - end %ld - ", indent, start, end);
    }

    if (start >= end) {
        if (debug) {
            printf("nothing to do\n");
            free(indent);
            free(pad);
        }
        return;
    }

    for (long i = start+1; i <= end; i++) {
        // if i-th element < pivot element, then insert it at the start of the list
        // this ensures all elements smaller than the pivot elem will be before the pivot element
        if (tab->t[i] < tab->t[pivot]) {
            move(tab, i, start);
            pivot++; // pivot element will have shifted right by 1
        }
    }
    if (debug) {
        printf("pivot %ld - split list%s\t", pivot, pad);
        display(tab);
        printf("\n");
    }

    quicksort_rec(tab, start, pivot-1, up_indent+4, debug);
    quicksort_rec(tab, pivot+1, end, up_indent+4, debug);
    
    if (debug) {
        printf("%sDone. Sorted list:                                          %s", indent, pad);
        display(tab);
        printf("\n");
        
        free(indent);
        free(pad);
    }
}

void quickSort(list_t *tab, bool debug) {
    if (debug) {
        printf("###############\n");
        printf("# Quick sort: #\n");
        printf("###############\n");

        printf("Initial list:");
        display(tab);
        printf("\n");
    }

    // call recursive function on whole list
    quicksort_rec(tab, 0, tab->len-1, 0, debug);

    if (debug) {
        printf("\nSorted list:");
        display(tab);
        printf("\n");
    }
}