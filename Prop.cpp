#include "raylib.h"
#include "raymath.h"
#include "Prop.h"

Prop::Prop(Texture2D tex, Vector2 pos) : texture(tex),
                                         worldPosition(pos)
{
}
