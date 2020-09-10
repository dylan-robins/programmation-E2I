#include <iostream>
#include <cstring>

using namespace std;

void eliminer_premiere_occurence(char * CH1, char * CH2) {
    // tant qu'on trouve pas le debut de la chaine a supprimer, avancer
    while (CH1[0] != CH2[0] && CH1[0] != '\0') {
        CH1++;
    }
    
    // Si on est arrivé a la fin sans rien trouver, sortir
    if (CH1[0] == '\0') return;

    // Sinon, tester tous les chars suivants
    int i = 0;
    while (CH1[i] != '\0' && CH2[i] != '\0') {
        if (CH1[i] != CH2[i]) {
            // si les deux chars ne sont pas égaux, ce n'est pas une occurence
            break;
        }
        i++;
    }
    // Si on a trouve une occurence, alors ecraser le contenu de CH1 avec le
    // contenu de CH1+i, c'est a dire le contenu de CH1 à partir de la fin
    // de l'occurence 
    if (CH2[i] == '\0') {
        strcpy(CH1, CH1+i);
    }
}

int main(void) {
    char CH1[512], CH2[512], CH3[512];
    cout << "Entrez une chaine de caractères : " << endl << ">>> ";
    cin >> CH1;
    
    cout << "Entrez la sous-chaîne à supprimer : " << endl << ">>> ";
    cin >> CH2;

    strncpy(CH3, CH1, 512);
    
    eliminer_premiere_occurence(CH3, CH2);

    cout << CH1 << " | " << CH2 << " => " << CH3 << endl;

    return 0;
}