#ifndef __VECTEUR3D_H__
#define __VECTEUR3D_H__

class Vecteur3d
{
private:
    double _data[3];
    enum field_t { x = 0, y = 1, z = 2 };

public:
    Vecteur3d();
    Vecteur3d(const double x, const double y, const double z);
    double get(const unsigned long champs);
    double get(field_t champs);
    void set(const unsigned long champs, double data);
    void set(field_t champs, double data);
    void display();
};

#endif