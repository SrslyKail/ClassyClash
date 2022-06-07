#include "raylib.h"
#include "BaseCharacter.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Texture2D idle_texture, Texture2D run_texture, Vector2 position);
    Vector2 getWorldPosition() { return worldPosition; }
    void tick(float deltaTime);
    void undoMovement() { worldPosition = lastFrameWorldPosition; }
    Vector2 lastFrameWorldPosition{};
    Rectangle getCollionRectangle();

private:
    // textures
    Texture2D currentTexture{LoadTexture("Textures/characters/knight_idle_spritesheet.png")};
    Texture2D idleTexture{LoadTexture("Textures/characters/knight_idle_spritesheet.png")};
    Texture2D runTexture{LoadTexture("Textures/characters/knight_run_spritesheet.png")};
    float width{};
    float height{};
    // positions
    Vector2 screenPosition{};
    Vector2 worldPosition{};
    // animation variables
    int frame{};
    int maxFrame{6};
    float updateTime{1.0 / 12.0};
    float runningTime{};
    float rightLeft{1.f}; // 1= right, -1 = left. Used for flipping sprite
    float spriteScale{4};

    // gameplay variables
    float speed{5};
};