//
// Created by ali on 16/12/18.
//

#ifndef ALTER_TANK_MAP_H
#define ALTER_TANK_MAP_H
#define MAP_MARGIN 10
#define MAP_SCALE 60
#define WALL_WIDTH 5

#include "structs.h"

void LoadMap(Map *map, char *src);
void DrawMap(Map *map, SDL_Renderer *renderer);
int PointMapToPixel(int x);
int maxMapY(Map *map);
int maxMapX(Map *map);
void mapGenerator(Map *map);

#endif //ALTER_TANK_MAP_H
