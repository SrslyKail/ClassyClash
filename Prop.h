#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 playerPosition);
    Rectangle getCollionRectangle(Vector2 playerPosition);

private:
    Vector2 worldPosition{};
    Texture2D texture{};
    float propScale{4};
};