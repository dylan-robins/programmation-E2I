#include "complexe.h"

using namespace std;

#include <iostream>

void Complexe::afficher() {
    if (re() == 0 && im() == 0) {
        cout << 0 << endl;
    } else if (re() == 0) {
        cout << im() << "i" << endl;
    } else if (im() == 0) {
        cout << re() << endl;
    } else if (im() == 1) {
        cout << re() << "+i" << endl;
    } else if (im() > 0) {
        cout << re() << "+" << im() << "i" << endl;
    } else if (im() < 0) {
        cout << re() << im() << "i" << endl;
    } else {
        cerr << endl << "Error: invalid complex number " << re() << "+" << im() << "i" << endl;
        exit(EXIT_FAILURE);
    }
}

double Complexe::re() const {
    return _Re;
}

double Complexe::im() const {
    return _Im;
}
Complexe Complexe::add(const Complexe &z) {
    return Complexe(
        _Re + z._Re,
        _Im + z._Im
    );
}
Complexe Complexe::sub(const Complexe &z) {
    return Complexe(
        _Re - z._Re,
        _Im - z._Im
    );
}

Complexe Complexe::mul(const Complexe &z) {
    return Complexe(
        _Re * z._Re - _Im * z._Im,
        _Re * z._Im + _Im * z._Re
    );
}

bool operator==(const Complexe& c1, const Complexe c2) {
    return c1._Re == c2._Re && c1._Re ==c2._Im;
}
bool operator!=(const Complexe& c1, const Complexe c2) {
    return c1._Re != c2._Re || c1._Re != c2._Im;
}
bool operator!(const Complexe& c1) {
    return c1._Re == 0 && c1._Re == 0; // vrai si = 0, faux sinon
}
Complexe& Complexe::operator=(const Complexe& c1) {
    _Re = c1._Re;
    _Im = c1._Im;
    return *this; // pour chaîner l'opérateur
}

Complexe operator+(const Complexe& c1, const Complexe c2) {
    return Complexe(c1._Re+c2._Re, c1._Im+c2._Im);
}

Complexe operator-(const Complexe& c1, const Complexe c2) {
    return Complexe(c1._Re-c2._Re, c1._Im-c2._Im);
}

Complexe operator*(const Complexe& c1, const Complexe c2) {
    return Complexe(
        c1._Re*c2._Re - c1._Im*c2._Im,
        c1._Re*c2._Im + c1._Im*c2._Re
    );
}

Complexe operator/(const Complexe& c1, const Complexe c2) {
    if (!c2) {
        cerr << "Erreur: division par 0" << endl;
        return Complexe(0, 0);
    }
    return Complexe(
        (c1._Re*c2._Re + c1._Im*c2._Im) / (c2._Re*c2._Re + c2._Im*c2._Im),
        (c2._Re*c1._Im - c1._Re*c2._Im) / (c2._Re*c2._Re + c2._Im*c2._Im)
    );
}

ostream& operator<<(ostream& os, const Complexe& z) {
    if (z.re() == 0 && z.im() == 0) {
        os << 0;
    } else if (z.re() == 0) {
        os << z.im() << "i";
    } else if (z.im() == 0) {
        os << z.re();
    } else if (z.im() == 1) {
        os << z.re() << "+i";
    } else if (z.im() > 0) {
        os << z.re() << "+" << z.im() << "i";
    } else if (z.im() < 0) {
        os << z.re() << z.im() << "i";
    } else {
        cerr << endl << "Error: invalid complex number " << z.re() << "+" << z.im() << "i" << endl;
        exit(EXIT_FAILURE);
    }
    return os;
}

// Lit des nombres complexes formattés "a+bi", et extrait a et b pour les
// placer dans z. 
istream& operator>>(istream& is, Complexe& z) {
    char sign, i;
    is >> z._Re >> sign >> z._Im >> i;
    return is;
}