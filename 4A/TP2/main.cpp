#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

#include "vec3d.h"
#include "pile.h"
int Pile::_nb_objets = 0;
#include "point.h"


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

    Point p;
    cout << "Créé un point aux coordonnées (" << p.abscisse() << "," << p.ordonnee() << "}" << endl;
    p.translate(3, 4);
    cout << "Bougé le point selon le vecteur (3, 4) : (" << p.abscisse() << "," << p.ordonnee() << "}" << endl;
    
    cout << "Coordonnées polaires (" << p.rho() << "," << p.teta() << "}" << endl;

    p.rotation(M_PI);
    cout << "Rotation du point de pi radians : (" << p.abscisse() << "," << p.ordonnee() << "}" << endl;
    p.set_deg();
    p.rotation(-45);
    cout << "Rotation du point de -45° : (" << p.abscisse() << "," << p.ordonnee() << "}" << endl;

    return 0;
}
