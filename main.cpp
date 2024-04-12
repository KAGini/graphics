#include <fstream>
#include <iostream>
#include <utility>
#include "geometry.hpp"

using namespace std;

const string INPUT_FILE_NAME = "config.txt";
const string OUTPUT_FILE_NAME = "photo.ppm";

class Light {
public:
    Light(): S(Point()), intensity(1) {}
    Light(Point _S, double _intensity): S(_S), intensity(_intensity) {}

    Point S;
    double intensity;
};

pair<Point, Sphere> GetClosestIntersection(const vector<Sphere>& spheres, Ray r) {
    Point I(INF, INF, INF);
    double mdist = INF;
    Sphere S;
    for (auto& s : spheres) {
        Point I2 = GetIntersection(s, r);
        if (I2.x == INF) continue;
        double dist = GetDistance(I2, r.C);
        if (dist < mdist) {
            mdist = dist;
            I = I2;
            S = s;
        }
    }
    return {I, S};
}

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

void Start() {

    ifstream fin(INPUT_FILE_NAME);

    int N, M;
    const double H = 1, W = double(M) / double(N), D = 1;
    Color bgColor;
    fin >> N >> M;
    fin >> bgColor.r >> bgColor.g >> bgColor.b; 
    vector<vector<Color>> screen(N, vector<Color> (M, bgColor));
    vector<Light> lights;
    vector<Sphere> spheres;
    string type;
    while (fin >> type) {
        if (type == "light") {
            Light light;
            fin >> light.S.x >> light.S.y >> light.S.z;
            light.intensity = 1;
            lights.push_back(light);
        } else if (type == "sphere") {
            Sphere S;
            fin >> S.O.x >> S.O.y >> S.O.z >> S.r >> S.color.r >> S.color.g >> S.color.b;
            spheres.push_back(S);
        }   
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            Vector B = Vector(-W / 2.0 + double(j) * W / double(M), H / 2.0 - double(i) * H / double(N), D);
            Ray r(Point(0, 0, 0), B);
            auto [I, S] = GetClosestIntersection(spheres, r);
            if (I.x == INF) continue;
            double koef = 0;
            for (Light l : lights) {
                Point Il = GetClosestIntersection(spheres, Ray(l.S, Vector(l.S, I))).first;
                if (!(Il == I)) {
                    continue;
                }
                koef += l.intensity * max(0.0, GetDotProduct(Vector(I, l.S).GetNormalized(), Vector(S.O, I).GetNormalized()));
            }
            screen[i][j] = S.color * koef;
        }
    }

    fin.close();

    RenderPPM(screen);
}

int main() {

    Start();

    return 0;
}
