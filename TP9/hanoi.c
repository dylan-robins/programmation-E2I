#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *t;
    size_t capacity;    // number of disks the peg can hold (= length of t)
    size_t nb;          // number of disks on the peg
    char label;         // label of the peg
} peg;

void init(peg *p, size_t capacity, size_t nb, char label) {
    p->t = (int *) malloc(capacity * sizeof(int));
    p->capacity = capacity;
    p->nb = nb;
    p->label = label;

    // populate peg in reverse order (largest at bottom)
    for (int i = 0; i < nb; i++) {
        p->t[i] = nb-i;
    }
}

void destroy(peg *p) {
    free(p->t);
}

// adds the disk of size n onto to the p peg
int append(peg *p, int n) {
    if (p->nb+1 <= p->capacity) {
        p->t[p->nb] = n;
        p->nb++;
        return 1;
    } else {
        // peg is full
        return 0;
    }
}

// removes the disk on top of the p peg and returns it
int pop(peg *p) {
    if (p->nb > 0) {
        p->nb--;
        return p->t[p->nb];
    } else {
        // peg is already empty
        return -1;
    }
}

// finds and returns the peg that has the correct label amongst p1, p2 and p3
// if none have the correct label, returns a null
peg *findWithLabel(peg *p1, peg *p2, peg *p3, char label) {
    if (p1->label == label) {
        return p1;
    } else if (p2->label == label) {
        return p2;
    } else if (p3->label == label) {
        return p3;
    } else {
        return NULL;
    }
}

//displays the pegs in order
void display(peg *p1, peg *p2, peg *p3) {
    peg *A = findWithLabel(p1, p2, p3, 'A');
    peg *B = findWithLabel(p1, p2, p3, 'B');
    peg *C = findWithLabel(p1, p2, p3, 'C');
    
    printf("A: ");
    for (size_t i = 0; i < A->nb; i++) {
        printf("%2d ", A->t[i]);
    }
    for (size_t i = A->nb; i < A->capacity; i++) {
        printf("__ ");
    }
    printf("\n");

    printf("B: ");
    for (size_t i = 0; i < B->nb; i++) {
        printf("%2d ", B->t[i]);
    }
    for (size_t i = B->nb; i < B->capacity; i++) {
        printf("__ ");
    }
    printf("\n");

    printf("C: ");
    for (size_t i = 0; i < C->nb; i++) {
        printf("%2d ", C->t[i]);
    }
    for (size_t i = C->nb; i < C->capacity; i++) {
        printf("__ ");
    }
    printf("\n");

}

void hanoi(peg *source, peg *target, peg *spare, int n) {
    // if n == 0, do nothing
    if (n != 0) {
        // move n-1 disks from source to spare
        hanoi(source, spare, target, n-1);
        // move nth disk to target
        int tmp = pop(source);
        if (tmp == -1) {printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ERROR1\nPeg %c is already empty!\n", source->label);}
        tmp = append(target, tmp);
        if (tmp == 0) {printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ERROR2\nPeg %c is overfilled!\n", target->label);}
        printf("__________\n");
        display(source, spare, target);
        // move n-1 disks from spare to target
        hanoi(spare, target, source, n-1);
    }
}

int main(int argc, char **argv) {
    peg peg1;
    peg peg2;
    peg peg3;
    size_t n;

    if (argc == 1) {
        // default: 3
        printf("Initializing Towers of Hanoï with default size of 3:\n");
        n = 3;
    } else if (argc == 2 && sscanf(argv[1], "%ld", &n) == 1) {
        printf("Initializing Towers of Hanoï with size of %ld:\n", n);
    } else {
        printf("Usage: %s [peg size]\n", argv[0]);
        return 1;
    }

    // initialize pegs
    init(&peg1, n, n, 'A');
    init(&peg2, n, 0, 'B');
    init(&peg3, n, 0, 'C');
    
    printf("Initial state:\n");
    display(&peg1, &peg2, &peg3);

    // move n disks from peg1 to peg3
    hanoi(&peg1, &peg3, &peg2, n);

    printf("\nFinal state:\n");
    display(&peg1, &peg2, &peg3);

    destroy(&peg1);
    destroy(&peg2);
    destroy(&peg3);

    return 0;
}