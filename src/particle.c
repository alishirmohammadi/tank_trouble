//
// Created by ali on 12/01/19.
//

#include <stdlib.h>
#include <time.h>
#include <SDL_timer.h>
#include <SDL_render.h>
#include <SDL2_gfxPrimitives.h>
#include "particle.h"
#include "structs.h"
#include "colors.h"

float mx(float a, float b) {
    return a > b ? a : b;
}

void RandomSmoke(Smoke *smoke, int x, int y) {
    srand(time(NULL));
    smoke->enable = true;
    smoke->particle_count = PARTICLE_COUNT;
    smoke->x = x;
    smoke->y = y;
    smoke->instantiate_time = SDL_GetTicks();
    for(int i = 0; i < smoke->particle_count; i++) {
        smoke->particles[i].x = x + (rand() % SMOKE_DELTA_POSITION) - SMOKE_DELTA_POSITION / 2;
        smoke->particles[i].y = y + (rand() % SMOKE_DELTA_POSITION) - SMOKE_DELTA_POSITION / 2;
        smoke->particles[i].color = new_Color(0, 0, 0, rand() % MAX_COLOR_ALPHA);
        smoke->particles[i].dx = (rand() % MAX_PARTICLE_SPEED - MAX_PARTICLE_SPEED / 2) / 80.0;
        smoke->particles[i].dy = (rand() % MAX_PARTICLE_SPEED - MAX_PARTICLE_SPEED / 2) / 80.0;
        smoke->particles[i].life_time = rand() % (MAX_PARTICLE_LIFETIME - MIN_PARTICLE_LIFETIME) + MIN_PARTICLE_LIFETIME;
        smoke->particles[i].radius = rand() % (MAX_PARTICLE_RADIUS - MIN_PARTICLE_RADIUS) + MIN_PARTICLE_RADIUS;
        smoke->particles[i].radius_speed = (rand() % MAX_PARTICLE_RADIUS_SPEED) / 100.0;
    }
}

void SmallSmoke(Smoke *smoke, int x, int y) {
    srand(time(NULL));
    smoke->enable = true;
    smoke->particle_count = PARTICLE_COUNT;
    smoke->x = x;
    smoke->y = y;
    smoke->instantiate_time = SDL_GetTicks();
    for(int i = 0; i < smoke->particle_count; i++) {
        smoke->particles[i].x = x + (rand() % SMOKE_DELTA_POSITION) - SMOKE_DELTA_POSITION / 2;
        smoke->particles[i].y = y + (rand() % SMOKE_DELTA_POSITION) - SMOKE_DELTA_POSITION / 2;
        smoke->particles[i].color = new_Color(50, 50, 50, rand() % 20);
        smoke->particles[i].dx = (rand() % MAX_PARTICLE_SPEED - MAX_PARTICLE_SPEED / 2) / 80.0 / 2.0;
        smoke->particles[i].dy = (rand() % MAX_PARTICLE_SPEED - MAX_PARTICLE_SPEED / 2) / 80.0 / 2.0;
        smoke->particles[i].life_time = (rand() % (MAX_PARTICLE_LIFETIME - MIN_PARTICLE_LIFETIME) + MIN_PARTICLE_LIFETIME) / 1.5;
        smoke->particles[i].radius = (rand() % (MAX_PARTICLE_RADIUS - MIN_PARTICLE_RADIUS) + MIN_PARTICLE_RADIUS);
        smoke->particles[i].radius_speed = (rand() % MAX_PARTICLE_RADIUS_SPEED) / 100.0 / 2.0;
    }
}

void DrawSmoke(SDL_Renderer *renderer, Smoke smoke[], int count) {
    for(int i = 0; i < count; i++) {
        if(!smoke[i].enable)
            continue;
        for(int j = 0; j < smoke[i].particle_count; j++) {
            filledCircleRGBA(
                    renderer,
                    smoke[i].particles[j].x,
                    smoke[i].particles[j].y,
                    smoke[i].particles[j].radius,
                    smoke[i].particles[j].color.red,
                    smoke[i].particles[j].color.green,
                    smoke[i].particles[j].color.blue,
                    smoke[i].particles[j].color.alpha * mx((1 - (SDL_GetTicks() - smoke[i].instantiate_time) / smoke[i].particles[j].life_time), 0.0)
            );
        }
    }
}