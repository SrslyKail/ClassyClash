#include "raylib.h"
#include "raymath.h"
#include "Character.h"

Character::Character(int windowWidth, int windowHeight) : screenWidth(windowWidth),
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
    if (!getAlive())
        return;

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

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightLeft > 0.f)
    {
        origin = {0.f, weapon.height * spriteScale};
        offset = {35.f, 55.f};
        weaponCollision = {
            getScreenPosition().x + offset.x,
            getScreenPosition().y + offset.y - (weapon.height * spriteScale),
            weapon.width * spriteScale,
            weapon.height * spriteScale};
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.f : rotation = 0.f;
    }
    else
    {
        origin = {static_cast<float>(weapon.width) * spriteScale, weapon.height * spriteScale};
        offset = {25.f, 55.f};
        weaponCollision = {
            getScreenPosition().x + offset.x - (weapon.width * spriteScale),
            getScreenPosition().y + offset.y - (weapon.height * spriteScale),
            weapon.width * spriteScale,
            weapon.height * spriteScale};
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.f : rotation = 0.f;
    }

    // Draw the sword
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle destination{getScreenPosition().x + offset.x, getScreenPosition().y + offset.y, weapon.width * spriteScale, weapon.height * spriteScale};
    DrawTexturePro(weapon, source, destination, origin, rotation, WHITE);

    DrawRectangleLines(
        weaponCollision.x,
        weaponCollision.y,
        weaponCollision.width,
        weaponCollision.height,
        RED);
}
void Character::takeDamage(float damage)
{
    health -= damage;

    if (health <= 0.f)
    {
        setAlive(false);
    }
}
