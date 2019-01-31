#include "manager.h"
#include "structs.h"
#include "colors.h"
#include "keyboard_handler.h"
#include "map.h"
#include "physics.h"
#include "tank.h"
#include "particle.h"
#include "ui.h"
#include <time.h>
#define RELOAD_TIME 3
#define TANK_COLOR_COUNT 6

SDL_Surface *Surfaces[TANK_COLOR_COUNT];
SDL_Texture *Textures[TANK_COLOR_COUNT];

Action gameHandleEvent() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return Exit;
        handleKeyboard(event);
    }
}


void InitializeGame(Manager *manager) {
    srand(time(NULL));

    char MapFiles[9][40];
    const int MAP_COUNT = 9;
    strcpy(MapFiles[0], "../maps/1.txt");
    strcpy(MapFiles[1], "../maps/2.txt");
    strcpy(MapFiles[2], "../maps/3.txt");
    strcpy(MapFiles[3], "../maps/4.txt");
    strcpy(MapFiles[4], "../maps/5.txt");
    strcpy(MapFiles[5], "../maps/6.txt");
    strcpy(MapFiles[6], "../maps/7.txt");
    strcpy(MapFiles[7], "../maps/8.txt");
    strcpy(MapFiles[8], "../maps/9.txt");

    Color TankColors[6];
    TankColors[0] = COLOR_RED;
    TankColors[1] = COLOR_BLUE;
    TankColors[2] = COLOR_GREEN;
    TankColors[3] = COLOR_YELLOW;
    TankColors[4] = COLOR_ORANGE;
    TankColors[5] = COLOR_BROWN;

    Surfaces[0] = SDL_LoadBMP("../images/tank_red.bmp");
    Surfaces[1] = SDL_LoadBMP("../images/tank_blue.bmp");
    Surfaces[2] = SDL_LoadBMP("../images/tank_green.bmp");
    Surfaces[3] = SDL_LoadBMP("../images/tank_yellow.bmp");
    Surfaces[4] = SDL_LoadBMP("../images/tank_orange.bmp");
    Surfaces[5] = SDL_LoadBMP("../images/tank_brown.bmp");

    Textures[0] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[0]);
    Textures[1] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[1]);
    Textures[2] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[2]);
    Textures[3] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[3]);
    Textures[4] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[4]);
    Textures[5] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[5]);


    FILE *f = fopen("../alter_tank.conf", "r");
    int max_score, tank1Color, tank2Color, tank3Color;
    fscanf(f, "%d%d%d%d", &max_score, &tank1Color, &tank2Color, &tank3Color);

    manager->tanks[0].score = 0;
    manager->tanks[1].score = 0;
    manager->tanks[2].score = 0;
    manager->tanks[0].color = TankColors[tank1Color];
    manager->tanks[1].color = TankColors[tank2Color];
    manager->tanks[2].color = TankColors[tank3Color];
    manager->tanks[0].colorIndex = tank1Color;
    manager->tanks[1].colorIndex = tank2Color;
    manager->tanks[2].colorIndex = tank3Color;

    while(true) {
        LoadMap(&manager->map, MapFiles[rand() % MAP_COUNT]);
        int mapMaxX = maxMapX(&manager->map);
        int mapMaxY = maxMapY(&manager->map);

        SDL_SetWindowSize(
                manager->window,
                PointMapToPixel(mapMaxX) + MAP_MARGIN,
                PointMapToPixel(mapMaxY) + MAP_MARGIN + UI_WIDTH
        );

        // mapGenerator(&manager->map);
        manager->tanks[0].x = PointMapToPixel(rand() % (mapMaxX - 1) + 0.5);
        manager->tanks[0].y = PointMapToPixel(rand() % (mapMaxY - 1) + 0.5);
        manager->tanks[0].enable = true;
        manager->tanks[0].right_key = KEY_RIGHT;
        manager->tanks[0].left_key = KEY_LEFT;
        manager->tanks[0].forward_key = KEY_UP;
        manager->tanks[0].backward_key = KEY_DOWN;
        manager->tanks[0].fire_key = KEY_SLASH;
        manager->tanks[0].angle = rand() % 31415 / 500.0;
        manager->tanks[0].last_smoke_time = 0;
        for (int i = 0; i < BULLET_COUNT; i++)
            manager->tanks[0].bullets[i].state = Disable;

        manager->tanks[1].x = PointMapToPixel(rand() % (mapMaxX - 1) + 0.5);
        manager->tanks[1].y = PointMapToPixel(rand() % (mapMaxY - 1) + 0.5);
        manager->tanks[1].enable = true;
        manager->tanks[1].right_key = KEY_D;
        manager->tanks[1].left_key = KEY_A;
        manager->tanks[1].forward_key = KEY_W;
        manager->tanks[1].backward_key = KEY_S;
        manager->tanks[1].fire_key = KEY_Q;
        manager->tanks[1].angle = rand() % 31415 / 500.0;
        manager->tanks[1].last_smoke_time = 0;
        for (int i = 0; i < BULLET_COUNT; i++)
            manager->tanks[1].bullets[i].state = Disable;

        manager->tanks[2].x = PointMapToPixel(rand() % (mapMaxX - 1) + 0.5);
        manager->tanks[2].y = PointMapToPixel(rand() % (mapMaxY - 1) + 0.5);
        manager->tanks[2].enable = true;
        manager->tanks[2].right_key = KEY_K;
        manager->tanks[2].left_key = KEY_H;
        manager->tanks[2].forward_key = KEY_U;
        manager->tanks[2].backward_key = KEY_J;
        manager->tanks[2].fire_key = KEY_M;
        manager->tanks[2].angle = rand() % 31415 / 500.0;
        manager->tanks[2].last_smoke_time = 0;
        for (int i = 0; i < BULLET_COUNT; i++)
            manager->tanks[2].bullets[i].state = Disable;

        Smoke smoke[SMOKE_COUNT];
        for (int i = 0; i < SMOKE_COUNT; i++) {
            smoke[i].enable = false;
        }

        const double FPS = 100;
        Action action;

        while (true) {
            action = gameHandleEvent();
            if (action == Exit)
                break;

            int start_ticks = SDL_GetTicks();

            SDL_SetRenderDrawColor(manager->renderer, 230, 230, 230, 255);
            SDL_RenderClear(manager->renderer);

            PhysicsRenderer(manager->tanks, manager->tank_count, &manager->map, smoke, SMOKE_COUNT, manager);
            SmokeRenderer(smoke, SMOKE_COUNT);

            DrawMap(&manager->map, manager->renderer);
            DrawTank(manager->tanks, manager->tank_count, manager->renderer);
            DrawTanksBullets(manager->tanks, manager->tank_count, manager->renderer);
            DrawSmoke(manager->renderer, smoke, SMOKE_COUNT);
            UITankScore(manager->renderer, manager->tanks, manager->tank_count, mapMaxX, mapMaxY, Textures);

            SDL_RenderPresent(manager->renderer);

            int enable_tanks = 0;
            for (int i = 0; i < manager->tank_count; i++)
                enable_tanks += manager->tanks[i].enable == true ? 1 : 0;

            if (enable_tanks < 2 && SDL_GetTicks() - manager->last_destroy_time > RELOAD_TIME * 1000) {
                action = Reload;
                break;
            }

            while (SDL_GetTicks() - start_ticks < 1000 / FPS);
        }
        if (action == Exit)
            break;
        for(int i = 0; i < manager->tank_count; i++)
            if(manager->tanks[i].enable)
                manager->tanks[i].score++;
    }

    SDL_DestroyRenderer(manager->renderer);
    SDL_DestroyWindow(manager->window);
    SDL_Quit();
}