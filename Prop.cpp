#include "raylib.h"
#include "raymath.h"
#include "Prop.h"

Prop::Prop(Vector2 pos, Texture2D tex) : worldPosition(pos), 
                                         texture(tex)
                                                      
{
}

void Prop::Render(Vector2 playerPosition)
{
    Vector2 screenPosition{Vector2Subtract(worldPosition, playerPosition)};
    DrawTextureEx(texture, screenPosition, 0, propScale, WHITE);
}

Rectangle Prop::getCollionRectangle(Vector2 playerPosition)
{
    Vector2 screenPosition{Vector2Subtract(worldPosition, playerPosition)};
    return Rectangle{
        screenPosition.x,
        screenPosition.y,
        texture.width * propScale,
        texture.height * propScale};
}
