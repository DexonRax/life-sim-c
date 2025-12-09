#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "humans.h"
#include "player.h"

int main(void){
    srand(time(NULL));
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int humanCount = 1000;
    
    printf("DEBUG: Humans: %lu bytes\n", sizeof(Human) * humanCount);
    printf("DEBUG: Player: %lu bytes\n", sizeof(Player));
    
    InitWindow(screenWidth, screenHeight, "raylib - modular");
    SetTargetFPS(60);  
    
    Player player = { 0 };
    InitPlayer(&player);
    
    Human* humans = (Human*)malloc(humanCount * sizeof(Human));
    if (humans == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for(int i = 0; i < humanCount; i++){
        humans[i].position.x = (float)(i*40.f)+50.f;
        humans[i].position.y = (float)(i*32.f)+50.f;
        humans[i].direction = (float)(rand()%360+1);
        humans[i].controlled = false;
    }
    
    while (!WindowShouldClose())
    {
        ControlHuman(&player, humans, humanCount);
        UpdatePlayer(&player);
        
        BeginDrawing();
        
            ClearBackground(RAYWHITE);

            BeginMode2D(player.camera);
            
                UpdateHumans(humans, humanCount, false);
            
            EndMode2D();
        
        EndDrawing();
    }

    free(humans); // Pamiętaj o zwalnianiu pamięci
    CloseWindow();
    return 0;
}