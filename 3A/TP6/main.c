#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAILLE_MEM 0x20
#define NUL -1

typedef enum {LIBRE=0, OCCUPE=-1} statut;
typedef char info;
typedef int adr;
typedef struct {
    info donnee;
    statut etat;
} case_mem;

void init_memoire(case_mem mem[]) {
    for (int i = 0; i < TAILLE_MEM; i++) {
        mem[i].etat = LIBRE;
        mem[i].donnee = '0';
    }
}

void afficher_memoire(case_mem mem[]) {
    printf("    adr | donnée |  etat  \n");
    for (int i = 0; i < TAILLE_MEM; i++) {
        char c = mem[i].donnee;
        if (isalnum(c)) {
            printf(" 0x%04x | %6c | %6d \n", i, c, mem[i].etat);
        } else {
            printf(" 0x%04x | %6d | %6d \n", i, c, mem[i].etat);
        }
    }
}

int verifier_memoire_libre(case_mem mem[], adr base, int taille) {
    for (int i = 0; i < taille; i++) {
        if (mem[base+i].etat == OCCUPE) return 0;
    }
    return 1;
}

void verifier_case(case_mem mem[], adr a) {
    if (mem[a].etat == LIBRE) {
        fprintf(stderr, "Segmentation Fault: attempting to access unallocated block.\n");
        exit(2);
    } else if (a < 0 || a >= TAILLE_MEM) {
        fprintf(stderr, "Segmentation Fault: Accessing address 0x%x in memory of size 0x%x\n", a, TAILLE_MEM);
        exit(2);
    }
}

void occuper_memoire(case_mem mem[], adr base, int taille) {
    for (int i = 0; i < taille; i++) {
        mem[base+i].etat = OCCUPE;
    }
}

adr rechercher_bloc_libre (case_mem mem[], int taille) {
    for (int i = 0; i < TAILLE_MEM-taille; i++) {
        if (verifier_memoire_libre(mem, i, taille)) {
            return i;
        }
    }
    return NUL;
}

adr allouer_memoire(case_mem mem[], int taille) {
    adr bloc_libre = rechercher_bloc_libre(mem, taille);
    if (bloc_libre != NUL) {
        occuper_memoire(mem, bloc_libre, taille);
    }
    return bloc_libre;
}

int liberer_memoire(case_mem mem[], adr base, int taille) {
    int nb_freed = 0;
    for (int i = 0; i < taille; i++) {
        if (mem[base+i].etat == OCCUPE) {
            nb_freed++;
            mem[base+i].etat = LIBRE;
        }
    }
    return nb_freed;
}

info lire_case(case_mem mem[], adr a) {
    verifier_case(mem, a);
    return mem[a].donnee;
}

void ecrire_case(case_mem mem[], adr a, info c) {
    verifier_case(mem, a);
    mem[a].donnee = c;
}

void lire_chaine(case_mem mem[], adr a, info * ch) {
    char c = 'a'; // initialisation à autre chose que '\0'
    int i;
    for (i = 0; c != '\0'; i++) {
        c = lire_case(mem, a+i);
        ch[i] = c;
    }
    // rajouter le '\0' en fin de chaine
    ch[i] = '\0';
}

void ecrire_chaine(case_mem mem[], adr a, info * ch) {
    int i;
    for (i = 0; i < strlen(ch)+1; i++) {
        ecrire_case(mem, a+i, ch[i]);
    }
}

int main() {
    case_mem mem[TAILLE_MEM];
    // initialiser la memoire et l'afficher
    init_memoire(mem);

    adr bloc1 = allouer_memoire(mem, 1);
    adr bloc2 = allouer_memoire(mem, 5);

    ecrire_case(mem, bloc1, '5');

    info chaine1[5]  = "test";
    ecrire_chaine(mem, bloc2, chaine1);
    
    liberer_memoire(mem, bloc1, 1);
    bloc1 = allouer_memoire(mem, 3);

    info chaine2[3]  = "ah";
    ecrire_chaine(mem, bloc1, chaine2);

    adr bloc3 = allouer_memoire(mem, 1);
    ecrire_case(mem, bloc3, '1');

    printf("Allocation d'un bloc de 25 alors qu'il ne reste que 22. Resultat : %d\n", allouer_memoire(mem, 25));
    adr bloc4 = allouer_memoire(mem, 22);
    info chaine3[27]  = "abcdefghijklmnopqrstuvwxyz";
    printf("Ecriture de 27 chars dans un bloc réservé de 22 :\n");
    ecrire_chaine(mem, bloc4, chaine3);

    afficher_memoire(mem);
    return 0;
}