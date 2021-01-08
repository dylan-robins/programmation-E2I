#ifndef __COMPLEXE_H__
#define __COMPLEXE_H__

#include <iostream>
using namespace std;

class Complexe {
  public:
    Complexe(double re = 0, double im = 0) : _Re(re), _Im(im){};
    Complexe(const Complexe &z) : _Re(z.re()), _Im(z.im()){};

    void afficher();
    double re() const;
    double im() const;
    Complexe add(const Complexe &z);
    Complexe sub(const Complexe &z);
    Complexe mul(const Complexe &z);

    Complexe &operator=(const Complexe &c1);
    Complexe &operator+=(const Complexe &c1);

  private:
    friend bool operator==(const Complexe &c1, const Complexe c2);
    friend bool operator!=(const Complexe &c1, const Complexe c2);
    friend bool operator!(const Complexe &c1);
    friend Complexe operator+(const Complexe &c1, const Complexe c2);
    friend Complexe operator-(const Complexe &c1, const Complexe c2);
    friend Complexe operator*(const Complexe &c1, const Complexe c2);
    friend Complexe operator/(const Complexe &c1, const Complexe c2);
    friend ostream &operator<<(ostream &os, const Complexe &z);
    friend istream &operator>>(istream &is, Complexe &z);
    double _Re, _Im;
};

#endif