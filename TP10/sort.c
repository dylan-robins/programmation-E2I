#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Pseudo-polymorphism */
#define T int

typedef struct {
    T *t;
    size_t capacity;
    size_t len;
} list_t;

list_t *list(const T* l, size_t n) {
    list_t *new_list = (list_t *) malloc(n * sizeof(T));
    new_list->len = n;
    new_list->capacity = n;
    new_list->t = (T *) malloc(n * sizeof(int));
    
    memcpy(new_list->t, l, n * sizeof(int));
    
    return new_list;
}

void delete(list_t *l) {
    free(l->t);
    free(l);
}

void swap(list_t *list, size_t i, size_t j) {
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
    for (int i = list->len; i > n; i--) {
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

void bubbleSort(list_t *tab) {
    int sorted = 0;
    int iteration = 0;

    printf("################\n");
    printf("# Bubble sort: #\n");
    printf("################\n");

    printf("Initial list:\t\t\t\t");
    display(tab);
    printf("\n");
    
    while (!sorted) {
        printf("    Iteration %d: \t\t\t", iteration);
        display(tab);
        printf("\n");

        sorted = 1; // stays 1 if we loop right through without moving anything
        for (int i = 1; i < tab->len-iteration; i++) {
            if (tab->t[i-1] > tab->t[i]) {
                printf("        Swapping positions %d and %d: \t", tab->t[i], tab->t[i-1]);

                swap(tab, i, i-1);
                
                display(tab);
                printf("\n");
                sorted = 0;
            }
        }
        iteration++;
    }
    
    printf("\nSorted list:");
    display(tab);
    printf("\n");
}

void insertionSort(list_t *tab) {
    size_t j=0;

    printf("###################\n");
    printf("# Insertion sort: #\n");
    printf("###################\n");

    printf("Initial list:");
    display(tab);
    printf("\n");

    for (size_t i = 1; i < tab->len; i++) {
        // find index in sorted section of list at which to insert i-th element
        j = 0;
        while (tab->t[j] < tab->t[i]) {
            j++;
        }
        // insert i-th element at correct index of list
        if (i != j) {
            printf("    Iteration %ld:  inserting element %d at index %ld\t", i, tab->t[i], j);
            display(tab);
            insert(tab, pop(tab, i), j);
            printf(" -> ");
            display(tab);
            printf("\n");
        } else {
            printf("    Iteration %ld:  element %d in correct place     \t", i, tab->t[i]);
            display(tab);
            printf(" -> ");
            display(tab);
            printf("\n");
        }
    }

    printf("\nSorted list:");
    display(tab);
    printf("\n");
}

void quicksort_rec(list_t *tab, long start, long end, int up_indent) {
    long pivot = start;
    // build indent string
    char *indent = malloc(up_indent+5);
    for (int i = 0; i < up_indent+4; i++) {
        indent[i] = ' ';
    }
    indent[up_indent+5] = 0;

    // build padding string
    char *pad = malloc(25-up_indent);
    for (int i = 0; i < 25-up_indent-1; i++) {
        pad[i] = ' ';
    }
    pad[25-up_indent] = 0;

    printf("%sSorting list: start %ld - end %ld - ", indent, start, end);
    if (start >= end) {
        printf("nothing to do\n");
        return;
    }

    for (long i = start+1; i <= end; i++) {
        // if i-th element < pivot element, then insert it at the start of the list
        // this ensures all elements smaller than the pivot elem will be before the pivot element
        if (tab->t[i] < tab->t[pivot]) {
            T tmp = pop(tab, i);
            insert(tab, tmp, start);
            pivot++; // pivot element will have shifted right by 1
        }
    }
    printf("pivot %ld - split list%s\t", pivot, pad);
    display(tab);
    printf("\n");

    quicksort_rec(tab, start, pivot-1, up_indent+4);
    quicksort_rec(tab, pivot+1, end, up_indent+4);
    
    printf("%sDone. Sorted list:                                          %s", indent, pad);
    display(tab);
    printf("\n");
    
    free(indent);
}

void quickSort(list_t *tab) {
    printf("###############\n");
    printf("# Quick sort: #\n");
    printf("###############\n");

    printf("Initial list:");
    display(tab);
    printf("\n");

    // call recursive function on whole list
    quicksort_rec(tab, 0, tab->len-1, 0);

    printf("\nSorted list:");
    display(tab);
    printf("\n");
}

int main() {
    list_t *tab = list((const int []){5, 10, 2, 9, 1, 79, 2, 8, 1}, 9);
    bubbleSort(tab);
    delete(tab);

    tab = list((const int []){5, 10, 2, 9, 1, 79, 2, 8, 1}, 9);
    insertionSort(tab);
    delete(tab);

    tab = list((const int []){5, 10, 2, 9, 1, 79, 2, 8, 1}, 9);
    quickSort(tab);
    delete(tab);
    return 0;
}