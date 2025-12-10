#include "food.h"
#include <stdlib.h>


void DrawFood(Food* food, const int foodCount){
    for(int i = 0; i < foodCount; i++){
        Food* f = &food[i];
        if(f->consumed) continue;
        DrawCircle((int)f->position.x, (int)f->position.y, 4.f, RED);
    }
}