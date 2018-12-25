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
    char linecount[100];
    fgets(linecount, 100, file);
    map->wall_count = (linecount[0] - '0') * 10 + linecount[1] - '0';
    for(int i = 0; i < map->wall_count; i++) {
        char wall[20];
        fgets(wall, 20, file);
        map->walls[i].x1 = wall[0] - '0';
        map->walls[i].y1 = wall[2] - '0';
        map->walls[i].x2 = wall[4] - '0';
        map->walls[i].y2 = wall[6] - '0';
    }
}

int pointMapToPixel(int x) {
    return MAP_SCALE * x + MAP_MARGIN;
}

void DrawMap(Map *map, SDL_Renderer *renderer) {
    for(int i = 0; i < map->wall_count; i++)
        thickLineRGBA(
                renderer,
                pointMapToPixel(map->walls[i].x1),
                pointMapToPixel(map->walls[i].y1),
                pointMapToPixel(map->walls[i].x2),
                pointMapToPixel(map->walls[i].y2),
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