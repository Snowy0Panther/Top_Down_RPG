#include"Enemy.h"
#include"raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_Texture, Texture2D run_Texture)
{
    worldPos = pos;
    texture = idle_Texture;
    idle = idle_Texture;
    run = run_Texture;
    speed = 3.5f;
    width = texture.width/maxFrames;
    height = texture.height;
}

void Enemy::tick(float deltaTime)
{
    if(!getAlive()) return;
    // get toTarget
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < radius) velocity = {};
    BaseCharacter::tick(deltaTime);
    if(CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}