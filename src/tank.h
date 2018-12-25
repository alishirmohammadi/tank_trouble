#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "keyboard_handler.h"
#include "colors.h"
#include "bullet.h"
#define TANK_RADIUS 15
#define TANK_GUN_LENGTH 23
#define ROTATE_SPEED 0.07
#define FORWRD_SPEED 2
#define BACKWARD_SPEED 1
//
// Created by ali on 16/12/18.
//

#ifndef ALTER_TANK_TANK_H
#define ALTER_TANK_TANK_H

#endif //ALTER_TANK_TANK_H


void TankRotateRight(Tank *tank);
void TankRotateLeft(Tank *tank);
void TankForwardX(Tank *tank);
void TankBackwardX(Tank *tank);
void TankForwardY(Tank *tank);
void TankBackwardY(Tank *tank);
void DrawTank(Tank tank[], int count, SDL_Renderer *renderer);
