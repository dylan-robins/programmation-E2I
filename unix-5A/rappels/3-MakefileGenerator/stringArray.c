#include "stringArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strUtils.h"

// Alloue et initialise un nouveau stringArray vide
stringArray * newStringArray() {
    stringArray * strArr = (stringArray *) malloc(sizeof(stringArray));
    strArr->count = 0;
    strArr->capacity = 0;

    resizeStringArray(strArr, 10); // Capacité par défaut: 10

    return strArr;
}


// Supprime proprement un stringArray
void deleteStringArray(stringArray * strArr) {
    for (unsigned int i = 0; i < strArr->count; i++) {
        // Supprimer proprement la chaine de charactères
        free(strArr->strings[i]);
    }
    // Supprimer le tableau
    free(strArr);
}


// Redimentionne un stringArray et renvoie la nouvelle taille (= new_capacity).
// Si new_capacity < strArr.count, ne fait rien et renvoie 0
int resizeStringArray(stringArray * strArr, unsigned int new_capacity) {
    if (new_capacity < strArr->count) {
        // Erreur: si on rend le tableau trop petit on va perdre des éléments
        return 0;
    }
    // Sinon, créer un nouveau tableau de la taille souhaitée 
    char ** new_pointer = (char **) malloc(new_capacity * sizeof(char *));
    // Copier les éléments de l'ancien vers le nouveau
    for (unsigned int i = 0; i < strArr->count; i++) {
        new_pointer[i] = strArr->strings[i];
    }
    // Supprimer l'ancier tableau et le remplacer par le nouveau
    free(strArr->strings);
    strArr->strings = new_pointer;
    strArr->capacity = new_capacity;
    return strArr->capacity;
}

// Copie une chaine de caractères à la fin de la liste
void copyStringToArray(stringArray * strArr, char * str) {
    unsigned int char_count = strlen(str) + 1;

    // Si on a plus de place, il faut en réserver plus
    if (strArr->count == strArr->capacity) {
        resizeStringArray(strArr, strArr->capacity*2);
    }

    // Maintenant on peut rajouter notre élément
    strArr->count++;
    strArr->strings[strArr->count-1] = (char *) malloc(char_count * sizeof(char));
    strcpy(strArr->strings[strArr->count-1], str);
}

// Affiche toutes les chaines de caractère dans un stringArray
void printStringArray(stringArray * strArr) {
    for (unsigned int i = 0; i < strArr->count; i++) {
        printf("- '%s'\n", strArr->strings[i]);
    }
}

static int promptUser(char * lineBuffer, unsigned int size) {
    printf("(Entrez 'end' pour arrêter la saisie) >>> ");
    return (fgets(lineBuffer, size, stdin) != NULL);
}

// Lit des chaines de caractère au clavier et les renvoie sous la forme d'un stringArray 
stringArray * readStrings() {
    stringArray * strArr = newStringArray();
    char lineBuffer[1024];

    while (promptUser(lineBuffer, 1024)) {
        if (strcmp(lineBuffer, "end\n") == 0) {
            // Si l'utilisateur tape "end\n", arrêter la saisie
            break;
        } else {
            // Sinon, rajouter la chaine tapée au clavier à la liste
            copyStringToArray(strArr, trim(lineBuffer));
        }
    }

    return strArr;
}
