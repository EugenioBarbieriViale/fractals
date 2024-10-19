#include <iostream>
#include <vector>
#include <complex>
#include <raylib.h>


using namespace std;

#define square(x) (x)*(x)

typedef struct {
    int dim;
    int density;
    vector<complex<double>> mat;
} Plane;

vector<double> linspace(double a, double b, int n) {
    vector<double> v(n);
    for (int i=0; i<=n; i++)
        v[i] = a + i * ((b - a) / (double)n);
    return v;
}

vector<complex<double>> complex_mat(Plane p) {
    vector<double> re = linspace(0, p.dim, p.density);
    vector<double> im = linspace(0, p.dim, p.density);

    vector<complex<double>> mat;

    for (int i=0; i<p.density; i++)
        for (int j=0; j<p.density; j++)
            mat.push_back(re[j] + im[i] * 1i);
            // mat[i * density + j] = re[j] + im[i] * 1i;

    return mat;
}

void draw_plane(Plane p, int xi, int yi, int r) {
    for (int y = yi; y > yi - p.dim; y -= (int)(p.dim/p.density)) {
        for (int x = xi; x < xi + p.dim; x += (int)(p.dim/p.density)) {
            DrawCircle(x, y, r, RED);
        }
    }
}

void print_plane(Plane p) {
    for (int i=0; i<p.density; i++) {
        for (int j=0; j<p.density; j++)
            cout << p.mat[i * p.density + j] << " ";
        cout << endl;
    }
}

int main() {
    const int L = 800;

    int r = 5;
    int xi = r*2;
    int yi = L - r*2;

    Plane p;

    p.dim = L - r*2;
    p.density = 50;
    p.mat = complex_mat(p);

    InitWindow(L, L, "Mandelbrot");
    SetTargetFPS(30);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        draw_plane(p, xi, yi, r);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
