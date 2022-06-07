#include "raylib.h"
#include "Enemy.h"

Enemy::Enemy(Texture2D idle_texture, Texture2D run_texture, Vector2 position)
{
    currentTexture = idle_texture;
    idleTexture = idle_texture;
    runTexture = run_texture;
    worldPosition = position;
    width = currentTexture.width / maxFrame;
    height = currentTexture.height;
}

void Enemy::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);
}