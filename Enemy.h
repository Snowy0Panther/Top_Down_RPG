#ifndef ENEMY_H
#define ENEMY_H

#include"raylib.h"
#include"BaseCharacter.h"
#include"Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_Texture, Texture2D run_Texture);
    virtual void tick(float deltaTime) override;
    void setTarget(Character* character) { target = character; }
    virtual Vector2 getScreenPos() override;
protected:
    
private:
    Character* target;
    const float damagePerSec{10.0f};
    float radius{25.0f};
};

#endif