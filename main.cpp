#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main()
{
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Top-down Game");

    Texture2D map = LoadTexture("Textures/nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPosition{0.0, 0.0};
    const int mapScale{4};

    Character player{windowWidth, windowHeight};

    Prop prop_array[2]{
        Prop{Vector2{600, 300}, LoadTexture("Textures/nature_tileset/Rock.png")},
        Prop{Vector2{400, 500}, LoadTexture("Textures/nature_tileset/Log.png")}};
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

        // Draw the props
        for (Prop i : prop_array)
        {
            i.Render(player.getWorldPosition());
        }

        // check map boundaries
        if (player.getWorldPosition().x < 0.f ||
            player.getWorldPosition().y < 0.f ||
            player.getWorldPosition().x + windowWidth > map.width * mapScale ||
            player.getWorldPosition().y + windowHeight > map.height * mapScale)
        {
            player.undoMovement();
        }

        // Check player and prop collision
        for (Prop i : prop_array)
        {
            if (CheckCollisionRecs(player.getCollionRectangle(), i.getCollionRectangle(player.getWorldPosition())))
            {
                player.undoMovement();
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 1;
}