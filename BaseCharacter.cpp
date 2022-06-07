#include "BaseCharacter.h"
#include "raylib.h"

BaseCharacter::BaseCharacter()
{
    width = currentTexture.width / maxFrame;
    height = currentTexture.height;
}
Rectangle BaseCharacter::getCollionRectangle()
{
    return Rectangle{
        screenPosition.x,
        screenPosition.y,
        width * spriteScale,
        height * spriteScale};
}

void BaseCharacter::tick(float deltaTime)
{
    lastFrameWorldPosition = getWorldPosition();

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

    // Draw the sprite
    DrawTexturePro(currentTexture, source, dest, Vector2{}, 0.f, WHITE);
}