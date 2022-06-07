#include "raylib.h"
#include "BaseCharacter.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Texture2D idle_texture, Texture2D run_texture, Vector2 position);
    void tick(float deltaTime);

private:
};