/*
//  Created by Frederic Rousseau on 16/12/13.
//
*/




#include <stdio.h>
#include <stdlib.h>

#define TAILLE_QR 21
#define TAILLE_MOTIF 7


void affiche_QR21x21(int tab[]);
void affiche_QR21x21_bis(int tab[]);
int val_linQRCode(int x, int y);
int VerifPositionGlobale(int motif[], int qr[]);
void RotationQRcode(int qr[], int qr_rotated[], int angle);
void realignerQRcode(int qr[], int motif[]);

int main() {
    int exemple1[TAILLE_QR * TAILLE_QR]= {
        1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1,
        1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1,
        1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1,
        0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0,
        1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0,
        1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0,
        1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0};

    int motif_align[TAILLE_MOTIF * TAILLE_MOTIF]={
        1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 1, 1, 0, 1,
        1, 0, 1, 1, 1, 0, 1,
        1, 0, 1, 1, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1};

    int rot_90[TAILLE_QR * TAILLE_QR];
    RotationQRcode(exemple1, rot_90, 90);

    int rot_180[TAILLE_QR * TAILLE_QR];
    RotationQRcode(exemple1, rot_180, 180);

    int rot_270[TAILLE_QR * TAILLE_QR];
    RotationQRcode(exemple1, rot_270, 270);

#define CURRENT rot_270
    realignerQRcode(CURRENT, motif_align);

    return 0;
}





/***********************************************/
/* Des caracteres speciaux, dits d'echappement */
/* permettent de modifier la couleur des       */
/* caracteres ou du fond.                      */
/* 1 caractere est affiche sur 7 pixels en x   */
/* 13 en y. Dans la fonction ci-dessous, 2 car */
/* consecutifs permettent d'obtenir 1 carre de */
/* 14 pixels en x, et 13 en y.                 */
/* Un telephone portable est capable de lire   */
/* le QRcode affiche avec cette technique.     */
/***********************************************/

void affiche_QR21x21(int tab[]) {
    int i, j;
#define K_BG "\033[40;1m"
#define K_FG "\033[30;1m"
#define W_BG "\x1b[47;1m"

    for (j = 0; j < TAILLE_QR; j++)
    {
        for (i = 0; i < TAILLE_QR; i++)
        {
            if (tab[i + j * TAILLE_QR] == 1)
            {
                printf("%s##", K_BG); /* fond noir pour les 2 caractères ## */
                printf("\x1b[0m");    /* Retour au paramètre d'affichage par défaut */
            }
            else {
                printf("%s  ", W_BG); /* Affichage de 2 espaces pour obtenir 14 pixels */
                printf("\x1b[0m");    /* Retour au paramètre d'affichage par défaut */
            }

        }
        printf("\n");
    }
    printf("\x1b[0m \n"); /* Retour au paramètre d'affichage par défaut */
}


/*  Version basique */
void affiche_QR21x21_bis(int tab[]) {
    int i;

    for (i = 0; i < TAILLE_QR * TAILLE_QR; i++)
    {
        if ((i % TAILLE_QR) == 0)
            printf("\n");

        if (tab[i] == 1)
            printf("#");
        else
            printf(" ");        

    }
    printf("\n");
}


/* Transformation des coordonnees (x, y) en coordonnees lineaires */
int val_linQRCode(int x, int y) {
    return x + y * TAILLE_QR;
}


/* Transformation des coordonnees (x, y) en coordonnees lineaires */
int val_linMotif(int x, int y) {
    return x + y * TAILLE_MOTIF;
}

/*
   Verification qu'un motif est present dans le qr code a la position (x0,y0)
   Renvoie 1 si le motif est trouve, 0 sinon
   */
int Verif1Motif(int motif[], int qr[], int x0, int y0) {
    // si le motif depasserait du qr code en partant de (x0,y0), c'est mort
    if (y0+TAILLE_MOTIF > TAILLE_QR || x0+TAILLE_MOTIF > TAILLE_QR) {
        return 0;
    }
    // sinon essayer de matcher pixel par pixel
    for (int y = 0; y < TAILLE_MOTIF; y++) {
        for (int x = 0; x < TAILLE_MOTIF; x++) {
            // Si un pixel ne correspond pas, c'est mort
            if (motif[val_linMotif(x, y)] != qr[val_linQRCode(x+x0, y+y0)]) {
                return 0;
            }
        }
    }
    // si tous les pixels correspondent, alors on a trouve le motif
    return 1;
}

/*
   Verification qu'un motif est present dans les trois coins
   Renvoie 1 si OK, 0 sinon
   */
int VerifPositionGlobale(int motif[], int qr[]) {
    int top_left[2] = {0,0};
    int top_right[2] = {TAILLE_QR-TAILLE_MOTIF,0};
    int bot_left[2] = {0, TAILLE_QR-TAILLE_MOTIF};

    return (   Verif1Motif(motif, qr, top_left[0], top_left[1])
            && Verif1Motif(motif, qr, top_right[0], top_right[1])
            && Verif1Motif(motif, qr, bot_left[0], bot_left[1])   );
}


/*
   Effectue une rotation dans le sens horaire du qr code
   */
void RotationQRcode(int qr[], int qr_rotated[], int angle) {
    int x_r, y_r;

    for (int y = 0; y < TAILLE_QR; y++) {
        for (int x = 0; x < TAILLE_QR; x++) {
            switch (angle) {
                case 90:
                    x_r = TAILLE_QR -1 - y;
                    y_r = x;
                    break;
                case 180:
                    x_r = TAILLE_QR-1 - x;
                    y_r = TAILLE_QR-1 - y;
                    break;
                case 270:
                    x_r = y;
                    y_r = TAILLE_QR-1 - x;
                    break;
                default:
                    x_r = x;
                    y_r = y;
                    break;
            }
            qr_rotated[val_linQRCode(x_r,y_r)] = qr[val_linQRCode(x,y)];
        }
    }
}


void realignerQRcode(int qr[], int motif[]) {
    int top_left[2] = {0,0};
    int top_right[2] = {TAILLE_QR-TAILLE_MOTIF,0};
    int bot_left[2] = {0, TAILLE_QR-TAILLE_MOTIF};
    int bot_right[2] = {TAILLE_QR-TAILLE_MOTIF, TAILLE_QR-TAILLE_MOTIF};

    if (VerifPositionGlobale(motif, qr) == 1) {
        printf("QR OK!\n");
        affiche_QR21x21(qr);
    } else {
        printf("QR MAL ALIGNE!\n");

        int realigne[TAILLE_QR * TAILLE_QR];

        if (   Verif1Motif(motif, qr, top_left[0], top_left[1])
                && Verif1Motif(motif, qr, top_right[0], top_right[1])
                && Verif1Motif(motif, qr, bot_right[0], bot_right[1])) {
            RotationQRcode(qr, realigne, 270);

        } else if (   Verif1Motif(motif, qr, top_right[0], top_right[1])
                && Verif1Motif(motif, qr, bot_right[0], bot_right[1])
                && Verif1Motif(motif, qr, bot_left[0], bot_left[1])) {
            RotationQRcode(qr, realigne, 180);
        } else if (   Verif1Motif(motif, qr, bot_right[0], bot_right[1])
                && Verif1Motif(motif, qr, bot_left[0], bot_left[1])
                && Verif1Motif(motif, qr, top_left[0], top_left[1])) {
            RotationQRcode(qr, realigne, 90);
        }

        affiche_QR21x21(realigne);
    }
}
