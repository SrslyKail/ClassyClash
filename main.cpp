#include "raylib.h"
#include "raymath.h"

class Character
{
public:
private:
};

int main()
{
    float windowDimensions[2]{384, 384};
    InitWindow(windowDimensions[0], windowDimensions[1], "Top-down Game");

    Texture2D map = LoadTexture("Textures/nature_tileset/OpenWorldMap24x24.png");

    Texture2D playerIdle = LoadTexture("Textures/characters/knight_idle_spritesheet.png");
    Texture2D playerMove = LoadTexture("Textures/characters/knight_run_spritesheet.png");
    Texture2D playerSheet{playerIdle};
    const int playerSpriteScale{4};

    // character animation variables
    float runningTime{};
    int frame{};
    const int maxFrame{6};
    const float updateTime{1.0 / 12.0};

    // 1= right, -1 = left. Used for flipping sprite
    float rightleft{1.f};

    Vector2 playerPosition{
        (windowDimensions[0] / 2) - (playerSpriteScale * playerSheet.width / maxFrame) / 2.f,
        (windowDimensions[1] / 2) - (playerSpriteScale * playerSheet.height) / 2.f};
    float playerSpeed{0.1};

    Vector2 mapPosition{0.0, 0.0};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};

        // check for directional inputs and apply force
        if (IsKeyDown(KEY_A) or IsKeyDown(KEY_LEFT))
            direction.x -= 1;
        if (IsKeyDown(KEY_D) or IsKeyDown(KEY_RIGHT))
            direction.x += 1;
        if (IsKeyDown(KEY_W) or IsKeyDown(KEY_UP))
            direction.y -= 1;
        if (IsKeyDown(KEY_S) or IsKeyDown(KEY_DOWN))
            direction.y += 1;

        // if directional input found, set the new map position
        if (Vector2Length(direction) != 0.0)
        {
            mapPosition = Vector2Subtract(
                mapPosition,
                Vector2Scale(
                    Vector2Normalize(direction), // normalized direction so diagonal movement isnt faster than cardinal
                    playerSpeed));               // scale by player speed, to control rate of movement

            // if direction is less than zero, player must be moving right
            direction.x < 0.f ? rightleft = -1.f : rightleft = 1.f;
            playerSheet = playerMove;
        }
        else
            playerSheet = playerIdle;

        // Draw the map
        DrawTextureEx(map, mapPosition, 0, 4, WHITE);

        // update animation frame
        //  add deltaTime to time since last update
        runningTime += GetFrameTime();
        // if more time has passed than the fps of the animation
        if (runningTime >= updateTime)
        {
            // reset RunningTime
            runningTime = 0.0;

            // if we're at the last frame
            if (frame >= maxFrame)
            {
                // go back to the first frame
                frame = 0;
            }
            else
            {
                // go to the next game
                frame++;
            }
        }

        // Get the sprite from the current sprite sheet
        Rectangle source{
            (playerSheet.width / maxFrame) * (float)frame,
            0.f,
            rightleft * (playerSheet.width / maxFrame),
            (float)playerSheet.height};

        // where to put the sprite on the screen
        Rectangle dest{
            playerPosition.x,
            playerPosition.y,
            playerSpriteScale * playerSheet.width / (float)maxFrame,
            playerSpriteScale * (float)playerSheet.height};

        // Draw the player
        DrawTexturePro(playerSheet, source, dest, Vector2{}, 0.f, WHITE);

        EndDrawing();
    }

    CloseWindow();
    UnloadTexture(map);

    return 1;
}