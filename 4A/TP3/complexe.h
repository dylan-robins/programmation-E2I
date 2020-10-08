#ifndef __COMPLEXE_H__
#define __COMPLEXE_H__

class Complexe {
private:
    double _Re, _Im;

public:
    Complexe() : _Re(0), _Im(0) {};
    Complexe(double re, double im) : _Re(re), _Im(im) {};
    void afficher();
    double re();
    double im();
    Complexe add(const Complexe &z);
    Complexe sub(const Complexe &z);
    Complexe mul(const Complexe &z);
};

#endif