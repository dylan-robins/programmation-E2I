#include <stdio.h>
#include <stdlib.h>

// Pythonic int list typedef
typedef struct {
    int *t;
    long len;
    long capacity;
} list;

// initialises a list
list *initList(long capacity) {
    list *l = (list *) malloc(sizeof(list));
    l->t = (int *) malloc(capacity * sizeof(int));
    l->capacity = capacity;
    l->len = 0;
    return l;
}

// frees the memory used by a list
void deleteList(list *l) {
    free(l->t);
    free(l);
}

// appends an int to a list, realloc'ing if necessary
int append(list *l, int n) {
    if (l->len >= l->capacity) {
        l = realloc(l, 2*l->capacity);
        if (l == NULL) {
            // error : out of memory
            return 1;
        }
    }
    l->t[l->len] = n;
    l->len++;
    return 0;
}

// fills a list with as many ints as the user wants
int readList(list *l) {
    int tmp;
    while (scanf("%d", &tmp) != 0) {
        if (append(l, tmp)) {
            // clear stdin
            while (getchar() != '\n') {}

            // return error appending to list
            return 1;
        }
    }
    // clear stdin
    while (getchar() != '\n') {}
    return 0;
}

// recursive function implementing dichotomic search
long findInListRec(list* l, long min, long max, int n) {
    long m = -1;
    long M = -1;

    if (l->t[min] == n) {
        return min;
    } else if (min >= max) {
        // reached end but not found
        return -1;
    } else {
        // look in lower half of the list
        m = findInListRec(l, min, (max+min)/2, n);
        if (m != -1) {return m;}

        // look in upper half of the list
        M = findInListRec(l, (min+max)/2+1, max, n);
        if (M != -1) {return M;}

        return -1;
    }
}

// user-friendly function for calling the dichotomic search
long findInList(list *l, int n) {
    return findInListRec(l, 0, l->len-1, n);
}

int main(void) {
    list *l = initList(10); // start off with a size of 10
    int n;                  // int we'll be looking for
    long index;

    printf("Rentrez une liste d'entiers séparés par des espaces :\n>>>");
    readList(l);

    do {
        printf("Entrez un entier à rechercher dans la liste :\n>>>");
    } while (scanf("%d", &n) != 1);

    index = findInList(l, n);
    if (index >= 0) {
        printf("%d est au rang %ld de la liste.\n", n, index);
    } else {
        printf("%d n'est pas dans la liste.\n", n);
    }

    deleteList(l);
    return 0;
}