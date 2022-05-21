#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 getWorldPosition() { return worldPosition; }
    Vector2 getScreenPosition() { return screenPosition; }
    void setScreenPosition(int screenWidth, int screenHeight);
    void tick(float deltaTime);
    float getFrame() { return frame; }

private:
    // textures
    Texture2D currentTexture{LoadTexture("Textures/characters/knight_idle_spritesheet.png")};
    Texture2D idleTexture{LoadTexture("Textures/characters/knight_idle_spritesheet.png")};
    Texture2D runTexture{LoadTexture("Textures/characters/knight_run_spritesheet.png")};
    // positions
    Vector2 screenPosition{};
    Vector2 worldPosition{};
    // animation variables
    int frame{};
    const int maxFrame{6};
    const float updateTime{1.0 / 12.0};
    float runningTime{};
    float rightLeft{1.f}; // 1= right, -1 = left. Used for flipping sprite
    float spriteScale{4};

    // gameplay variables
    float speed{4};
};

void Character::setScreenPosition(int screenWidth, int screenHeight)
{
    screenPosition = {
        (screenWidth / 2) - (spriteScale * (currentTexture.width / maxFrame) / 2.f),
        (screenHeight / 2) - (spriteScale * currentTexture.height / 2.f)};
}

void Character::tick(float deltaTime) // things we want to do every frame
{
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
        worldPosition = Vector2Add(worldPosition, Vector2Scale(
                                                      Vector2Normalize(direction), // normalized direction so diagonal movement isnt faster than cardinal
                                                      speed));                     // scale by player speed, to control rate of movement

        // if direction is less than zero, player must be moving right
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        currentTexture = runTexture;
    }
    else
    {
        currentTexture = idleTexture;
    }
    // update animation frame
    runningTime += deltaTime;
    // if more time has passed than the fps of the animation
    if (runningTime >= updateTime)
    {
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
        // reset RunningTime
        runningTime = 0.0;
    }
    // Get the sprite from the current sprite sheet
    Rectangle source{
        (frame * currentTexture.width) / (float)maxFrame,
        0.f,
        rightLeft * currentTexture.width / maxFrame,
        (float)currentTexture.height};

    // where to put the sprite on the screen
    Rectangle dest{
        screenPosition.x,
        screenPosition.y,
        spriteScale * currentTexture.width / (float)maxFrame,
        spriteScale * (float)currentTexture.height};

    // Draw the player
    DrawTexturePro(currentTexture, source, dest, Vector2{}, 0.f, WHITE);
}

int main()
{
    float windowWidth{384};
    float windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Top-down Game");

    Texture2D map = LoadTexture("Textures/nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPosition{0.0, 0.0};

    Character player;
    player.setScreenPosition(windowWidth, windowHeight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPosition = Vector2Scale(player.getWorldPosition(), -1);

        // Draw the map
        DrawTextureEx(map, mapPosition, 0, 4, WHITE);
        player.tick(GetFrameTime());

        EndDrawing();
    }

    CloseWindow();

    return 1;
}