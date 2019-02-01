//
// Created by ali on 22/12/18.
//

#ifndef ALTER_TANK_BULLET_H
#define ALTER_TANK_BULLET_H
#define BULLET_SPEED 1.5
#define BULLET_RADIUS 2.5
#define BULLET_COLOR COLOR_BLACK
#define BULLET_LIFETIME 15
#define BULLET_FADE_TIME 0.6

#include "structs.h"
#include "stdbool.h"
#include "colors.h"
#include "tank.h"


void MoveBullet(Bullet *bullet);
void DrawTanksBullets(Tank tanks[], int count, SDL_Renderer *renderer);
void DrawSmallBullets(SDL_Renderer *renderer, Bullet bullets[][20]);

#endif //ALTER_TANK_BULLET_H
