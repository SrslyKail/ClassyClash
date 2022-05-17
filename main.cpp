#include "raylib.h"

int main()
{
    int windowDimensions[2]{384, 384};

    InitWindow(windowDimensions[0], windowDimensions[1], "Top-down Game");

    Texture2D map = LoadTexture("Textures/nature_tileset/OpenWorldMap24x24.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 mapPosition{0.0, 0.0};
        DrawTextureEx(map, mapPosition, 0, 4, WHITE);

        EndDrawing();
    }

    CloseWindow();
    UnloadTexture(map);

    return 1;
}