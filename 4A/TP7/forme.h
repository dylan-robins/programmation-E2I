#ifndef __FORME_H__
#define __FORME_H__

#include <iostream>

using namespace std;

class Coords {
  private:
    double _x;
    double _y;
    friend ostream &operator<<(ostream &os, const Coords &c);

  public:
    Coords();
    Coords(const double x, const double y);
    Coords(const Coords &c);
    ~Coords() {} // default destructor: nothing to do

    void translate(double dx, double dy);
};

class Shape {
  private:
    Coords _center;
    friend ostream &operator<<(ostream &os, const Shape &shape);

  public:
    Shape();
    Shape(const double x, const double y);
    // default destructor: nothing to do here
    virtual void translate(double dx, double dy);
    virtual double perimeter() const {};
    virtual double area() const {};
};

class Circle : virtual public Shape {
  private:
    double _radius;
    friend ostream &operator<<(ostream &os, const Circle &shape);

  public:
    Circle(const double x, const double y, const double radius);
    ~Circle(void) {} // default destructor: nothing to do

    virtual double perimeter() const;
    virtual double area() const;
};

class Rectangle : virtual public Shape {
  private:
    double _width;
    double _height;
    friend ostream &operator<<(ostream &os, const Rectangle &shape);

  public:
    Rectangle(const double x, const double y, const double width, const double height);
    ~Rectangle(void) {} // default destructor: nothing to do

    virtual double perimeter() const;
    virtual double area() const;
};

class Square : public Rectangle {
  public:
    Square(const double x, const double y, const double side);
    ~Square(void) {} // default destructor: nothing to do
};

class Triangle : virtual public Shape {
  private:
    double _base;
    double _height;
    friend ostream &operator<<(ostream &os, const Triangle &shape);

  public:
    // equilateral triangle
    Triangle(const double x, const double y, const double side);
    // isocelese triangle
    Triangle(const double x, const double y, const double base, const double height);
    ~Triangle(void) {} // default destructor: nothing to do

    virtual double perimeter() const;
    virtual double area() const;
};

double area(Shape& s);

#endif