//
// Created by ali on 12/01/19.
//

#ifndef ALTER_TANK_PARTICLE_H
#define ALTER_TANK_PARTICLE_H

#include "structs.h"

#define TANK_SMOKE_INIT_INTERVAL 0.3
#define PARTICLE_COUNT 30
#define SMOKE_DELTA_POSITION 10
#define MAX_COLOR_ALPHA 64
#define MAX_PARTICLE_SPEED 30
#define MAX_PARTICLE_LIFETIME 4000
#define MIN_PARTICLE_LIFETIME 2000
#define MAX_PARTICLE_RADIUS 16
#define MIN_PARTICLE_RADIUS 5
#define MAX_PARTICLE_RADIUS_SPEED 8

void RandomSmoke(Smoke *smoke, int x, int y);
void SmallSmoke(Smoke *smoke, int x, int y);
void DrawSmoke(SDL_Renderer *renderer, Smoke smoke[], int count);

#endif //ALTER_TANK_PARTICLE_H
