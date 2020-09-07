#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#include "sort.h"
list_t *rand_ints(int nb, int min, int max) {
    list_t *new_list = list(nb);
    for (int i = 0; i < nb; i++) {
        new_list->t[i] = (int)round(((double)rand()/RAND_MAX)*(max-min)+min);
    }
    return new_list;
}

int main(int argc, char **argv) {
    int nb_iterations;
    int list_length;

    clock_t avg_runtime = 0;
    clock_t start_time;
    list_t *l = NULL;

    srand(time(NULL));

    if (argc != 3) {
        fprintf(stderr, "Wrong number of arguments. Please provide only the number of times to run each algorithm and the lenth of the lists to create.\n");
        return 1;
    }

    if (sscanf(argv[1], "%d", &nb_iterations) != 1) {
        fprintf(stderr, "Argument <%s> couldn't be parsed as an integer.\n", argv[1]);
        return 2;
    }

    if (sscanf(argv[2], "%d", &list_length) != 1) {
        fprintf(stderr, "Argument <%s> couldn't be parsed as an integer.\n", argv[2]);
        return 2;
    }

    printf("RUNNING SORT ALGORITHMS WITH LISTS OF LENGTH %d %d TIMES EACH\n\n", list_length, nb_iterations);

    for (int i = 0; i < nb_iterations; i++) {
        // generate a random list of ints
        l = rand_ints(list_length, 0, 20);

        // save start time for later
        start_time = clock();
        // sort them using insertion sort
        bubbleSort(l, false);
        // destroy list
        delete(l);

        // add runtime to avg
        avg_runtime += clock() - start_time;
    }
    avg_runtime /= nb_iterations;

    printf("Avg runtime for bubble sort algorithm: %ld ms\n", avg_runtime);

    avg_runtime = 0;

    for (int i = 0; i < nb_iterations; i++) {
        // generate a random list of ints
        l = rand_ints(list_length, 0, 20);

        // save start time for later
        start_time = clock();
        // sort them using insertion sort
        insertionSort(l, false);
        // destroy list
        delete(l);

        // add runtime to avg
        avg_runtime += clock() - start_time;
    }
    avg_runtime /= nb_iterations;

    printf("Avg runtime for insertion sort algorithm: %ld ms\n", avg_runtime);

    avg_runtime = 0;

    for (int i = 0; i < nb_iterations; i++) {
        // generate a random list of ints
        l = rand_ints(list_length, 0, 20);

        // save start time for later
        start_time = clock();
        // sort them using quick sort
        quickSort(l, false);
        // destroy list
        delete(l);

        // add runtime to avg
        avg_runtime += clock() - start_time;
    }
    avg_runtime /= nb_iterations;

    printf("Avg runtime for quick sort algorithm: %ld ms\n", avg_runtime);

    return 0;
}