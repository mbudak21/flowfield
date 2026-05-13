#include "raylib.h"
#include <stdio.h>

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

int main(void) {
    double t0 = GetTime(); 
    
    const int screenWidth = 1600;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "RayLib");
    SetTargetFPS(60);

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    Shader shader = LoadShader("src/shaders/simple_vert.vert", "src/shaders/simple_frag.frag");

    int resLoc = GetShaderLocation(shader, "uResolution");
    int timeLoc = GetShaderLocation(shader, "uTime");
    int mouseLoc = GetShaderLocation(shader, "uMouseCoords");

    float resolution[2] = { (float)screenWidth-20, (float)screenHeight-20 };
    float time = 0.0f;

    
    double t1 = GetTime();
    printf("Total Init Time: %f ms\n", (t1 - t0) * 1000.0);

    while (!WindowShouldClose())
    {
        double tn_0 = GetTime();
        float mouseCoord[2] = { (float)GetMouseX(), (float)(screenHeight - GetMouseY()) };

        
        // Logic
        time = GetTime();
        SetShaderValue(shader, resLoc, resolution, SHADER_UNIFORM_VEC2);
        SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, mouseLoc, mouseCoord, SHADER_UNIFORM_VEC2);

        // BeginTextureMode(target);   
        //     ClearBackground(WHITE);
        // EndTextureMode();

        double tn_1 = GetTime();

        BeginDrawing();
            ClearBackground(BLACK);

            BeginShaderMode(shader);
                DrawRectangle(10, 10, screenWidth-20, screenHeight-20, RED);
            EndShaderMode();

            DrawText("RayLib", 190, 200, 20, LIGHTGRAY);
            
            // Displaying the raw data in the window
            DrawText(TextFormat("Logic: %.4f ms", (tn_1 - tn_0) * 1000.0), 20, 20, 20, GREEN);
            DrawText(TextFormat("Draw:  %.4f ms", (GetTime() - tn_1) * 1000.0), 20, 50, 20, SKYBLUE);
            
            DrawText(TextFormat("FPS:  %i", GetFPS()), 20, 80, 20, SKYBLUE);
        EndDrawing();
        
        double tn_2 = GetTime();

        // 4. Print Frame Summary to Console
        // Total "Work" Time vs Frame Time
        printf("Logic: %.3fms | Draw: %.3fms | Total: %.3fms\r", 
                (tn_1 - tn_0) * 1000.0, (tn_2 - tn_1) * 1000.0, (tn_1 - tn_0) * 1000.0 + (tn_2 - tn_1) * 1000.0);
        fflush(stdout);
    }

    CloseWindow();
    return 0;
}