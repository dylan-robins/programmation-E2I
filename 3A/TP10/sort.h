#ifndef __sort_h__
#define __sort_h__
/* Pseudo-polymorphism */
#define T int
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    T *t;
    size_t capacity;
    size_t len;
} list_t;


list_t *list(size_t n);
list_t *list_from_arr(const T* l, size_t n);
void delete(list_t *l);
void swap(list_t *list, size_t i, size_t j);
void insert(list_t *list, T new_elem, size_t n);
T pop(list_t *list, size_t i);
void display(list_t *tab);
void bubbleSort(list_t *tab, bool debug);
void insertionSort(list_t *tab, bool debug);
void quicksort_rec(list_t *tab, long start, long end, int up_indent, bool debug);
void quickSort(list_t *tab, bool debug);

#endif