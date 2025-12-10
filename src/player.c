#include "player.h"
#include <stdio.h> // Do NULL
#include <math.h>

void InitPlayer(Player* player){
    player->position = (Vector2){ 0.f, 0.f };
    player->controllerIndex = -1;
    player->speed = 3.f;
    player->camera.target = player->position;
    player->camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    player->camera.rotation = 0.0f;
    player->camera.zoom = 1.0f;
    player->controller = NULL;
}

void ControlHuman(Player* player, Human* humans, const int humanCount){
    if(humanCount > 0){
        if(IsKeyPressed(KEY_UP)){ 
            if(player->controllerIndex < humanCount - 1){
                if(player->controllerIndex >= 0) humans[player->controllerIndex].controlled = false;
                player->controllerIndex++;
                humans[player->controllerIndex].controlled = true;
            }
        }else if(IsKeyPressed(KEY_DOWN)){
            if(player->controllerIndex > -1){
                humans[player->controllerIndex].controlled = false;
                player->controllerIndex--;
                if(player->controllerIndex > -1) humans[player->controllerIndex].controlled = true;
            }
        }

        if(player->controllerIndex > -1){
            player->controller = &humans[player->controllerIndex];
            player->position = player->controller->position;
            
        }else{
            player->controller = NULL;
        }
    }
}

void UpdatePlayer(Player* p){
    Vector2 vel = { 0, 0 };

    if (IsKeyDown(KEY_D)) vel.x += 1;
    if (IsKeyDown(KEY_A)) vel.x -= 1;
    if (IsKeyDown(KEY_S)) vel.y += 1;
    if (IsKeyDown(KEY_W)) vel.y -= 1;

    if (vel.x != 0 || vel.y != 0) {
        float length = sqrtf(vel.x * vel.x + vel.y * vel.y);
        vel.x /= length;
        vel.y /= length;

        p->position.x += vel.x * p->speed;
        p->position.y += vel.y * p->speed;
    }
    
    DrawText(TextFormat("x: %f, y: %f", p->position.x, p->position.y), 10, 10, 20, RED);
    
    if(p->controller != NULL){
        DrawText(TextFormat("Controlling human %d", p->controllerIndex), 10, 40, 20, RED);
        p->controller->position = p->position;
    }

    p->camera.zoom += GetMouseWheelMove() * 0.1f;

    if (p->camera.zoom > 3.0f) p->camera.zoom = 3.0f;
    if (p->camera.zoom < 0.1f) p->camera.zoom = 0.1f;

    if (IsKeyPressed(KEY_R)) {
        p->camera.zoom = 1.0f;
        p->camera.rotation = 0.0f;
    }

    p->camera.target = p->position;
}