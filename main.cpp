#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
    float windowWidth{384};
    float windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Top-down Game");

    Texture2D map = LoadTexture("Textures/nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPosition{0.0, 0.0};
    const int mapScale{4};

    Character player;

    player.setScreenPosition(windowWidth, windowHeight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        float deltaTime{GetFrameTime()};

        mapPosition = Vector2Scale(player.getWorldPosition(), -1);
        // Draw the map
        DrawTextureEx(map, mapPosition, 0, mapScale, WHITE);
        player.tick(deltaTime);

        // check map boundaries
        if (player.getWorldPosition().x < 0.f ||
            player.getWorldPosition().y < 0.f ||
            player.getWorldPosition().x + windowWidth > map.width * mapScale ||
            player.getWorldPosition().y + windowHeight > map.height * mapScale)
        {
            player.undoMovement();
        }

        EndDrawing();
    }

    CloseWindow();

    return 1;
}