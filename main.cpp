#include "raylib.h"
#include "raymath.h"

int main()
{
    int windowDimensions[2]{384, 384};

    InitWindow(windowDimensions[0], windowDimensions[1], "Top-down Game");

    Texture2D map = LoadTexture("Textures/nature_tileset/OpenWorldMap24x24.png");

    Texture2D playerIdle = LoadTexture("Textures/characters/knight_idle_spritesheet.png");
    // Texture2D playerMove = LoadTexture("Textures/characters/knight_run_spritesheet.png");
    float playerSpriteScale{4};
    Vector2 playerPosition{
        (windowDimensions[0]/2) - (playerSpriteScale * playerIdle.width/6),
        (windowDimensions[1]/2) - (playerSpriteScale * playerIdle.height)
    };
    


    Vector2 mapPosition{0.0, 0.0};
    float playerSpeed{0.25};
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};

        //check for directional inputs and apply force
        if (IsKeyDown(KEY_A) or IsKeyDown(KEY_LEFT)) direction.x -= 1;
        if (IsKeyDown(KEY_D) or IsKeyDown(KEY_RIGHT)) direction.x += 1;
        if (IsKeyDown(KEY_W) or IsKeyDown(KEY_UP)) direction.y -= 1;
        if (IsKeyDown(KEY_S) or IsKeyDown(KEY_DOWN)) direction.y += 1;

        //if directional input found, set the new map position
        if (Vector2Length(direction) != 0.0)
        {
            mapPosition = Vector2Subtract(mapPosition, Vector2Scale(
                Vector2Normalize(direction), //normalized direction so diagonal movement isnt faster than cardinal
                playerSpeed)); //scale by player speed, to control rate of movement
        }
        

        //Draw the map
        DrawTextureEx(map, mapPosition, 0, 4, WHITE);
        //Draw the player
        Rectangle source{0.f, 0.f, (float)(playerIdle.width/6), (float)playerIdle.height};
        Rectangle dest{playerPosition.x, playerPosition.y, playerSpriteScale * playerIdle.width/6, playerSpriteScale* playerIdle.height};
        DrawTexturePro(playerIdle, source, dest, Vector2{}, 0, WHITE);

        EndDrawing();
    }

    CloseWindow();
    UnloadTexture(map);

    return 1;
}