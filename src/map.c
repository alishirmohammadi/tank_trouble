#include <bits/types/FILE.h>
#include <stdio.h>
#include <SDL_render.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "map.h"


void LoadMap(Map *map, char *src) {
    FILE *file;
    file = fopen(src, "r");
    fscanf(file, "%d\n", &map->wall_count);
    for(int i = 0; i < map->wall_count; i++)
        fscanf(file, "%d %d %d %d\n", &map->walls[i].x1, &map->walls[i].y1, &map->walls[i].x2, &map->walls[i].y2);
}

int PointMapToPixel(int x) {
    return MAP_SCALE * x + MAP_MARGIN;
}

void DrawMap(Map *map, SDL_Renderer *renderer) {
    for(int i = 0; i < map->wall_count; i++)
        thickLineRGBA(
                renderer,
                PointMapToPixel(map->walls[i].x1),
                PointMapToPixel(map->walls[i].y1),
                PointMapToPixel(map->walls[i].x2),
                PointMapToPixel(map->walls[i].y2),
                WALL_WIDTH, 0, 0, 0, 255);
}

int maxMapX(Map *map) {
    int max = 0;
    for(int i = 0; i < map->wall_count; i++)
        if(max < map->walls[i].x1) max = map->walls[i].x1;
        else if(max < map->walls[i].x2) max = map->walls[i].x2;
    return max;
}

int maxMapY(Map *map) {
    int max = 0;
    for(int i = 0; i < map->wall_count; i++)
        if(max < map->walls[i].y1) max = map->walls[i].y1;
        else if(max < map->walls[i].y2) max = map->walls[i].y2;
    return max;
}