#include "tank.h"
#include "bullet.h"
#include "map.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <time.h>
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
        if(!tank[i].enable)
            continue;
        filledCircleRGBA(
                renderer,
                tank[i].x,
                tank[i].y,
                TANK_RADIUS,
                tank[i].color.red,
                tank[i].color.green,
                tank[i].color.blue,
                tank[i].color.alpha);
        filledCircleRGBA(
                renderer,
                tank[i].x,
                tank[i].y,
                TANK_RADIUS/2,
                0,
                0,
                0,
                tank[i].color.alpha);
        thickLineRGBA(
                renderer,
                tank[i].x + (TANK_RADIUS - 1) * cos(tank[i].angle),
                tank[i].y + (TANK_RADIUS - 1) * sin(tank[i].angle),
                tank[i].x + TANK_GUN_LENGTH * cos(tank[i].angle),
                tank[i].y + TANK_GUN_LENGTH * sin(tank[i].angle),
                4, 0, 0, 0, 255);
    }
}

void TankRandomPosition(Tank *tank, int maxX, int maxY) {
    srand(time(NULL));

    tank->x = PointMapToPixel(rand() % (maxX - 1) + 0.5);
    tank->y = PointMapToPixel(rand() % (maxY - 1) + 0.5);
}

void DestroyTank(Tank *tank) {
    tank->enable = false;
}