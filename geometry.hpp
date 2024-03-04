#include <vector>
#include <cmath>
#include <string>

const double eps = 1e-9;
const double INF = 1e9;

class Color {
public:
    Color(): r(0), g(0), b(0) {}
    Color(double _r, double _g, double _b): r(_r), g(_g), b(_b) {}

    double r, g, b;

    Color operator* (double k) {
        if (k < 0) k = 0;
        return Color(fmin(1.0, r * k), fmin(1.0, g * k), fmin(1.0, b * k));
    }

    std::string ToPrint(double L) {
        return std::to_string(int(r * L)) + " " + std::to_string(int(g * L)) + " " + std::to_string(int(b * L));
    }    
};

class Point {
public:
    Point(): x(0), y(0), z(0) {}
    Point(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}

    double x, y, z;

    Point operator+(Point rhs) {
        return Point(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    Point operator-(Point rhs) {
        return Point(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    bool operator==(Point rhs) {
        auto AreEqual = [] (double lhs, double rhs) { return std::abs(lhs - rhs) < eps; };
        return AreEqual(x, rhs.x) && AreEqual(y, rhs.y) && AreEqual(z, rhs.z);
    }
};

double GetDistance(Point A, Point B) {
    auto sq = [] (double x) { return x * x; };
    return sqrt(sq(A.x - B.x) + sq(A.y - B.y) + sq(A.z - B.z));
}

class Vector {
public:
    Vector(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}
    Vector(Point A = {0, 0, 0}): x(A.x), y(A.y), z(A.z) {}
    Vector(Point A, Point B) {
        x = B.x - A.x;
        y = B.y - A.y;
        z = B.z - A.z;
    }

    double x, y, z;

    Vector operator+(const Vector rhs) {
        return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    Vector operator-(const Vector rhs) {
        return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    Vector operator*(double k) {
        return Vector(x * k, y * k, z * k);
    }

    Vector operator/(double k) {
        return Vector(x / k, y / k, z / k);
    }

    double GetLength() {
        return sqrt(x * x + y * y + z * z);
    }

    Vector GetNormalized() {
        Vector a(x, y, z);
        return *(this) / this->GetLength();
    }
};

Vector GetReflection(Vector a, Vector norm) {
    a = a.GetNormalized();
    norm = norm.GetNormalized();
    return Vector();
}

Point operator+ (Point A, Vector B) {
    return Point(A.x + B.x, A.y + B.y, A.z + B.z);
}

double GetDotProduct(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

class Sphere {
public:   
    Sphere(double _x = 0, double _y = 0, double _z = 0, double _r = 0, Color clr = Color()): 
        O(Point(_x, _y, _z)), r(_r), color(clr) 
    {}
    Sphere(Point A, double _r, Color clr): O(A), r(_r), color(clr) {}

    Point O;
    double r;
    Color color;

    bool operator==(Sphere rhs) {
        return O == rhs.O && abs(r - rhs.r) < eps;
    }

    bool IsBelong(Point A) {
        auto sq = [] (double x) { return x * x; };
        return abs(sq(Vector(A - O).GetLength()) - sq(r)) < eps;
    }
};

class Ray {
public:    
    Ray(): C(Point()), d(1, 0, 0) {}
    Ray(Point _C, Vector _d): C(_C), d(_d.GetNormalized()) {}
    
    Point C;
    Vector d;
};

Point GetIntersection(Sphere S, Ray r) {
    auto sq = [] (double x) { return x * x; };
    double a = sq(r.d.GetLength());
    double b = 2 * GetDotProduct(r.d, Vector(r.C - S.O));
    double c = sq(Vector(r.C - S.O).GetLength()) - sq(S.r);
    double dis = sq(b) - 4 * a * c;
    if (dis < -eps) {
        return Point(INF, INF, INF);
    }
    dis = std::abs(dis);
    double t1 = (-b + sqrt(dis)) / (2 * a);
    double t2 = (-b - sqrt(dis)) / (2 * a);
    double t = t2 > -eps ? t2 : t1;
    if (t < -eps) {
        return Point(INF, INF, INF);
    }
    return r.C + r.d * t;
}
