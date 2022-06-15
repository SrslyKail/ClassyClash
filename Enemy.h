#pragma once
#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Texture2D idle_texture, Texture2D run_texture, Vector2 position);
    virtual void tick(float deltaTime) override;
    void setTarget(Character* character){ target = character;}
    virtual Vector2 getScreenPosition() override;
private:
   Character* target;
};