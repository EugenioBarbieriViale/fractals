#include <raylib.h>
#include <raymath.h>

#define square(x) (x)*(x)

const int X = 600;
const int Y = 600;

const int shiftx = 100;
const int shifty = 50;

const double zoomy = 2.f;
const double zoomx = 3.f;

const int max_iterations = 100;

void mandelbrot();
Color gradient(int n);

int main() {
    InitWindow(X, Y, "Mandelbrot");
    SetTargetFPS(30);

    Camera2D camera = {0};
    camera.zoom = 1.0f;
    camera.target = (Vector2){X/2, Y/2};

    int W = X;
    int H = Y;

    while (!WindowShouldClose()) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera.zoom);
            camera.target = Vector2Add(camera.target, delta);
        }

        float wheel = GetMouseWheelMove();
        if (wheel != 0) {
            camera.offset = GetMousePosition();

            float scale_factor = 1.0f + (0.25f * fabsf(wheel));
            if (wheel < 0) 
                scale_factor = 1.0f / scale_factor;

            camera.zoom = Clamp(camera.zoom * scale_factor, 0.125f, 64.0f);
        }

        BeginDrawing();
        ClearBackground(BLACK);

            BeginMode2D(camera);

                mandelbrot(W, H);

            EndMode2D();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void mandelbrot(int X, int Y) {
    for (int y = -Y/2 - shifty; y < Y/2 + shifty; y++) {
        for (int x = -X/2 - shiftx; x < X/2; x++) {
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

                if (square(a) + square(b) > 100)
                    break;

                n++;
            }
            
            Color col = gradient(n);
            DrawPixel(x + X, y + Y, col);
        }
    }
}

Color gradient(int n) {
    double bright = (double)n / (double)max_iterations * 255.f;

#if 0
    return (Color){bright, bright, bright, 255};

#else
    unsigned char r = (unsigned char)(9.f * (1.f - bright) * bright * bright * bright * 255.f);
    unsigned char g = (unsigned char)(15.f * (1.f - bright) * (1.f - bright) * bright * bright * 255.f);
    unsigned char b = (unsigned char)(8.5 * (1.f - bright) * (1.f - bright) * (1.f - bright) * bright * 255.f);

    return (Color){r, g, b, 255};
#endif
}
