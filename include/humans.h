#ifndef HUMANS_H
#define HUMANS_H

#include <raylib.h>
#include <stdbool.h>

typedef struct {
    Vector2 position;
    float direction;
    bool controlled;
} Human;

void UpdateHumans(Human* humans, const int humanCount, bool boundaryCheck);

#endif