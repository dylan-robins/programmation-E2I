#ifndef __STRING_ARRAY__
#define __STRING_ARRAY__

/* Represente une liste de chaines de caractères
Membres:
    - strings (char **): tableau de chaines de caractères
    - count (uint): nombre de chaines dans le tableau
    - capacity (uint): taille du tableau (nombre max d'éléments)
*/
typedef struct {
    char ** strings;
    unsigned int count;
    unsigned int capacity;
} stringArray;

// Alloue et initialise un nouveau stringArray vide
stringArray * newStringArray();
// Supprime proprement un stringArray
void deleteStringArray(stringArray * strArr);
// Redimentionne un stringArray et renvoie la nouvelle taille (= new_capacity).
// Si new_capacity < strArr.count, ne fait rien et renvoie 0
int resizeStringArray(stringArray * strArr, unsigned int new_capacity);
// Copie une chaine de caractères à la fin de la liste
void copyStringToArray(stringArray * strArr, char * str);

// Affiche toutes les chaines de caractère dans un stringArray
void printStringArray(stringArray * strArr);

// Lit des chaines de caractère au clavier et les renvoie sous la forme d'un stringArray 
stringArray * readStrings();

#endif