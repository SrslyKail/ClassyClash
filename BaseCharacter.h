#pragma once
#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPosition() { return worldPosition; }
    void undoMovement() { worldPosition = lastFrameWorldPosition; }
    Vector2 lastFrameWorldPosition{};
    Rectangle getCollionRectangle();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPosition() = 0;
protected:
    // textures
    Texture2D currentTexture{LoadTexture("Textures/characters/knight_idle_spritesheet.png")};
    Texture2D idleTexture{LoadTexture("Textures/characters/knight_idle_spritesheet.png")};
    Texture2D runTexture{LoadTexture("Textures/characters/knight_run_spritesheet.png")};
    float width{};
    float height{};
    // positions
    Vector2 worldPosition{};

    // animation variables
    int frame{};
    int maxFrame{6};
    float updateTime{1.0 / 12.0};
    float runningTime{};
    float rightLeft{1.f}; // 1= right, -1 = left. Used for flipping sprite
    float spriteScale{4};
    Vector2 velocity{};

    // gameplay variables
    float speed{5};

private:
};