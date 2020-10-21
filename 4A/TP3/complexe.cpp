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

double Complexe::re() {
    return _Re;
}

double Complexe::im() {
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
