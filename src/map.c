#include <bits/types/FILE.h>
#include <stdio.h>
#include <SDL_render.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <time.h>
#include <stdlib.h>
#include "map.h"


void LoadMap(Map *map, char *src) {
    FILE *file;
    file = fopen(src, "r");
    fscanf(file, "%d\n", &map->wall_count);
    for(int i = 0; i < map->wall_count; i++)
        fscanf(file, "%d %d %d %d\n", &map->walls[i].x1, &map->walls[i].y1, &map->walls[i].x2, &map->walls[i].y2);
}

float PointMapToPixel(float x) {
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

Wall new_Wall(int x1, int y1, int x2, int y2) {
    Wall w;
    w.x1 = x1;
    w.y1 = y1;
    w.x2 = x2;
    w.y2 = y2;
    return w;
}

void PrintMap(bool map[][10]) {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++)
            printf("%s", map[i][j] ? "  ": " #");
        printf("\n");
    }
}

bool ValidMap(bool map[][10]) {
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            if(map[i][j] == true)
                return false;
    return true;
}

void mapRouteSearch(Wall walls[], int k, bool map[][10], int x, int y) {
    map[x][y] = false;

    if(x < 9 && map[x + 1][y]) {
        bool flag = true;
        for(int i = 0; i < k; i++)
            if( walls[i].x1 == walls[i].x2 &&
                walls[i].x1 == x + 1 &&
                walls[i].y1 <= y &&
                walls[i].y2 > y)
                flag = false;
        if(flag)
            mapRouteSearch(walls, k, map, x + 1, y);
    }

    if(y < 9 && map[x][y + 1]) {
        bool flag = true;
        for(int i = 0; i < k; i++)
            if( walls[i].y1 == walls[i].y2 &&
                walls[i].y1 == y + 1 &&
                walls[i].x1 <= x &&
                walls[i].x2 > x)
                flag = false;
        if(flag)
            mapRouteSearch(walls, k, map, x, y + 1);
    }

    if(x > 0 && map[x - 1][y]) {
        bool flag = true;
        for(int i = 0; i < k; i++)
            if( walls[i].x1 == walls[i].x2 &&
                walls[i].x1 == x &&
                walls[i].y1 <= y &&
                walls[i].y2 > y)
                flag = false;
        if(flag)
            mapRouteSearch(walls, k, map, x - 1, y);
    }

    if(y > 0 && map[x][y - 1]) {
        bool flag = true;
        for(int i = 0; i < k; i++)
            if( walls[i].y1 == walls[i].y2 &&
                walls[i].y1 == y &&
                walls[i].x1 <= x &&
                walls[i].x2 > x)
                flag = false;
        if(flag)
            mapRouteSearch(walls, k, map, x, y - 1);
    }
}

void EmptyMap(bool map[][10]) {
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            map[i][j] = true;
}

void mapGenerator(Map *MAP) {
    srand(time(NULL));

    Wall walls[100];
    int last_wall = 3;
    walls[0] = new_Wall(0, 0, 10, 0);
    walls[1] = new_Wall(0, 0, 0, 10);
    walls[2] = new_Wall(10, 0, 10, 10);
    walls[3] = new_Wall(0, 10, 10, 10);

    for(int i = 0; i < 100; i++) {
        int x1, x2, y1, y2;
        x1 = rand() % 10;
        y1 = rand() % 10;
        x2 = rand() % 10;
        y2 = rand() % 10;
        if(rand() % 2) {
            y2 = y1;
        } else {
            x2 = x1;
        }
        if(x1 == x2 && y1 == y2)
            continue;

        walls[last_wall + 1] = new_Wall(x1, y1, x2, y2);
        bool map_test[10][10];
        EmptyMap(map_test);
        mapRouteSearch(walls, last_wall + 1, map_test, 0, 0);
        PrintMap(map_test);
        printf("_________________________________\n");
        if(ValidMap(map_test))
            last_wall++;
    }

    MAP->wall_count = last_wall;
    for(int i = 0; i <= last_wall; i++)
        MAP->walls[i] = walls[i];
}