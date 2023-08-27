#include"Character.h"
#include"raymath.h"

Character::Character(int winWidth, int winHeight, Texture2D idle_texture, Texture2D run_texture):
    windowWidth(winWidth),
    windowHeight(winHeight) 
{
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;

    width = texture.width / maxFrames;
    height = texture.height;   
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth)/2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight)/2.0f - scale * (0.5f * height)
    };
}

void Character::tick(float deltaTime)
{
    if (!getAlive()) return;
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0f;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0f;

    BaseCharacter::tick(deltaTime);   

    float rotation{};
    Vector2 origin{};
    Vector2 offset{};
    if (righLeft > 0.0f)
    {
        origin = {0.0f, weapon.height * scale};
        offset = {35.0f, 55.0f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsKeyDown(KEY_SPACE) ? 35.0f : 0.0f;
    }
    else
    {
        origin = {weapon.height * scale, weapon.width * scale};
        offset = {25.0f, 55.0f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsKeyDown(KEY_SPACE) ? -35.0f : 0.0f;
    }
    

    // draw sword
    Rectangle source{
        0.0f, 
        0.0f,
        static_cast<float>(weapon.width) * righLeft,
        static_cast<float>(weapon.height)
    };
    Rectangle dest{
        getScreenPos().x + offset.x,
        getScreenPos().y + offset.y,
        weapon.width * scale,
        weapon.height * scale
    };
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
    //DrawRectangleLines(
    //    weaponCollisionRec.x,
    //    weaponCollisionRec.y,
    //    weaponCollisionRec.width,
    //    weaponCollisionRec.height,
    //    RED
    //);
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.0f)
    {
        setAlive(false);
    }
    
}