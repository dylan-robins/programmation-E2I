#include <stdio.h>
#include <math.h>

int main() {
    int u0 = 0;
    int r = 0;
    int n = 0;
    int somme_ari, somme_geo;
    int un_ari;
    int ui_ari, ui_geo;


    // Lecture des données utilisateur
    printf("Entrez le 1e terme de la suite (u0):\n");
    scanf("%d", &u0);
    getchar();

    printf("Entrez la raison (r):\n");
    scanf("%d", &r);
    getchar();

    printf("Entrez le dernier rang à calculer (n):\n");
    scanf("%d", &n);
    getchar();
    
    // Méthode de calcul 1: formules mathématiques

    un_ari = u0 + n*r; // terme max un pour la somme arithmétique
    somme_ari = (n+1)*(u0+un_ari)/2;

    somme_geo = u0*(1-pow(r, n+1))/(1-r);

    printf("Somme arithmétique: %d; Somme géométrique: %d\n", somme_ari, somme_geo);

    // Méthode de calcul 2: boucle avec accumulateur

    // valeurs un intermédiaires
    ui_ari = u0;
    ui_geo = u0;
    // accumulateurs
    somme_ari = u0;
    somme_geo = u0;

    // On a déjà u0: on calcule de u1 à un (inclus)
    for (int i = 1; i <= n; i++) {
        ui_ari += r;
        ui_geo = ui_geo * r;

        somme_ari += ui_ari;
        somme_geo += ui_geo;

    }
    printf("Somme arithmétique: %d; Somme géométrique: %d\n", somme_ari, somme_geo);

    return 0;
}
