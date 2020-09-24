#include <iostream>

#include "vec3d.h"
#include "pile.h"
int Pile::_nb_objets = 0;

using namespace std;

int main(void) {
    cout << "########## Exercice 1 ##########" << endl;
    
    Vecteur3d *u = new Vecteur3d();
    cout << "Vecteur u initialisé : ";
    (*u).afficher();
    delete u;

    Vecteur3d v(1, 3, 2);
    cout << "Vecteur v initialisé : ";
    v.afficher();

    cout << endl << "########## Exercice 2 ##########" << endl;

    Pile p1(5);
    cout << "Pile 1 créé!" << endl;

    cout << "Nombre de piles créées: " << p1.nb_objets() << endl;
    
    Pile p2(2);
    cout << "Pile 2 créé!" << endl;
    Pile p3(3);
    cout << "Pile 3 créé!" << endl;
    Pile p4(15);
    cout << "Pile 4 créé!" << endl;

    cout << "Nombre de piles créées: " << p1.nb_objets() << endl;

    cout << endl << "########## Exercice 3 ##########" << endl;

    return 0;
}
