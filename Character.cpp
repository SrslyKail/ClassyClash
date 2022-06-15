#include "raylib.h"
#include "raymath.h"
#include "Character.h"

Character::Character(int windowWidth, int windowHeight) :
    screenWidth(windowWidth),
    screenHeight(windowHeight)
{
    width = currentTexture.width / maxFrame;
    height = currentTexture.height;
}

Vector2 Character::getScreenPosition()
{
    return Vector2{
    (screenWidth / 2) - (spriteScale * width / 2.f),
    (screenHeight / 2) - (spriteScale * height / 2.f)};
}

void Character::tick(float deltaTime) // things we want to do every frame
{
    lastFrameWorldPosition = getWorldPosition();

    // check for directional inputs and apply force
    if (IsKeyDown(KEY_A) or IsKeyDown(KEY_LEFT))
        velocity.x -= 1;
    if (IsKeyDown(KEY_D) or IsKeyDown(KEY_RIGHT))
        velocity.x += 1;
    if (IsKeyDown(KEY_W) or IsKeyDown(KEY_UP))
        velocity.y -= 1;
    if (IsKeyDown(KEY_S) or IsKeyDown(KEY_DOWN))
        velocity.y += 1;

    BaseCharacter::tick(deltaTime);

}