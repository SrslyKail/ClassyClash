#include "BaseCharacter.h"
#include "raylib.h"

BaseCharacter::BaseCharacter(Texture2D idle_texture, Texture2D run_texture, Vector2 position) :
    currentTexture(idle_texture),
    idleTexture(idle_texture),
    runTexture(run_texture),
    worldPosition(position)
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