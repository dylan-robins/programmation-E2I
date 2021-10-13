---
marp: true
author: Dylan Robins
paginate: true
title: Révisions langage C
style: |
  section {
    font-size: 20pt;
  }

---

# Révisions langage C
Dylan Robins
2021-10-13

---

## 1. Notions

### 1.1. Compilation / édition de liens

En C, la génération d'un programme est un processus en deux étapes:  
1. La compilation: transformation de chaque fichier C en un fichier objet
   (~= assembleur) équivalent  
   `gcc -c <mon-fichier-c>.c -o <mon-fichier-objet>.o`
2. L'édition de liens: remplacement des "étiquettes" dans les fichiers objet
   par les adresses qui vont bien  
   `gcc <mes-fichiers-objet> -o <mon-programme>`

GCC est intelligent: il sait faire plein de choses automatiquement donc souvent
il n'est pas nécessaire de spécifier toutes les étapes:
`gcc <mes-fichiers-c> -o <mon-programme>`


---

### 1.2. Makefile

Un Makefile est un fichier qui sert à automatiser les flux de compilation lorsque
l'intelligence de GCC ne suffit pas (ou lorsqu'on veut être compatible avec des
compilateurs moins intelligents que GCC).

Le principe est très simple: on définit des "recettes" pour créer les différents
fichiers nécessaires pour le bon fonctionnement de notre programme:  
```Makefile
nom_de_recette: liste_des_dépendances
    <commandes à executer>
```

Une dépendance peut être soit un fichier, soit une autre tâche  
=> Beaucoup de flexibilité pour faire des trucs beaucoup trop compliqués

---

On peut écrire des recettes génériques à l'aide de macros et de variables:
```Makefile
$@ # nom de la recette en cours
$^ # liste des dépendances
$< # première dépendance
TOTO = Lorem ipsum dolor sit amet # déclaration d'une variable
$(TOTO) # utilisation de la variable
```

Par exemple, une tâche générique pour compiler n'importe quel fichier C en son .o:
```Makefile
O_DIR = ./obj
C_FLAGS = -Wall -std=c11

$(O_DIR)/%.o: %.c
    gcc -c $(C_FLAGS) -o $@ $<
```

---

## 2. Langage C

### 2.1. Types de base

Le C est un langage **typé**: il faut spécifier le type de chaque variable ainsi que
la signature de toutes les fonctions:  
```c
double i = 0;
int somme(int a, int b) {
  return a + b;
}
```

---

En C, tout s'exprime en termes de nombres:  
- Nombres entiers:
  - `char / unsigned char`: 8 bits
  - `short / unsigned short`: 16 bits
  - `int / unsigned int`: 32 bits
  - `long / unsigned long`: 64 bits
- Nombres flottants:
  - `float`: 32 bits
  - `double`: 64 bits

Rappels:
- Un charactère (char) est juste un nombre de 8 bits => cf la table ASCII

---

### 2.2. Pointeurs

Un pointeur est une variable qui contient l'adresse mémoire d'une ressource.
Cela nous permet de faire plein de choses compliquées.

- Tableaux / listes:
  - En C, un tableau est **l'adresse du premier élément**. Un tableau ne connait donc pas sa propre taille!  
    ```c
    int tab[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}; // tab est l'adresse de la case mémoire qui contient 9
    ```
  - Une chaine de caractère n'est rien d'autre qu'un tableau de chars
    où on a pris que le dernier élément serait un char nul (valeur 0 = '\0')  
    ```c
    char string[12] = "Hello World"; // "Hello World" = 11 chars, mais '\0' implicite à la fin!
    ```  
    Toutes les fonctions de string.h suivent cette convention, après libre à vous de faire comme vous voulez.

---

### 2.3. Types composés

Parfois on a envie de faire des choses plus complexes et les types de base ne suffisent plus.
On a à notre disposition 3 types d'objet autre que des nombres:
- Les structures
- Les énumérations
- Les unions

