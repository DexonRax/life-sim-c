#ifndef FOOD_H
#define FOOD_H

#include <raylib.h>

typedef struct {
    Vector2 position;
    float nutriency;
    bool consumed;
} Food;

void DrawFood(Food* food, int foodCound);

#endif