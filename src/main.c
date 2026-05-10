#include "raylib.h"
#include "open-simplex-noise.h"
#include <stdio.h>
#include <sys/types.h>


int main(void) {
    // Initialization
    const int screenWidth = 800*2;
    const int screenHeight = 450*2;
    const double noise_Size = 0.03;
    double td = 0;

    InitWindow(screenWidth, screenHeight, "Flowfield");
    struct osn_context *ctx;
    open_simplex_noise(0, &ctx);
    

    SetTargetFPS(60);
    u_int8_t noise_buff[screenWidth*screenHeight];

    while (!WindowShouldClose())
    {


        for (int i = 0; i < screenWidth; i++) {
            for (int j = 0; j < screenHeight; j++) {
                double value = open_simplex_noise4(ctx, i*noise_Size, j*noise_Size, td, 0);
                uint32_t rgb = (uint32_t) ((value + 1) * 127.5);
                noise_buff[j*screenWidth + i] = rgb;
            }
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            for (int i = 0; i < screenWidth; i++) {
                for (int j = 0; j < screenHeight; j++) {
                    int val = noise_buff[j*screenWidth + i];
                    Color col = (Color){val, val, val, 255};
                    DrawPixel(i, j, col);
                }
            }
            td += 0.05;

            DrawText("RayLib", 190, 200, 20, LIGHTGRAY);

        EndDrawing();

        printf("%f\n", GetFrameTime());
    }

    CloseWindow();
    return 0;
}
