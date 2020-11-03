#ifndef __COMPLEXE_H__
#define __COMPLEXE_H__

#include <iostream>
using namespace std;

class Complexe {
private:
    friend bool operator==(const Complexe& c1, const Complexe c2);
    friend bool operator!=(const Complexe& c1, const Complexe c2);
    friend bool operator!(const Complexe& c1);
    friend Complexe operator+(const Complexe& c1, const Complexe c2);
    friend Complexe operator-(const Complexe& c1, const Complexe c2);
    friend Complexe operator*(const Complexe& c1, const Complexe c2);
    friend Complexe operator/(const Complexe& c1, const Complexe c2);
    friend ostream& operator<<(ostream& os, const Complexe& z);
    friend istream& operator>>(istream& is, Complexe& z);
    double _Re, _Im;

public:
    Complexe() : _Re(0), _Im(0) {};
    Complexe(double re, double im) : _Re(re), _Im(im) {};
    Complexe(const Complexe &z) : _Re(z.re()), _Im(z.im()) {};
    
    void afficher();
    double re() const;
    double im() const;
    Complexe add(const Complexe &z);
    Complexe sub(const Complexe &z);
    Complexe mul(const Complexe &z);

    Complexe& operator=(const Complexe& c1);
};

#endif