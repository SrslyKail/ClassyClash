#include "BaseCharacter.h"
#include "raylib.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
    width = currentTexture.width / maxFrame;
    height = currentTexture.height;
}
Rectangle BaseCharacter::getCollisionRectangle()
{
    return Rectangle{
        getScreenPosition().x,
        getScreenPosition().y,
        width * spriteScale,
        height * spriteScale};
}

void BaseCharacter::tick(float deltaTime)
{
    lastFrameWorldPosition = getWorldPosition();
    if (Vector2Length(velocity) != 0.0)
    {
        worldPosition = Vector2Add(
            worldPosition, Vector2Scale(
                               Vector2Normalize(velocity), // normalized direction so diagonal movement isnt faster than cardinal
                               speed));                    // scale by character speed, to control rate of movement

        // if direction is less than zero, character must be moving right
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        currentTexture = runTexture;
    }
    else
    {
        currentTexture = idleTexture;
    }
    velocity = {};
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
        getScreenPosition().x,
        getScreenPosition().y,
        spriteScale * currentTexture.width / static_cast<float>(maxFrame),
        spriteScale * static_cast<float>(height)};

    // Draw the sprite
    DrawTexturePro(currentTexture, source, dest, Vector2{}, 0.f, WHITE);

    // TODO: Remove This
    DrawRectangleLines(
        getCollisionRectangle().x,
        getCollisionRectangle().y,
        width * spriteScale,
        height * spriteScale,
        BLUE);
}