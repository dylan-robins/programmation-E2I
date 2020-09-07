#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LONG_ENTIERE 31
#define LONG_DECIMALE 21

typedef struct {
    char pentiere[LONG_ENTIERE];
    char pdecimale[LONG_DECIMALE];
} GrandNombre;

void AfficherGN(GrandNombre nb) {
    printf("%s,%s\n", nb.pentiere, nb.pdecimale);
}

void NormaliserGN(GrandNombre *nb) {
    // partie entiere
    int len = strlen(nb->pentiere);
    // Tout decaler a droite
    for (int i = len; i >= 0; i--) {
        nb->pentiere[LONG_ENTIERE+i-len-1] = nb->pentiere[i];
    }
    // Remplir le reste avec des 0
    for (int i = 0; i < LONG_ENTIERE-len-1; i++) {
        nb->pentiere[i] = '0';
    }

    // partie decimale
    len = strlen(nb->pdecimale);
    // deja tout a gauche, il faut juste remplir avec des 0
    for (int i = len; i < LONG_DECIMALE-1; i++) {
        nb->pdecimale[i] = '0';
    }
    // Ajouter le \0 de fin de chaine
    nb->pdecimale[LONG_DECIMALE] = '\0';
}

GrandNombre AdditionGN(GrandNombre a, GrandNombre b) {
    GrandNombre res;
    res.pdecimale[LONG_DECIMALE-1] = '\0';
    res.pentiere[LONG_ENTIERE-1] = '\0';
    unsigned char a_digit;
    unsigned char b_digit;
    unsigned char retenue = 0;

    // Addition parties decimales
    for (int i = LONG_DECIMALE-2; i >= 0; i--) {
        a_digit = a.pdecimale[i] - '0';
        b_digit = b.pdecimale[i] - '0';
        res.pdecimale[i] = '0' + (a_digit + b_digit + retenue) % 10;
        retenue = (a_digit+b_digit)/10;
    }

    // Addition parties entiere
    for (int i = LONG_ENTIERE-2; i >= 0; i--) {
        a_digit = a.pentiere[i] - '0';
        b_digit = b.pentiere[i] - '0';
        res.pentiere[i] = '0' + (a_digit + b_digit + retenue) % 10;
        retenue = (a_digit+b_digit)/10;
    }
    return res;
}

GrandNombre ComplementA9GN(GrandNombre x) {
    GrandNombre res;
    res.pdecimale[LONG_DECIMALE-1] = '\0';
    res.pentiere[LONG_ENTIERE-1] = '\0';

    for (int i = 0; i < strlen(x.pentiere); i++) {
        res.pentiere[i] = '0' + (9 - (x.pentiere[i] - '0'));
    }
    for (int i = 0; i < strlen(x.pdecimale); i++) {
        res.pdecimale[i] = '0' + (9 - (x.pdecimale[i] - '0'));
    }
    GrandNombre un = {"0", "0"};
    NormaliserGN(&un);

    AfficherGN(un);
    res = AdditionGN(res, un);

    return res;
}

GrandNombre SoustractionGN(GrandNombre a, GrandNombre b) {
    GrandNombre res = ComplementA9GN(a);
    res = AdditionGN(res, b);
    return res;
}

int main() {
    GrandNombre x = {"1234","567"};
    GrandNombre a = {"47891","00567"};
    GrandNombre b = {"1234","6789"};
    printf("Test normalisation:\n");
    AfficherGN(x);
    NormaliserGN(&x);
    AfficherGN(x);

    printf("\nTest addition:\n");
    NormaliserGN(&a);
    NormaliserGN(&b);
    printf("a =   ");
    AfficherGN(a);
    printf("b =   ");
    AfficherGN(b);
    printf("a+b = ");
    AfficherGN(AdditionGN(a, b));

    printf("\nTest soustraction:\n");
    NormaliserGN(&a);
    NormaliserGN(&b);
    printf("a =   ");
    AfficherGN(a);
    printf("b =   ");
    AfficherGN(b);
    printf("a-b = ");
    AfficherGN(SoustractionGN(a, b));
    return 0;
}