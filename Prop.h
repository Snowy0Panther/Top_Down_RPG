#include"raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 characterPos);
    Rectangle getCollisionRec(Vector2 characterPos);
protected:

private:
    Texture2D texture{LoadTexture("nature_tileset/Rock.png")};
    Vector2 worldPos{0.0f, 0.0f};
    float scale{4.0f};
};