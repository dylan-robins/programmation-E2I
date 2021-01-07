#include "forme.h"

#include <cmath>
#include <iostream>

using namespace std;

Coords::Coords() : _x(0), _y(0) {}
Coords::Coords(const double x, const double y) : _x(x), _y(y) {}

void Coords::translate(double dx, double dy) {
    _x += dx;
    _y += dy;
}

ostream &operator<<(ostream &os, const Coords &coords) {
    os << "(" << coords._x << "," << coords._y << ")";
}

Shape::Shape() : _center(0, 0) {
    cout << "- Shape::Shape() -";
}
Shape::Shape(const double x, const double y) : _center(x, y) {
    cout << "- Shape::Shape() -";
}

void Shape::translate(double dx, double dy) {
    _center.translate(dx, dy);
}

ostream &operator<<(ostream &os, const Shape &shape) {
    os << shape._center;
}

Circle::Circle(const double x, const double y, const double radius) : Shape(x, y), _radius(radius) {
    cout << "- Circle::Circle() -";
}

double Circle::perimeter() const {
    return 2 * M_PI * _radius;
}

double Circle::area() const {
    return M_PI * pow(_radius, 2);
}

ostream &operator<<(ostream &os, const Circle &c) {
    os << (const Shape&)c << ", radius = " << c._radius;
}

Rectangle::Rectangle(const double x, const double y, const double width, const double height) : Shape(x, y), _width(width), _height(height) {
    cout << "- Rectangle::Rectangle() -";
}

double Rectangle::perimeter() const {
    return 2 * _width + 2 * _height;
}

double Rectangle::area() const {
    return _width * _height;
}

ostream &operator<<(ostream &os, const Rectangle &c) {
    os << (const Shape&)c << ", width = " << c._width << ", height = " << c._height;
}

Square::Square(const double x, const double y, const double side) : Rectangle(x, y, side, side) {
    cout << "- Square::Square() -";
}

// equilateral triangle
Triangle::Triangle(const double x, const double y, const double side) : Shape(x, y), _base(side), _height(acos(M_PI / 6) * side) {
    cout << "- Triangle::Triangle() -";
}

// isocelese triangle
Triangle::Triangle(const double x, const double y, const double base, const double height) : Shape(x, y), _base(base), _height(height) {
    cout << "- Triangle::Triangle() -";
}

double Triangle::perimeter() const {
    return _base + 2 * (_height / cos(M_PI / 6));
}

double Triangle::area() const {
    return _base * _height / 2;
}

ostream &operator<<(ostream &os, const Triangle &c) {
    os << (const Shape&)c << ", base = " << c._base << ", height = " << c._height;
}

double area(Shape &s) {
    return s.area();
}