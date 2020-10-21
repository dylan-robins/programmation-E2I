#include <iostream>

#include "complexe.h"
#include "poly2deg.h"
#include "setOfIntegers.h"
#include "setOfInts_ll.h"
#include "vecteur3d.h"
#include "matrice.h"

using namespace std;

#define TEST_EX1
#define TEST_EX2
#define TEST_EX3

int main(void) {
    #ifdef TEST_EX1
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

    #endif
    #ifdef TEST_EX2
    cout << "########## Exercice 2 ##########" << endl;
    Set_Of_Integer set(10);
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

    #endif
    #ifdef TEST_EX3
    cout << "########## Exercice 3 ##########" << endl;
    
    Vecteur3d v;
    cout << "Valeurs vecteur initiales :" << endl;
    v.display();

    v = Vecteur3d(1, 2, 3);
    cout << "Valeurs vec (1 2 3) :" << endl;
    v.display();

    const double tab3[3][3] = {
        {1,   2,   3  },
        {11,  22,  33 },
        {111, 222, 333}
    };
    Matrice m(tab3);
    cout << "Matrice tab3 :" << endl;
    m.display();

    cout << "vec * tab3 =" << endl;
    m.produit_vec_mat(v).display();


    cout << "tab3 * vec =" << endl;
    m.produit_mat_vec(v).display();

    #endif
    return 0;
}