#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char Num_ss[14];
    int sexe; // 1=H, 2=F
    int annee;
    int mois;
    int departement;
    int commune;
    int ordre;
    int cle;

    
} info_ss;

int Verif_cle(info_ss *num) {
    // découper la chaine num->Num_ss en n1 et n2
    char n1[8];
    n1[7] = '\0';
    strncpy(n1, num->Num_ss, 7);

    char n2[7];
    n2[6] = '\0';
    strncpy(n2, (num->Num_ss + 7), 6);

    // calculer r1 
    int r1 = atoi(n1) % 97;

    // construire n3 = str(r1)+n2
    char n3[9];
    sprintf(n3, "%d", r1);
    strncat(n3, n2, 7);

    // calcul du complement a 97 du reste r = n3 % 97
    return (num->cle == (97-(atoi(n3)%97)));
}

void Traitement_info(char numero_secu[16], info_ss *secu) {
    // N.I.R
    strncpy(secu->Num_ss, numero_secu, 13);
    secu->Num_ss[13] = '\0';
    // cle
    char cle[3];
    cle[2] = '\0';
    strncpy(cle, numero_secu+13, 2);
    secu->cle = atoi(cle);
    // sexe
    secu->sexe = numero_secu[0] - '0';
    // annee
    char annee[3];
    annee[2] = '\0';
    strncpy(annee, numero_secu+1, 2);
    secu->annee = atoi(annee);
    // mois
    char mois[3];
    mois[2] = '\0';
    strncpy(mois, numero_secu+3, 2);
    secu->mois = atoi(mois);
    // departement
    char dep[3];
    dep[2] = '\0';
    strncpy(dep, numero_secu+5, 2);
    secu->departement = atoi(dep);
    // commune
    char commune[4];
    commune[3] = '\0';
    strncpy(commune, numero_secu+7, 3);
    secu->commune = atoi(commune);
    // ordre
    char ordre[4];
    ordre[3] = '\0';
    strncpy(ordre, numero_secu+7, 3);
    secu->ordre = atoi(ordre);
}

void Afficher_info(info_ss *secu) {
    printf("N.I.R: %s\n", secu->Num_ss);
    printf("Cle: %d\n", secu->cle);
    printf("Sexe: %d\n", secu->sexe);
    printf("Année de naissance: %d\n", secu->annee);
    printf("Mois de naissance: %d\n", secu->mois);
    printf("Département de naissance: %d\n", secu->departement);
    printf("Commune de naissance: %d\n", secu->commune);
    printf("Numéro d'ordre': %d\n", secu->ordre);
}

void init_secu(info_ss *secu) {
    char numero_secu[17];
    printf("Veuillez rentrer un numéro de sécurité socale (15 chiffres)\n>>> ");
    fgets(numero_secu, 17, stdin);
    numero_secu[16] = '\0'; // on vire le \n en fin de ligne
    Traitement_info(numero_secu, secu);
}

void test_statique() {
    info_ss fausse_secu;
    info_ss bonne_secu;

    // version automatique
    //Traitement_info("180072636200695", &fausse_secu);
    //Traitement_info("180072636200694", &bonne_secu);

    // version manuelle
    init_secu(&fausse_secu);
    init_secu(&bonne_secu);

    // test traitement + affichage
    printf("Faux numéro de sécurité sociale:\n");
    Afficher_info(&fausse_secu);
    printf("\n");

    printf("Bon numéro de sécurité sociale:\n");
    Afficher_info(&bonne_secu);
    printf("\n");

    // test fausse secu
    if (Verif_cle(&fausse_secu)) {
        printf(
            "%s %d est un numero de securite sociale valide\n",
            fausse_secu.Num_ss, fausse_secu.cle
        );
    } else {
        printf(
            "%s %d n'est pas un numero de securite sociale valide\n",
            fausse_secu.Num_ss, fausse_secu.cle
        );
    }

    // test bonne secu
    if (Verif_cle(&bonne_secu)) {
        printf(
            "%s %d est un numero de securite sociale valide\n",
            bonne_secu.Num_ss, bonne_secu.cle
        );
    } else {
        printf(
            "%s %d n'est pas un numero de securite sociale valide\n",
            bonne_secu.Num_ss, bonne_secu.cle
        );
    }
}

void test_alloc() {
    char buffer[1024];
    printf("Veuillez rentrer le nombre de numéros de sécurité sociale à entrer:\n>>> ");
    fgets(buffer, 1024, stdin);
    size_t nb_elements = atol(buffer);
    printf("Création d'un tableau de %ld elements...\n", nb_elements);
    info_ss *tab = (info_ss *) malloc(nb_elements * sizeof(info_ss));

    free(tab);
}


int main() {
    printf("########## TEST STATIQUE ##########\n");
    test_statique();
    printf("\n\n########## TEST ALLOCATION ##########\n");
    test_alloc();
    return 0;
}
