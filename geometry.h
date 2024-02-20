#pragma once

#include "vector"
#include "cmath"

const double PI = acos(-1);
constexpr double eps = 1e-5;
constexpr double INF = 1e9;

class Point {
public:
    Point(): x(0), y(0) {}
    Point(double _x, double _y): x(_x), y(_y) {}

    double x, y;
};

class Polygon {
public:
    Polygon(int _n, std::vector<Point>& _points): n(_n), points(_points) {}

    int n;
    std::vector<Point> points;
};

class Vector {
public:
    Vector(Point B, Point A = {0, 0});

    double x, y;

    void Rotate(double angle);

    Vector GetRotated(double angle);
};

class Circle {
public:

    Circle(Point _O, double _R): O(_O), R(_R) {
        LU = {O.x - R, O.y - R};
        RD = {O.x + R, O.y + R};
    } 

    Point O, LU, RD;
    double R;
};

double GetDotProduct(Vector a, Vector b);

double GetCrossProduct(Vector a, Vector b);

double GetAngle(Vector a, Vector b);

class Line {
public:
    Line(double _a, double _b, double _c): a(_a), b(_b), c(_c) {}

    double a, b, c;

    bool IsBelong(Point A) const;
};

Line GetLine(Point A, Point B);

Point GetLinesIntersection(Line ln1, Line ln2);

double GetDistance(Point A, Point B);

class Segment {
public:
    Point A, B;

    bool IsBelong(Point C) const;
};

class Ray {
public:
    Ray(Point A, Vector v);
    double x0, y0;
    double px, py;

    bool IsBelong(Point A) const;
};

double GetDistance(Line a, Point A);

double GetDistance(Segment a, Point A);

Point GetIntersection(Ray A, Segment AB);

int CountIntersections(Point A, Polygon& pol);
