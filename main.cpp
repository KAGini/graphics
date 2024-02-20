#include <fstream>
#include <iostream>
#include "geometry.h"

using namespace std;

const string OutFileName = "photo.ppm";
const string ConfigFileName = "config.txt";

class Color {
public:
    Color() {
        r = 0;
        g = 0;
        b = 0;
    }
    Color(double _r, double _g, double _b): r(_r), g(_g), b(_b) {}

    double r;
    double g;
    double b;

    string ToPrint(int L) {
        return to_string(int(r * L)) + " " + to_string(int(g * L)) + " " + to_string(int(b * L));
    }
};

void SetCircle(vector<vector<Color>>& screen, Circle cq, Color clr) {
    auto sqr = [] (double x) { return x * x; };
    int N = screen.size();
    int M = screen[0].size();

    for (int i = max(0, int(cq.LU.x)); i < min(N, int(cq.RD.x)); ++i) {
        for (int j = max(0, int(cq.LU.y)); j < min(M, int(cq.RD.y)); ++j) {
            if (sqr(j - cq.O.x) + sqr(i - cq.O.y) <= sqr(cq.R)) {
                screen[i][j] = clr;
            }
        }
    }

}

void SetPolygon(vector<vector<Color>>& screen, Polygon& pol, Color clr) {
    int N = screen.size();
    int M = screen[0].size();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (CountIntersections(Point(j, i), pol) % 2) {
                screen[i][j] = clr;
            }
        }
    }
}

void RenderPPM(vector<vector<Color>>& screen) {
    ofstream fout(OutFileName);

    fout << "P3\n";
    fout << screen[0].size() << " " << screen.size() << "\n"; 
    fout << "255\n";
    for (int i = 0; i < screen.size(); ++i) {
        for (int j = 0; j < screen[i].size(); ++j) {
            fout << screen[i][j].ToPrint(255) << "\n";
        }
    }

    fout.close();
}

void INIT(int& N, int& M, Color& BGcolor, vector<vector<Color>>& screen) {
    ifstream fin(ConfigFileName);

    fin >> N >> M;
    double r, g, b;
    fin >> r >> g >> b;
    BGcolor = {r, g, b};
    screen.assign(N, vector<Color> (M, BGcolor));
    int t;
    fin >> t;
    for (int i = 0; i < t; ++i) {
        string shape;
        fin >> shape;
        if (shape == "circle") {
            double x, y, R, r, g, b;
            fin >> x >> y >> R >> r >> g >> b;
            SetCircle(screen, Circle({x, y}, R), Color(r, g, b));
        } else if (shape == "polygon") {
            int n;
            fin >> n;
            vector<Point> points(n);
            for (int j = 0; j < n; ++j) {
                double x, y;
                fin >> x >> y;
                points[j] = {x, y};
            }
            double r, g, b;
            fin >> r >> g >> b;
            Polygon pol(n, points);
            SetPolygon(screen, pol, Color(r, g, b)); 
        }
    }

    fin.close();
}

int main() {

    int N, M;
    Color BGcolor;
    vector<vector<Color>> screen;
    INIT(N, M, BGcolor, screen);
    RenderPPM(screen);

    return 0;
}
