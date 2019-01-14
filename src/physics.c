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
#include "particle.h"

int min(int a, int b) {
    return a > b ? b : a;
}

int max(int a, int b) {
    return a > b ? a : b;
}

double magnitude(double x, double y) {
    return sqrt(x * x + y * y);
}

bool collision(Tank *tank, double newX, double newY, double x1, double y1, double x2, double y2) {
    double x = tank->x, y = tank->y;
    if(x1 == x2) {
        if((newY >= y1 - TANK_RADIUS && newY <= y2 + TANK_RADIUS) && ((x >= x1 + TANK_RADIUS && newX <= x1 + TANK_RADIUS) || (x <= x1 - TANK_RADIUS && newX >= x1 - TANK_RADIUS)))
            return true;
    } else if(y1 == y2) {
        if((newX >= x1 - TANK_RADIUS && newX <= x2 + TANK_RADIUS) && ((y >= y1 + TANK_RADIUS && newY <= y1 + TANK_RADIUS) || (y <= y1 - TANK_RADIUS && newY >= y1 - TANK_RADIUS)))
            return true;
    }
    return false;
}

void SmokeRenderer(Smoke smoke[], int count) {
    for(int i = 0; i < count; i++) {
        if(!smoke[i].enable)
            continue;
        for(int j = 0; j < smoke[i].particle_count; j++) {
            smoke[i].particles[j].x += smoke[i].particles[j].dx;
            smoke[i].particles[j].y += smoke[i].particles[j].dy;
            smoke[i].particles[j].radius += smoke[i].particles[j].radius_speed;
        }
        if(SDL_GetTicks() - smoke[i].instantiate_time > MAX_PARTICLE_LIFETIME)
            smoke[i].enable = false;
    }
}

void PhysicsRenderer(Tank *tanks, int count, Map *map, Smoke smoke[], int smoke_count, Manager *manager) {
    for(int i = 0; i < count; i++) {
        if(getKeyState(tanks[i].right_key) && tanks[i].enable)
            TankRotateLeft(&tanks[i]);
        if(getKeyState(tanks[i].left_key) && tanks[i].enable)
            TankRotateRight(&tanks[i]);
        if(getKeyState(tanks[i].forward_key) && tanks[i].enable) {
            Tank temp = tanks[i];
            TankForwardX(&temp);
            TankForwardY(&temp);
            double newX = temp.x;
            double newY = temp.y;
            double x = tanks[i].x;
            double y = tanks[i].y;
            bool CanChangeX = true;
            bool CanChangeY = true;
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
                    if(collision(&tanks[i], newX, newY, x1, y1, x2, y2)) {
                        CanChangeX = false;
                    }
                } else if(y1 == y2) {
                    if(collision(&tanks[i], newX, newY, x1, y1, x2, y2)) {
                        CanChangeY = false;
                    }
                }
            }
            if(CanChangeX)
                TankForwardX(&tanks[i]);
            if(CanChangeY)
                TankForwardY(&tanks[i]);
        }
        if(getKeyState(tanks[i].backward_key) && tanks[i].enable) {
            Tank temp = tanks[i];
            TankBackwardX(&temp);
            TankBackwardY(&temp);
            double newX = temp.x;
            double newY = temp.y;
            double x = tanks[i].x;
            double y = tanks[i].y;
            bool CanChangeX = true;
            bool CanChangeY = true;
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
                    if(collision(&tanks[i], newX, newY, x1, y1, x2, y2)) {
                        CanChangeX = false;
                    }
                } else if(y1 == y2) {
                    if(collision(&tanks[i], newX, newY, x1, y1, x2, y2)) {
                        CanChangeY = false;
                    }
                }
            }
            if(CanChangeX)
                TankBackwardX(&tanks[i]);
            if(CanChangeY)
                TankBackwardY(&tanks[i]);
        }
        if(getKeyState(tanks[i].fire_key) && tanks[i].enable) {
            int j = 0;
            for(; j < BULLET_COUNT && tanks[i].bullets[j].state != Disable; j++);
            if(j != BULLET_COUNT) {
                tanks[i].bullets[j].state = Enable;
                tanks[i].bullets[j].x = tanks[i].x + cos(tanks[i].angle) * (TANK_RADIUS - 2);
                tanks[i].bullets[j].y = tanks[i].y + sin(tanks[i].angle) * (TANK_RADIUS - 2);
                tanks[i].bullets[j].vx = cos(tanks[i].angle);
                tanks[i].bullets[j].vy = sin(tanks[i].angle);
                tanks[i].bullets[j].instantiate_time = SDL_GetTicks();
                disableKey(tanks[i].fire_key);
            }
        }
        for(int j = 0; j < BULLET_COUNT; j++) {
            if(tanks[i].bullets[j].state != Disable) {
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
                        if(y >= y1 - WALL_WIDTH / 2 && y <= y2 + WALL_WIDTH / 2) {
                            if((newX <= x1 + WALL_WIDTH / 2 && x >= x2 + WALL_WIDTH / 2) || (newX >= x1 - WALL_WIDTH / 2 && x <= x1 - WALL_WIDTH / 2))
                                tanks[i].bullets[j].vx *= -1;
                        }
                    } else if(y1 == y2) {
                        if(x >= x1 - WALL_WIDTH / 2 && x <= x2 + WALL_WIDTH / 2) {
                            if((newY <= y1 + WALL_WIDTH / 2 && y >= y1 + WALL_WIDTH / 2) || (newY >= y1 - WALL_WIDTH / 2 && y <= y1 - WALL_WIDTH / 2))
                                tanks[i].bullets[j].vy *= -1;
                        }
                    }
                }
                MoveBullet(&tanks[i].bullets[j]);
                if(SDL_GetTicks() - tanks[i].bullets[j].instantiate_time > BULLET_LIFETIME * 1000)
                    tanks[i].bullets[j].state = FadeOut;
                if(SDL_GetTicks() - tanks[i].bullets[j].instantiate_time > (BULLET_LIFETIME + BULLET_FADE_TIME) * 1000)
                    tanks[i].bullets[j].state = Disable;
            }
            if(tanks[i].bullets[j].state == Enable) {
                for(int k = 0; k < count; k++) {
                    if(tanks[k].enable == false)
                        continue;
                    if(magnitude(tanks[k].x - tanks[i].bullets[j].x, tanks[k].y - tanks[i].bullets[j].y) < TANK_RADIUS - BULLET_RADIUS) {
                        tanks[i].bullets[j].state = Disable;
                        tanks[k].enable = false;
                        manager->last_destroy_time = SDL_GetTicks();
                        int disableSmokeId = 0;
                        while(disableSmokeId < smoke_count && smoke[disableSmokeId].enable == true)
                            disableSmokeId++;
                        RandomSmoke(&smoke[disableSmokeId], tanks[k].x, tanks[k].y);
                    }
                }
            }
        }
    }

}