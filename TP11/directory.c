#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
    char *val;
    struct node_s *next;
} node_t;

node_t *new_node(const char *siret) {
    // create a node and allocate memory as necessary
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->val = (char *)malloc(strlen(siret) * sizeof(char) + 1);

    // fill in struct
    strcpy(node->val, siret);
    node->next = NULL;

    return node;
}

void print_list(node_t *node) {
    int i = 0;
    if (node == NULL) {
        // list is empty, special output
        printf("    Directory is empty\n");
    }
    while (node != NULL) {
        printf("    %4d: %s\n", i, node->val);
        i++;
        node = node->next;
    }
}

void delete (node_t *node) {
    free(node->val);
    free(node);
}

void remove_nth(node_t **head, int n) {
    node_t *current = *head;
    node_t *previous = NULL;

    if (current == NULL) {
        // list is already empty, do nothing
        return;
    } else if (n == 0) {
        // removing head of list: just move head and delete spare one
        *head = (*head)->next;
        delete (current);
    } else {
        // move current onto the n-th node
        int i = 0;
        while (i < n && current != NULL) {
            previous = current;
            current = current->next;
            i++;
        }
        if (current == NULL) {
            // list is shorter than n: don't remove anything
            return;
        }
        // splice current node out of list
        previous->next = current->next;
        // free it's memory
        delete (current);
    }
}

void insert_sorted(node_t **head, const char *siret) {
    node_t *current = *head;
    node_t *previous = NULL;
    node_t *new = new_node(siret);

    if (current == NULL) {
        // if list is empty, create a new one
        *head = new;
    } else if (current->next == NULL) {
        // if list only has one element, only two possibilities
        if (strcmp(siret, current->val) < 0) {
            *head = new;
            new->next = current;
        } else {
            current->next = new;
        }
    } else {
        // otherwise insert it in correct position
        // find correct place
        while (current->next != NULL && (strcmp(siret, current->val) > 0)) {
            previous = current;
            current = current->next;
        }
        // insert it
        previous->next = new;
        previous->next->next = current;
    }
}

void prompt_and_add(node_t **head) {
    char buffer[2048];
    printf("    Siret to add: ");
    // read line from user input
    fgets(buffer, 2048, stdin); // should validate user input but can't be arsed
    buffer[strlen(buffer) - 1] = '\0';  // remove trailing newline

    insert_sorted(head, buffer);
}

void prompt_and_remove(node_t **head) {
    char buffer[2048];
    int n = 0;
    printf("   Rank to remove from list : ");
    // read line from user input
    fgets(buffer, 2048, stdin);
    // parse it as an int
    sscanf(buffer, "%d", &n); // should validate user input but can't be arsed

    remove_nth(head, n);
}

int str_is_whitespace(const char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isspace(str[i])) return 0;
    }
    return 1;
}

void destroy_list(node_t *list) {
    if (list != NULL) {
        destroy_list(list->next);
        delete(list);
    }
}

int main() {
    node_t *directory = NULL;
    char buffer[2048];
    int exit_condition = 0;

    // main loop
    while (!exit_condition) {
        printf("Commands: disp, add, remove, quit\n>>> ");
        // read a line from user input
        fgets(buffer, 2048, stdin);
        buffer[strlen(buffer) - 1] = '\0';  // remove trailing newline

        // parse command and do stuff
        if (strcmp(buffer, "disp") == 0) {
            print_list(directory);

        } else if (strcmp(buffer, "add") == 0) {
            prompt_and_add(&directory);

        } else if (strcmp(buffer, "remove") == 0) {
            prompt_and_remove(&directory);

        } else if (strcmp(buffer, "quit") == 0) {
            exit_condition = 1;

        } else if (!str_is_whitespace(buffer)) {
            printf("Unknown command.\n");
        }
    }

    destroy_list(directory);

    return 0;
}