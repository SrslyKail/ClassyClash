#include "raylib.h"
#include "raymath.h"
#include "Prop.h"

Prop::Prop(Texture2D tex, Vector2 pos, float scale) : texture(tex),
                                         worldPosition(pos), scale(scale)
{
}

void Prop::Render(Vector2 playerPosition)
{
    Vector2 screenPosition{ Vector2Subtract(worldPosition, playerPosition)};
    DrawTextureEx(texture, screenPosition, 0, scale, WHITE);
}
