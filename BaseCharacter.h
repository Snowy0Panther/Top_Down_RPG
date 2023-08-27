#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() {return worldPos;}
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() { return bIsAlive; }
    void setAlive(bool isAlive) { bIsAlive = isAlive; }
protected:
    Texture2D texture{};
    Texture2D idle{};
    Texture2D run{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1 : facing right -1 : facing left
    float righLeft{1.0f};
    // animation variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.0f/12.0f};
    float speed{4.0f};
    float width{};
    float height{};
    float scale{4.0f};
    Vector2 velocity{};

private:
    bool bIsAlive{true};
};

#endif