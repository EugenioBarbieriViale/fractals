#include <iostream>
#include <vector>
#include <complex>
#include <raylib.h>


using namespace std;

#define square(x) (x)*(x)

typedef struct {
    int dim;
    vector<complex<double>> plane;
} Plane;

vector<double> linspace(double a, double b, int n) {
    vector<double> v(n);
    for (int i=0; i<=n; i++)
        v[i] = a + i * ((b - a) / (double)n);
    return v;
}

vector<complex<double>> complex_plane(int xmin, int xmax, int ymin, int ymax, int density) {
    vector<double> re = linspace(xmin, xmax, density);
    vector<double> im = linspace(ymin, ymax, density);

    vector<complex<double>> plane(square(density));
    for (int i=0; i<density; i++)
        for (int j=0; j<density; j++)
            plane[i * density + j] = re[j] + im[i] * 1i;

    return plane;
}

vector<bool> find_stable(vector<complex<double>> plane, int n_iterations) {
    ; 
}

void print_plane(vector<complex<double>> plane, int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++)
            cout << plane[i * n + j] << " ";
        cout << endl;
    }
}

int main() {
    int n = 10;
    vector<complex<double>> plane = complex_plane(0, 5, 0, 5, n);


    // const int X = 1000;
    // const int Y =  800;

    // InitWindow(X, Y, "Mandelbrot");
    // SetTargetFPS(30);

    // while (!WindowShouldClose()) {
    //     BeginDrawing();
    //     ClearBackground(BLACK);

    //     EndDrawing();
    // }

    // CloseWindow();
    // return 0;
}
