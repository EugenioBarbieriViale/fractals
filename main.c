#include <stdio.h>
#include <math.h>
#include <raylib.h>

#define square(x) (x)*(x)

int main() {
    const int X = 400;
    const int Y = 400;

    double zoomy = 1.f;
    double zoomx = 1.f;

    double step = 0.1f;
    int max_iterations = 100;

    InitWindow(X, Y, "Mandelbrot");
    SetTargetFPS(30);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyDown(KEY_UP)) 
            zoomy -= step;

        if (IsKeyDown(KEY_DOWN)) 
            zoomy += step;

        if (IsKeyDown(KEY_RIGHT))
            zoomx -= step;

        if (IsKeyDown(KEY_LEFT)) 
            zoomx += step;

        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
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
                
                int brightness = n / max_iterations * 255;
                if (n == max_iterations)
                    brightness = 255;

                Color col = {brightness, brightness, brightness, brightness};
                DrawPixel(x, y, col);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
