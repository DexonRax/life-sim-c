#include "player.h"
#include <stdio.h> // Do NULL

void InitPlayer(Player* player){
    player->position = (Vector2){ 0.f, 0.f };
    player->controllerIndex = -1;
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

void UpdatePlayer(Player* player){
    if (IsKeyDown(KEY_D)) player->position.x += 2;
    if (IsKeyDown(KEY_A)) player->position.x -= 2;
    if (IsKeyDown(KEY_S)) player->position.y += 2;
    if (IsKeyDown(KEY_W)) player->position.y -= 2;
    
    DrawText(TextFormat("x: %f, y: %f", player->position.x, player->position.y), 10, 10, 20, RED);
    
    if(player->controller != NULL){
        DrawText(TextFormat("Controlling human %d", player->controllerIndex), 10, 40, 20, RED);
        player->controller->position = player->position;
    }

    player->camera.zoom += GetMouseWheelMove() * 0.1f;

    if (player->camera.zoom > 3.0f) player->camera.zoom = 3.0f;
    if (player->camera.zoom < 0.1f) player->camera.zoom = 0.1f;

    if (IsKeyPressed(KEY_R)) {
        player->camera.zoom = 1.0f;
        player->camera.rotation = 0.0f;
    }

    player->camera.target = player->position;
}