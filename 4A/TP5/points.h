#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>

using namespace std;

/*****************************************************************************/
/*                          Réponses aux questions                           */
/*                                                                           */
/* Q1.2 :                                                                    */
/*     L'instruction `Pointcol P1(2.5, 3.25, 5);` ne fonctionne pas étant    */
/*     donné que j'ai numéroté mes couleurs selon leur valeur ANSI au lieu   */
/*     de 0 à N. Si j'avais numéroté mes couleurs de la façon attendue,      */
/*     l'instruction crééerait un point de coordonnées (2.5,3.25) et de      */
/*     couleur bleue.                                                        */
/*                                                                           */
/* Q1.3 :                                                                    */
/*     Pour implémenter Pointcol sans héritage il faudrait dupliquer toutes  */
/*     les fonctionnalités communes (membres communs, constructeur, fonction */
/*     deplace(). Aussi, aujourd'hui si on définit une fonction qui prend    */
/*     en argument un élément de type Point, on peut lui passer un Pointcol  */
/*     implicitement étant donné que le compilateur sait qu'un Pointcol est  */
/*     une extension de la classe Point. Sans héritage, ce mécanisme ne      */
/*     serait pas possible.                                                  */
/*****************************************************************************/

enum col_t {
    reset = 0,
    black = 30,
    red = 31,
    green = 32,
    yellow = 33,
    blue = 34,
    magenta = 35,
    cyan = 36,
    white = 37
};

class Colour {
public:

    Colour() : _col(col_t::reset) {};
    Colour(const col_t c) : _col(c) {};
private:
    col_t _col;
    friend ostream& operator<<(ostream& os, const Colour& col);
};

class Point {
public:
    Point(double abs, double ord);
    void affiche() const;
    void deplace(double dx, double dy);

    double get_x() const {return _x;}
    double get_y() const {return _y;}

private:
    double _x, _y;
    friend ostream& operator<<(ostream& os, const Point& point);
};

class Pointcol : public Point {
public:
    Pointcol();
    Pointcol(const double abs, const double ord);
    Pointcol(const double abs, const double ord, const Colour col);

    void affiche() const;
    void set_colour(const Colour col);
    Colour get_colour() const {return _colour;}

private:
    Colour _colour;

    friend ostream& operator<<(ostream& os, const Pointcol& col);
};

#endif