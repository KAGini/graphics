#include <fstream>
#include <string>
#include "geometry.hpp"

using namespace std;

const string INPUT_FILE_NAME = "config.txt";
const string OUTPUT_FILE_NAME = "photo.ppm";

class Color {
public:
    Color(): r(0), g(0), b(0) {}
    Color(double _r, double _g, double _b): r(_r), g(_g), b(_b) {}

    double r, g, b;

    string ToPrint(double L) {
        return to_string(int(r * L)) + " " + to_string(int(g * L)) + " " + to_string(int(b * L));
    }    
};

class Light: public Ray {
public:
    Light(): Ray(), brightness(1) {}
    Light(double _x, double _y, double _z, double _px, double _py, double _pz, double bright): 
        Ray(x0, y0, z0, px, py, pz), brightness(bright) 
    {}
    Light(Point A, Vector v, double bright): Ray(A, v), brightness(bright) {}
    
    double brightness;  
};

void RenderPPM(vector<vector<Color>>& screen) {
    ofstream fout(OUTPUT_FILE_NAME);

    int N = screen.size();
    int M = screen[0].size();
    fout << "P3\n";
    fout << M << " " << N << "\n";
    fout << "255\n";

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            fout << screen[i][j].ToPrint(255) << "\n";
        }
    }

    fout.close();
}

void Play() {
    ifstream fin(INPUT_FILE_NAME);

    int N, M;
    Color clr;
    vector<vector<Color>> screen;

    fin >> N >> M;
    double r, g, b;
    fin >> r >> g >> b;
    clr = Color(r, g, b);
    screen.assign(N, vector<Color> (M, clr));

    fin.close();
}

int main() {

    Play();

    return 0;
}