#include <raylib.h>
#include <raymath.h>

#define square(x) (x)*(x)

const int X = 600;
const int Y = 600;

const double zoomy = 2.f;
const double zoomx = 3.f;

const int max_iterations = 100;

void mandelbrot(int, int, double, double, double);
Color gradient(int n);

int main() {
    InitWindow(X, Y, "Mandelbrot");
    SetTargetFPS(30);

    Camera2D camera = {0};
    camera.zoom = 1.0f;
    camera.target = (Vector2){X/2, Y/2};

    int W = 600;
    int H = 600;

    double min_re = -2;
    double max_re = 1.5;
    double min_im = -2;

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

                mandelbrot(W, H, min_re, max_re, min_im);

            EndMode2D();

        EndDrawing();
    }


    CloseWindow();
    return 0;
}

void mandelbrot(int W, int H, double min_re, double max_re, double min_im) {
    double max_im = min_im + (max_re - min_re) * (double)H / (double)W;

    double re_factor = (max_re - min_re) / (double)W;
    double im_factor = (max_im - min_im) / (double)H;

    for (int y = -H; y < H; y++) {
        for (int x = -W; x < W; x++) {
            double a = min_re + x * re_factor;
            double b = max_im - y * im_factor;

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
            DrawPixel(x + W/2, y + H/2, col);
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
