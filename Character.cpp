#include "raylib.h"
#include "raymath.h"
#include "Character.h"

Character::Character(int screenWidth, int screenHeight)
{
    width = currentTexture.width / maxFrame;
    height = currentTexture.height;
    screenPosition = {
        (screenWidth / 2) - (spriteScale * width / 2.f),
        (screenHeight / 2) - (spriteScale * height / 2.f)};
}

void Character::tick(float deltaTime) // things we want to do every frame
{
    Vector2 direction{};
    lastFrameWorldPosition = getWorldPosition();

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
        (frame * currentTexture.width) / static_cast<float>(maxFrame),
        0.f,
        rightLeft * width,
        static_cast<float>(height)};

    // where to put the sprite on the screen
    Rectangle dest{
        screenPosition.x,
        screenPosition.y,
        spriteScale * currentTexture.width / static_cast<float>(maxFrame),
        spriteScale * static_cast<float>(height)};

    // Draw the player
    DrawTexturePro(currentTexture, source, dest, Vector2{}, 0.f, WHITE);
}
