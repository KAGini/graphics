#include <vector>
#include <cmath>

class Point {
public:
    Point(): x(0), y(0), z(0) {}
    Point(double _x, double _y, double _z): x(_x), y(_z), z(_z) {}

    double x, y, z;
};

class Vector {
public:
    Vector(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}
    Vector(Point A, Point B = {0, 0, 0}) {
        x = A.x - B.x;
        y = A.y - B.y;
        z = A.z - B.z;
    }

    double x, y, z;
};

double GetDotProduct(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

class Line {
public:    
    Line(): a(1), b(1), c(1), d(0) {}
    Line(double _a, double _b, double _c, double _d): a(_a), b(_b), c(_c), d(_d) {}

    double a, b, c, d;
};

class Sphere {
public:    
    Sphere(double _x = 0, double _y = 0, double _z = 0, double _r = 0): 
        x0(_x), y0(_y), z0(_z), r(_r) 
    {}

    double x0, y0, z0, r;

    bool IsBelong(Point A) {
    auto sq = [] (double x) { return x * x; };
    return sq(A.x - x0) + sq(A.y - y0) + sq(A.z - z0) <= sq(r);
}
};

class Ray {
public:    
    Ray(): x0(0), y0(0), z0(0), px(1), py(1), pz(1) {}
    Ray(double _x, double _y, double _z, double _px, double _py, double _pz): 
        x0(_x), y0(_y), z0(_z), px(_px), py(_py), pz(_pz)  
    {}
    Ray(Point A, Vector v): x0(A.x), y0(A.y), z0(A.z), px(v.x), py(v.y), pz(v.z) {}

    double x0, y0, z0, px, py, pz;
};

struct IntersectionPoints {
    IntersectionPoints(): n(0) {}

    int n;
    Point points[2];
};

IntersectionPoints GetIntersection(Ray r, Sphere s);
