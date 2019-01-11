#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "tank.h"
#include "map.h"
#include "keyboard_handler.h"
#include "colors.h"
#include "physics.h"
#include "bullet.h"

void MoveBullet(Bullet *bullet) {
    bullet->x += bullet->vx * BULLET_SPEED;
    bullet->y += bullet->vy * BULLET_SPEED;
}

void DrawTanksBullets(Tank tanks[], int count, SDL_Renderer *renderer) {
    for(int i = 0; i < count; i++)
        for(int j = 0; j < BULLET_COUNT; j++)
            if(tanks[i].bullets[j].state != Disable)
                filledCircleRGBA(
                        renderer,
                        tanks[i].bullets[j].x,
                        tanks[i].bullets[j].y,
                        BULLET_RADIUS,
                        BULLET_COLOR.red,
                        BULLET_COLOR.green,
                        BULLET_COLOR.blue,
                        BULLET_COLOR.alpha * (tanks[i].bullets[j].state == Enable ? 1.0 :
                                              (BULLET_FADE_TIME * 1000 - (SDL_GetTicks() - tanks[i].bullets[j].instantiate_time - BULLET_LIFETIME * 1000)) / (BULLET_FADE_TIME * 1000))
                        );
}