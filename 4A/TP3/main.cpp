#include <iostream>

#include "complexe.h"
#include "poly2deg.h"
#include "setOfIntegers.h"
#include "setOfInts_ll.h"

using namespace std;

int main(void) {
    cout << "########## Exercice 1 ##########" << endl;
    Complexe a(1, 1);
    Complexe b(3, -4);

    Complexe res;
    cout << "Valeurs complexes initiales :" << endl;
    cout << "\ta : ";
    a.afficher();
    cout << "\tb : ";
    b.afficher();
    cout << "\tc : ";
    res.afficher();

    res = a.add(b);
    cout << "a + b = ";
    res.afficher();

    res = a.sub(b);
    cout << "a - b = ";
    res.afficher();

    res = a.mul(b);
    cout << "a * b = ";
    res.afficher();

    Poly2Deg P(1, 0, 0);
    cout << "Polynome P(x) = ";
    P.afficher();

    res = P.solution();
    cout << "Solution de P: ";
    res.afficher();

    P = Poly2Deg(1, -2, 1);
    cout << "Polynome P(x) = ";
    P.afficher();
    cout << "Delta de P: " << P.delta() << endl;
    res = P.solution();
    cout << "Solution de P: ";
    res.afficher();

    P = Poly2Deg(2, 2, 1);
    cout << "Polynome P(x) = ";
    P.afficher();
    cout << "Delta de P: " << P.delta() << endl;
    res = P.solution();
    cout << "Solution de P: ";
    res.afficher();

    cout << "########## Exercice 2 ##########" << endl;
    SetOfIntegers set(10);
    int tmp;
    for (int i = 0; i < 10; i++) {
        cout << "Entrez un entier : >>> ";
        cin >> tmp;
        set.add(tmp);
    }

    set.display();
    cout << "Il y a " << set.cardinal() << " nombres distincts dans le tableau." << endl;

    cout << "Alternative avec liste chainées :" << endl;
    SetOfInts_ll set_ll;
    for (int i = 0; i < 10; i++) {
        cout << "Entrez un entier : >>> ";
        cin >> tmp;
        set_ll.add(tmp);
    }

    set_ll.display();
    cout << "Il y a " << set_ll.cardinal() << " nombres distincts dans le tableau." << endl;

    return 0;
}