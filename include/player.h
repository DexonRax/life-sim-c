#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "humans.h"

typedef struct {
    Vector2 position;
    Camera2D camera;
    int controllerIndex;
    Human* controller;
} Player;

void InitPlayer(Player* player);
void ControlHuman(Player* player, Human* humans, int humanCount);
void UpdatePlayer(Player* player);

#endif
