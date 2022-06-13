#pragma once
#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int screenWidth, int screenHeight);
    virtual void tick(float deltaTime) override;

private:
};