#include"BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::tick(float deltaTime)
{
     worldPosLastFrame = worldPos;
    // update animation
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0;
        if (frame >= maxFrames)
        {
            frame = 0;
        }
        
    }

    if (Vector2Length(velocity) != 0.0f)
    {
        // set worldPos = worldPos + velocity
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.0f ? righLeft = -1.0f : righLeft = 1.0f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    Rectangle source = {
        frame * width,
        0.0f,
        righLeft * width,
        height
    };
    Rectangle dest = {
        getScreenPos().x, 
        getScreenPos().y,
        scale * width,
        scale * height
    };
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}