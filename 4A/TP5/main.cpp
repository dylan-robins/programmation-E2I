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
#define EX2

int main() {
#ifdef EX1
    Colour red(col_t::red);
    Colour blue(col_t::blue);
    Colour yellow(col_t::yellow);
    Colour reset(col_t::reset);

    Pointcol x(5, 0, red);
    x.affiche();

    Pointcol y(1, 1, blue);
    y.affiche();
    
    Pointcol z(2.5, 3.1415, yellow);
    z.affiche();
#endif

#ifdef EX2
    directeur boss("Jean-Marc Chery", 0, 8181, 8000, 46000);
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
    Liste l;
    
    int a = 5, b = 8;
    char c = 'r';
    unsigned long d = 678990;
    const char * e = "Ceci est une chaine";

    l.ajouter(&a);
    l.ajouter(&b);
    l.ajouter(&c);
    l.ajouter(&d);
    l.ajouter(&e);

    cout << "Contenu de la liste générique :" << endl;
    cout << "  - " << 0 << ": " << l.premier << endl;
    for (int i = 1; !l.fini(); i++) {
        cout << "  - " << i << ": " << l.suivant << endl;
    }

    ListePoints lp;

    Point o(0, 0);
    Point x(1, 0);
    Point y(0, 1);
    Point u(1, 1);
    Point v(3, 4);

    lp.ajouter(&o);
    lp.ajouter(&x);
    lp.ajouter(&y);
    lp.ajouter(&u);
    lp.ajouter(&v);
    
    cout << "Contenu de la liste de points :" << endl;
    lp.afficher();

#endif
    return 0;
}