#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "tank.h"
#include "bullet.h"
#include "map.h"
#include "keyboard_handler.h"
#include "colors.h"
#include "physics.h"
#include "structs.h"


int min(int a, int b) {
    return a > b ? b : a;
}

int max(int a, int b) {
    return a > b ? a : b;
}

double magnitude(double x, double y) {
    return sqrt(x * x + y * y);
}

bool collision(Tank *tank, double newX, double newY, int x1, int y1, int x2, int y2) {
    if(x1 == x2) {
        if((newY >= y1 - TANK_RADIUS && newY <= y2 + TANK_RADIUS) && ((tank->x >= x1 + TANK_RADIUS && newX <= x1 + TANK_RADIUS) || (tank->x <= x1 - TANK_RADIUS && newX >= x1 - TANK_RADIUS)))
            return true;
    } else if(y1 == y2) {
        if((newX >= x1 - TANK_RADIUS && newX <= x2 + TANK_RADIUS) && ((tank->y >= y1 + TANK_RADIUS && newY <= y1 + TANK_RADIUS) || (tank->y <= y1 - TANK_RADIUS && newY >= y1 - TANK_RADIUS)))
            return true;
    }
    return false;
}

void PhysicsRenderer(Tank *tanks, int count, Map *map) {
    for(int i = 0; i < count; i++) {
        if(getKeyState(tanks[i].right_key))
            TankRotateLeft(&tanks[i]);
        if(getKeyState(tanks[i].left_key))
            TankRotateRight(&tanks[i]);
        if(getKeyState(tanks[i].forward_key)) {
            double newX = tanks[i].x + cos(tanks[i].angle) * FORWRD_SPEED;
            double newY = tanks[i].y + cos(tanks[i].angle) * FORWRD_SPEED;
            double x = tanks[i].x;
            double y = tanks[i].y;
            bool CanChangeX = true;
            bool CanChangeY = true;
            int a = 0, b = 0;
            for(int j = 0; j < map->wall_count; j++) {
                double x1 = PointMapToPixel(min(map->walls[j].x1, map->walls[j].x2));
                double x2 = PointMapToPixel(max(map->walls[j].x1, map->walls[j].x2));
                double y1 = PointMapToPixel(min(map->walls[j].y1, map->walls[j].y2));
                double y2 = PointMapToPixel(max(map->walls[j].y1, map->walls[j].y2));
                if (magnitude(newX - x1, newY - y1) <= TANK_RADIUS && magnitude(newX - x1, newY - y1) <= magnitude(x - x1, y - y1)) {
                    CanChangeX = false;
                    CanChangeY = false;
                } else if (magnitude(newX - x2, newY - y2) <= TANK_RADIUS && magnitude(newX - x2, newY - y2) <= magnitude(x - x1, y - y1)) {
                    CanChangeX = false;
                    CanChangeY = false;
                }
                if (x1 == x2) {
                    a++;
                    if(collision(&tanks[i], newX, newY, x1, y1, x2, y2)) {
                        CanChangeX = false;
                    }
                } else if(y1 == y2) {
                    b++;
                    if(collision(&tanks[i], newX, newY, x1, y1, x2, y2)) {
                        CanChangeY = false;
                    }
                }
            }
            //printf("%d   %d", a, b);
            if(CanChangeX)
                TankForwardX(&tanks[i]);
            if(CanChangeY)
                TankForwardY(&tanks[i]);
        }
        if(getKeyState(tanks[i].fire_key)) {
            int j = 0;
            for(; j < BULLET_COUNT && tanks[i].bullets[j].enabled; j++);
            if(j != BULLET_COUNT) {
                tanks[i].bullets[j].enabled = true;
                tanks[i].bullets[j].x = tanks[i].x;
                tanks[i].bullets[j].y = tanks[i].y;
                tanks[i].bullets[j].vx = cos(tanks[i].angle);
                tanks[i].bullets[j].vy = sin(tanks[i].angle);
                tanks[i].bullets[j].instantiate_time = SDL_GetTicks();
                disableKey(tanks[i].fire_key);
            }
        }
        for(int j = 0; j < BULLET_COUNT; j++) {
            if(tanks[i].bullets[j].enabled) {
                double x = tanks[i].bullets[j].x;
                double y = tanks[i].bullets[j].y;
                double newX = x + tanks[i].bullets[j].vx * BULLET_SPEED;
                double newY = y + tanks[i].bullets[j].vy * BULLET_SPEED;
                for(int k = 0; k < map->wall_count; k++) {
                    int x1, x2, y1, y2;
                    x1 = PointMapToPixel(min(map->walls[k].x1, map->walls[k].x2));
                    x2 = PointMapToPixel(max(map->walls[k].x1, map->walls[k].x2));
                    y1 = PointMapToPixel(min(map->walls[k].y1, map->walls[k].y2));
                    y2 = PointMapToPixel(max(map->walls[k].y1, map->walls[k].y2));
                    if(x1 == x2) {
                        if(y >= y1 && y <= y2) {
                            if((newX <= x1 && x >= x2) || (newX >= x1 && x <= x1))
                                tanks[i].bullets[j].vx *= -1;
                        }
                    } else if(y1 == y2) {
                        if(x >= x1 && x <= x2) {
                            if((newY <= y1 && y >= y1) || (newY >= y1 && y <= y1))
                                tanks[i].bullets[j].vy *= -1;
                        }
                    }
                }
                MoveBullet(&tanks[i].bullets[j]);
                if(SDL_GetTicks() - tanks[i].bullets[j].instantiate_time > BULLET_LIFETIME * 1000)
                    tanks[i].bullets[j].enabled = false;
            }
        }
    }


}