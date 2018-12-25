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
            if(tanks[i].bullets[j].enabled)
                filledCircleRGBA(
                        renderer,
                        tanks[i].bullets[j].x,
                        tanks[i].bullets[j].y,
                        BULLET_RADIUS,
                        BULLET_COLOR.red,
                        BULLET_COLOR.green,
                        BULLET_COLOR.blue,
                        BULLET_COLOR.alpha
                        );
}