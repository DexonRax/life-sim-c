#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "humans.h"
#include "player.h"
#include "food.h"

int hash(Vector2 pos) {
    int cellX = pos.x / 16; // because 1024/64 = 16
    int cellY = pos.y / 16;

    if (cellX < 0) cellX = 0;
    if (cellY < 0) cellY = 0;
    if (cellX >= 64) cellX = 63;
    if (cellY >= 64) cellY = 63;

    return cellY * 64 + cellX;
}

typedef struct {
    int count;
    int capacity;
    int* items;   // indices of humans
    int* foodItems;   // indices of food
    int foodCount;
    int foodCapacity;
} Cell;


int main(void){
    srand(time(NULL));
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int humanCount = 50;

    Cell* grid;
    int gridWidth = 64;
    int gridHeight = 64;

    grid = malloc(gridWidth * gridHeight * sizeof(Cell));

    for (int i = 0; i < gridWidth * gridHeight; i++) {
        grid[i].count = 0;
        grid[i].capacity = 16;
        grid[i].items = malloc(sizeof(int) * grid[i].capacity);
        grid[i].foodCount = 0;
        grid[i].foodCapacity = 16;
        grid[i].foodItems = malloc(sizeof(int) * grid[i].foodCapacity);
    }
    
    const Vector2 mapSize = {1024.f, 1024.f};
    const Vector2 mapAreasPerAxis = {64.f, 64.f};


    int cellCount = (int)(mapAreasPerAxis.x * mapAreasPerAxis.y);
    int* hashmap = malloc(sizeof(int) * cellCount);

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
        humans[i].position.x = (float)(rand()%(int)mapSize.x);
        humans[i].position.y = (float)(rand()%(int)mapSize.y);
        humans[i].direction = (float)(rand()%360+1);
        humans[i].controlled = false;
    }

    Food* foods = (Food*)malloc(100*sizeof(Food));
    for(int i = 0; i < 100; i++){
        foods[i].position.x = (float)(rand()%(int)mapSize.x);
        foods[i].position.y = (float)(rand()%(int)mapSize.y);
        foods[i].nutriency = (float)(rand()%100+1);
        foods[i].consumed = false;
    }
    
    while (!WindowShouldClose())
    {
        ControlHuman(&player, humans, humanCount);
        UpdatePlayer(&player);

        for (int i = 0; i < 64*64; i++){
            grid[i].count = 0;
            grid[i].foodCount = 0;
        }

        for (int i = 0; i < humanCount; i++) {
            int h = hash(humans[i].position);
            Cell* c = &grid[h];
            if (c->count >= c->capacity) {
                c->capacity *= 2;
                c->items = realloc(c->items, sizeof(int) * c->capacity);
            }
            c->items[c->count++] = i;
        }

        for (int i = 0; i < 100; i++) {
            int h = hash(foods[i].position);
            Cell* c = &grid[h];
            if (c->foodCount >= c->foodCapacity) {
                c->foodCapacity *= 2;
                c->foodItems = realloc(c->foodItems, sizeof(int) * c->foodCapacity);
            }
            c->foodItems[c->foodCount++] = i;
        }

        for(int i = 0; i < cellCount; i++) {
            if(grid[i].count > 0 && grid[i].foodCount > 0) {
                for(int f = 0; f < grid[i].foodCount; f++) {
                    int foodIndex = grid[i].foodItems[f];
                    foods[foodIndex].consumed = true;
                }
                grid[i].foodCount = 0;
            }
        }

        int index = hash(player.position);
        DrawText(TextFormat("Current cell: %d\n", index), 10, 60, 20, GREEN);
        int count = grid[index].count;
        for(int i = 0; i < count; i++)
            DrawText(TextFormat("Cell human: %d\n", grid[index].items[i]), 10, 80+20*i, 20, BLUE);
        int countFood = grid[index].foodCount;
        for(int i = 0; i < countFood; i++)
            DrawText(TextFormat("Cell food: %d\n", grid[index].foodItems[i]), 200, 80+20*i, 20, BLUE);

        BeginDrawing();
        
            ClearBackground(RAYWHITE);

            BeginMode2D(player.camera);
            
                UpdateHumans(humans, humanCount, true);
                DrawFood(foods, 100);
            
            EndMode2D();
        
        EndDrawing();
    }

    for(int i = 0; i < cellCount; i++) {
        if(grid[i].items != NULL) {
            free(grid[i].items);
        }
        if(grid[i].foodItems != NULL) {
            free(grid[i].foodItems);
        }
    }
    free(grid);
    free(foods);
    free(humans);
    CloseWindow();
    return 0;
}