---
#### 2.3.1. Les structures
Type 'conteneur' qui représente un groupe de variables à regrouper ensemble.  
```c
struct vecteur {
    double x;
    double y;
    double z;
};
```  
Le nom de la structure devient un nouveau type que l'on peut utiliser par la suite, et les champs sont
accessibles avec l'opérateur `.`:  
```c
struct vecteur v;
v.x = 0;
v.y = 1;
v.z = 2;
```
---
#### 2.3.2. Les énumérations
Type qui sert à créer des mots clés permettant de modéliser des choses distinctes de façon explicite.  
```c
enum pointCardinal {NORD, SUD, EST, OUEST};
```  
Par défaut l'énum n'est utilisable que dans le fichier où il est déclaré (on verra en 2.4. une stratégie pour remédier à ça).  
```c
pointCardinal dir = NORD;
if (dir == NORD) {
    printf("On va vers le nord!\n");
}
```
---
#### 2.3.3. Les unions
Type qui sert à représenter une variable qui peut avoir plusieurs types.  
```c
// Un tag peut être soit un identifiant ou un commentaire
union tag {
    int id;
    char * comment;
};
```  
La donnée est lue/stockée dans le format qui correspond au nom du membre que l'on utilise:  
```c
union tag t;
t.comment = "AAAA";
printf("Hello, %s!\n", t.comment); // Affiche "Hello, AAAA!"
printf("Hello, 0x%X!\n", t.id);    // Affiche "Hello, 0x42BC734!"
```

---
### 2.4. Types sur mesure

On a la possibilité de créer des noms de type sur mesure avec l'instruction `typedef`:  
```c
// Exemple de base
typedef unsigned long size_t;
// Exemples plus complexes
typedef enum {NORD, SUD, EST, OUEST} pointCardinal;
typedef struct {
    int length;
    int * tab;
} intList;
```

Dans l'exemple ci-dessus, le type `size_t` correspondra à un `unsigned long`, ce qui est moins lourd à écrire.  
Les deux autres exemples montrent des "effets de bord" de cette mécanique: si on définit un type qui correspond à un enum anonyme, l'enum est dès lors accessible partout dans notre projet et non plus seulement dans le fichier où il est déclaré. Similairement, en définissant un type qui correspond à une structure anonyme il n'est plus nécessaire de préfixer le nom de la structure par 'struct' (pratique...)

---

### 2.5. Structures de contrôle

On a 4 structures de contrôle de base:
- Expression conditionnelle (`if`)
- Boucles `while`
- Boucle `for`
- Dissociation par cas (`switch`)

---

#### 2.5.1. Expression conditionnelle (`if`)  
```c
if (expression) {
    // Code à executer si expression != 0
} else if (expression == 3) {
    // Code à executer si expression == 3
} else {
    // Code à executer le reste du temps
}
```  
  3. Attention, les parenthèses autour de la condition sont obligatoires!
--- 
#### 3.0.1. Boucles `while`  
```c
while (expression) {
    // Code à executer tant que expression != 0
}
```  
#### 3.0.2. Boucle `for`  
```c
for (initialisation; condition; expression_inter_iteration) {
    // Code à executer tant que expression != 0
}
```  
--- 
#### 3.0.3. Dissociation par cas (`switch`)  
```c
switch (variable) {
    case valeur_1:
      // code à executer si variable == valeur_1
      break;
    case valeur_2:
    case valeur_3:
      // code à executer si variable == valeur_2 ou valeur_3
      break; 
}
```  

---

## 4. Le C, en pratique...

### 4.1. Fonction `main()` et arguments de ligne de commande

La fonction qui s'exécute au lancement d'un programme est le `main`. Cette fonction peut avoir deux formes:  
```c
int main() {
    // Code à exécuter
    return 0;
}
```  
```c
int main(int argc, char ** argv) {
    // Code à exécuter
    return 0;
}
```

argc est le nombre d'arguments de ligne de commande passés au programme, et argv est le tableau des chaines de caractères correspondants.

---

### 4.2. Manipulation de chaînes de caractères

Libraries utiles:

- `<string.h>`: `strlen`, `strcpy`, `strncpy`, `strcmp`, `strncmp`...
- `<ctype.h>`: `atoi`, `atol`, `atof`, `isalpha`, `isdigit`, `isspace`...
- `<stdio.h>`: `printf`, `scanf`, `fgets`...
- `<stdlib.h>`: `malloc`, `free`...