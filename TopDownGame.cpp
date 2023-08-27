#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int windowDirections[2]{384, 384};
    const char *titleOfWindow{"Top Down Game"};
    InitWindow(windowDirections[0], windowDirections[1], titleOfWindow);
    Texture2D map{LoadTexture("nature_tileset/OpenWorldMap24x24.png")};
    Vector2 mapPos{0.0f, 0.0f};
    const float mapScale{4.0f};

    Character knight{windowDirections[0], windowDirections[1],
                     LoadTexture("characters/knight_idle_spritesheet.png"),
                     LoadTexture("characters/knight_run_spritesheet.png")};
    Prop props[2] = {
        Prop{Vector2{600.0f, 300.0f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.0f, 500.0f}, LoadTexture("nature_tileset/Log.png")}};
    Enemy goblin{Vector2{800.0f, 300.0f},
                 LoadTexture("characters/goblin_idle_spritesheet.png"),
                 LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy slime{Vector2{500.0f, 700.0f},
                LoadTexture("characters/slime_idle_spritesheet.png"),
                LoadTexture("characters/slime_run_spritesheet.png")};
    Enemy *enemies[]{
        &goblin,
        &slime};
    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);
        // draw map
        DrawTextureEx(map, mapPos, 0.0f, 4.0f, WHITE);

        // draw the props
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(GetFrameTime());
        // check map bounds
        if (knight.getWorldPos().x < 0.0f ||
            knight.getWorldPos().y < 0.0f ||
            knight.getWorldPos().x + windowDirections[0] > map.width * mapScale ||
            knight.getWorldPos().y + windowDirections[1] > map.height * mapScale)
        {
            knight.undoMovement();
        }

        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        if (!knight.getAlive()) // Character is not alive
        {
            DrawText("Game Over", 55.0f, 45.0f, 40, RED);
            EndDrawing();
            continue;
        }
        else // Character is alive
        {
            std::string knightHealth = "Health: ";
            knightHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.0f, 45.0f, 40.0f, RED);
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if (IsKeyDown(KEY_SPACE))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}