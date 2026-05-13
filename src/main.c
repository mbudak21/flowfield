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

    Image image = {
        .data = noise_buff,
        .width = screenWidth,
        .height = screenHeight,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_GRAYSCALE
    };
    Texture2D texture = LoadTextureFromImage(image);

    while (!WindowShouldClose())
    {
        #pragma omp parallel for schedule(dynamic)
        for (int j = 0; j < screenHeight; j++) {
            for (int i = 0; i < screenWidth; i++) {
                double value = open_simplex_noise4(ctx, i*noise_Size, j*noise_Size, td, 0);
                value = open_simplex_noise2(ctx, value - 1, value);
                noise_buff[j*screenWidth + i] = (uint8_t)((value + 1) * 127.5);
            }
        }
        td += 0.01;

        UpdateTexture(texture, noise_buff);

        BeginDrawing();
            DrawTexture(texture, 0, 0, WHITE);
            DrawText("RayLib", 190, 200, 20, LIGHTGRAY);
        EndDrawing();

        printf("%f\n", GetFrameTime());
    }

    UnloadTexture(texture);
    CloseWindow();
    return 0;
}
