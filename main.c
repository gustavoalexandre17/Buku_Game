#include "raylib.h"

int main(void)
{
    InitWindow(600, 600, "Buku Game");

    if (!IsWindowReady())
        return 1;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Gildo Viado", 200, 280, 30, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
