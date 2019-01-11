//
// Created by ali on 25/12/18.
//

#ifndef ALTER_TANK_STRUCTS_H
#define ALTER_TANK_STRUCTS_H

#include <stdbool.h>
#define BULLET_COUNT 5

typedef struct {
    double x, y, vx, vy;
    double instantiate_time;
    bool enabled;
} Bullet;

typedef struct {
    int red, green, blue, alpha;
} Color;

typedef struct {
    int x1, y1, x2, y2;
} Wall;

typedef struct {
    char source[256];
    Wall walls[100];
    int wall_count;
} Map;

typedef struct {
    double x, y;
    Color color;
    double angle;
    Bullet bullets[BULLET_COUNT];
    bool enable;
    int forward_key, backward_key, right_key, left_key, fire_key;
} Tank;

typedef struct{
    char Caption[120];
} UIButton;

typedef struct {
    Map map;
    int tank_count;
    Tank tanks[5];
} Manager;

#endif //ALTER_TANK_STRUCTS_H
