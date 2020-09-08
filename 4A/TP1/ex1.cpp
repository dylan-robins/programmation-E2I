#include <iostream>

using namespace std;

int nbjour(int mois, int annee) {
    switch (mois) {
    case 2:
        if (annee % 4 == 0) {
            // février bissextile
            return 29;
        } else {
            // février normal
            return 28;    
        }

    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        // mois à 31 jours
        return 31;
        break;
    
    default:
        // tous les autres mois
        return 30;
        break;
    }
}

int main(void) {
    cout << nbjour(2, 2020) << endl;
    return 0;
}