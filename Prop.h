#include "raylib.h"

class Prop
{
public:
    Prop(Texture2D tex, Vector2 pos);
    void Render(Vector2 playerPosition);

private:
    Vector2 screenPosition{};
    Texture2D texture{};
    Vector2 worldPosition{};
    float scale{};
}