#include <iostream>

#include "salaries.h"
unsigned long salarie::_nb_salaries = 0;
unsigned long employe::_nb_employes = 0;
unsigned long commercial::_nb_commerciaux = 0;
unsigned long directeur::_nb_directeurs = 0;

#include "points.h"
#include "liste.h"
#include "liste_points.h"

using namespace std;

#define EX1
#define EX2
#define EX3

int main() {
#ifdef EX1
    cout << "################################# EXERCICE 1 ##################################" << endl;

    Colour red(col_t::red);
    Colour blue(col_t::blue);
    Colour yellow(col_t::yellow);
    Colour reset(col_t::reset);

    Pointcol x(5, 0, red);
    cout << "Red point: ";
    x.affiche();

    Pointcol y(1, 1, blue);
    cout << "Blue point : ";
    y.affiche();
    
    Pointcol z(2.5, 3.1415, yellow);
    cout << "Yellow point : ";
    z.affiche();
#endif

#ifdef EX2
    cout << "################################# EXERCICE 2 ##################################" << endl;

    directeur boss("Jean-Marc", 0, 8181, 8000, 46000);
    employe troufion1("Kevin", 1, 10.03, 38.5);
    commercial troufion2("Karen", 250000, 4, 25, 35, 0.7);

    cout << "Chef d'entreprise:" << endl;
    boss.afficher();

    cout << endl << "Employé :" << endl;
    troufion1.afficher();

    cout << endl << "Commercial :" << endl;
    troufion2.afficher();

    cout << "Nb directeurs: " << directeur::get_nb_directeurs() << endl;
    cout << "Nb employés: " << employe::get_nb_employes() << endl;
    cout << "Nb commerciaux: " << commercial::get_nb_commerciaux() << endl;
#endif

#ifdef EX3
    cout << "################################# EXERCICE 3 ##################################" << endl;
    Liste l;
    
    int a=5, b=8, c=1, d=6, e=9;

    l.ajoute(&a);
    l.ajoute(&b);
    l.ajoute(&c);
    l.ajoute(&d);
    l.ajoute(&e);

    cout << "Contenu de la liste générique :" << endl;
    cout << "  - index " << 0 << " : " << *((int *)l.premier()) << endl;
    for (int i = 1; !l.fini(); i++) {
        cout << "  - index " << i << " : " << *((int *)l.prochain()) << endl;
    }

    ListePoints lp;

    Point m(0, 0);
    Point n(1, 0);
    Point o(0, 1);
    Point p(1, 1);
    Point q(3, 4);

    lp.ajoute(&m);
    lp.ajoute(&n);
    lp.ajoute(&o);
    lp.ajoute(&p);
    lp.ajoute(&q);
    
    cout << "Contenu de la liste de points :" << endl;
    lp.afficher();

#endif
    return 0;
}