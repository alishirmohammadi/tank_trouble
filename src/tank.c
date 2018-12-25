#include "tank.h"
#include "bullet.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
//
// Created by ali on 16/12/18.
//


void TankRotateRight(Tank *tank) {
    tank->angle -= ROTATE_SPEED;
}

void TankRotateLeft(Tank *tank) {
    tank->angle += ROTATE_SPEED;
}

void TankForwardX(Tank *tank) {
    double angle = tank->angle;
    tank->x += FORWRD_SPEED * cos(angle);
}

void TankBackwardX(Tank *tank) {
    double angle = tank->angle;
    tank->x -= BACKWARD_SPEED * cos(angle);
}

void TankForwardY(Tank *tank) {
    double angle = tank->angle;
    tank->y += FORWRD_SPEED * sin(angle);
}

void TankBackwardY(Tank *tank) {
    double angle = tank->angle;
    tank->y -= BACKWARD_SPEED* sin(angle);
}

void DrawTank(Tank tank[], int count, SDL_Renderer *renderer) {
    for(int i = 0; i < count; i++) {
        filledCircleRGBA(renderer, tank[i].x, tank[i].y, TANK_RADIUS, tank[i].color.red, tank[i].color.green, tank[i].color.blue, tank[i].color.alpha);
        thickLineRGBA(renderer, tank[i].x, tank[i].y, tank[i].x + TANK_GUN_LENGTH * cos(tank[i].angle), tank[i].y + 24 * sin(tank[i].angle), 5, tank[i].color.red, tank[i].color.green, tank[i].color.blue, 255);
    }
}
