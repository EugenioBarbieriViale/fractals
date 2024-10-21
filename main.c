#include <raylib.h>
#include <raymath.h>

#define square(x) (x)*(x)

const int X = 600;
const int Y = 600;
const int shiftx = 100;

const double zoomy = 2.f;
const double zoomx = 3.f;

const int max_iterations = 100;

void mandelbrot();

int main() {
    InitWindow(X, Y, "Mandelbrot");
    SetTargetFPS(30);

    Camera2D camera = {0};
    camera.zoom = 1.0f;

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

                mandelbrot();

            EndMode2D();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void mandelbrot() {
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
}

