#include <iostream>

#include "complexe.h"
#include "vecteur3d.h"
#include "string1.h"

using namespace std;

#define TEST_EX3

int main(void)
{
#ifdef TEST_EX1
    cout << "########## Exercice 1 ##########" << endl;
    Complexe z1(1, 1);
    cout << "z1 = " << z1 << endl;

    Complexe z2;
    cout << "Entrez une valeur pour z2: (format a+bi)" << endl
         << ">>> ";
    cin >> z2;
    cout << "z2 = " << z2 << endl;

    cout << "z1 + z2 = " << z1 + z2 << endl;
    cout << "z1 - z2 = " << z1 - z2 << endl;
    cout << "z1 * z2 = " << z1 * z2 << endl;
    cout << "z1 / z2 = " << z1 / z2 << endl;
    cout << "z1 == z2 : " << boolalpha << (z1 == z2) << endl;
    cout << "z1 != z2 : " << boolalpha << (z1 != z2) << endl;
    cout << "!z1 : " << boolalpha << (!z1) << endl;

    Complexe z3(z2);
    cout << "z3 = " << z3 << " (copie de z2)" << endl;
    z3 = z1;
    cout << "z3 := z1 => z3 = " << z3 << endl;
#endif

#ifdef TEST_EX2
    cout << "########## Exercice 2 ##########" << endl;
    Vecteur3d u(1, 1, 1);
    cout << "Vecteur u: " << u << endl;

    Vecteur3d v(u);
    cout << "Vecteur v initial: " << v << endl;
    cout << "u == v? : " << boolalpha << (u == v) << endl;
    v.set(0, 5.4);
    v.set(1, 4);
    v.set(2, 9.6);
    cout << "Vecteur v: " << v << endl;
    cout << "u == v? : " << boolalpha << (u == v) << endl;
    cout << "Entrez les nouvelles coordonnées de u (séparées par des espaces) :" << endl
         << ">>>";
    cin >> u;
    cout << "Vecteur u: " << u << endl;

    cout << "Test opérations :" << endl;
    cout << "Addition: " << u << " + " << v << " = " << u + v << endl;
    cout << "Produit scalaire: " << u << " . " << v << " = " << u * v << endl;
#endif

#ifdef TEST_EX3
    String ch1("essai"), ch2 = ch1, ch3('=', 80);
    cout << "ch1 initial: " << ch1 << endl;
    const String ch4("chaîne constante");
    ch1.nieme(1) = 'E'; // le premier caractère de la chaîne
    cout << "ch1 modifié: " << ch1 << endl;
    cout << ch4.nieme(1) << endl;
    ch2.saisie();
    ch2.concatene(" de la classe String");
    ch2.concatene('g');
    if (!egal(ch2, ""))
    {
        ch2.affiche();
        cout << endl;
    }
    ch2.minuscule().affiche(); // est-ce bien raisonnable ???
    cout << endl;
#endif

    return EXIT_SUCCESS;
}