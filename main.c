#include <stdio.h>
#include <math.h>
#include <raylib.h>

#define square(x) (x)*(x)

int main() {
    const int X = 600;
    const int Y = 600;
    const int shiftx = 100;

    const double zoomy = 2.f;
    const double zoomx = 3.f;

    const int max_iterations = 100;

    InitWindow(X, Y, "Mandelbrot");
    SetTargetFPS(30);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        for (int y = -Y/2; y < Y/2; y++) {
            for (int x = -X/2; x < X/2; x++) {
                double a = (double)x / (double)X * zoomx;
                double b = (double)y / (double)Y * zoomy;

                double pa = a;
                double pb = b;

                int n = 0;
                while (n < max_iterations) {
                    double re = square(a) - square(b);
                    double im = 2 * a * b;

                    a = re + pa;
                    b = im + pb;

                    if (square(a) + square(b) > 2)
                        break;

                    n++;
                }
                
                double brightness = (double)n / (double)max_iterations * 255.f;

                Color col = {brightness, brightness, brightness, 255};
                DrawPixel(x+X/2+shiftx, y+Y/2, col);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
