#pragma once
#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int windowWidth, int windowHeight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPosition() override;
    Rectangle getWeaponCollision() { return weaponCollision; }
    float getHealth() { return health; }
    void takeDamage(float damage);

private:
    int screenWidth{};
    int screenHeight{};
    Texture2D weapon{LoadTexture("Textures/characters/weapon_sword.png")};
    Rectangle weaponCollision{};
    float health{100.f};
};