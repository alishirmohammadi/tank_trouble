#include "manager.h"
#include "structs.h"
#include "colors.h"
#include "keyboard_handler.h"
#include "map.h"
#include "physics.h"
#include "tank.h"
#include "particle.h"
#include "ui.h"
#include "items.h"
#include <time.h>
#define RELOAD_TIME 3
#define TANK_COLOR_COUNT 6
#define ITEM_TYPE_COUNT 4
#define ITEM_FREQUENCY 300

SDL_Surface *Surfaces[TANK_COLOR_COUNT], *items_surfaces[ITEM_TYPE_COUNT];
SDL_Texture *Textures[TANK_COLOR_COUNT], *items_textures[ITEM_TYPE_COUNT];

void SaveGame(Manager *manager) {
    FILE *f = fopen("../game.dat", "w");
    fprintf(f, "%d\n", manager->tank_count);
    for(int i = 0; i < manager->tank_count; i++) {
        fprintf(f, "%f %f %f %d\n", manager->tanks[i].x, manager->tanks[i].y, manager->tanks[i].angle, manager->tanks[i].score);
    }
    fprintf(f, "%d", manager->mapIndex);
    fclose(f);
}

Action gameHandleEvent() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return Exit;
        }
        handleKeyboard(event);
        if (event.key.keysym.sym == SDLK_ESCAPE)
            return Pause;
    }
}

int ScreenWidth;
ButtonState btnState[3];

Action PauseMenuHandleEvent() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return Exit;
        }
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            for(int i = 0; i < 4; i++) {
                if(x >= ScreenWidth / 2 - 100 && x <= ScreenWidth / 2 + 100)
                    if(y >= BUTTON_TOP + i * BUTTON_DISTANCE - BUTTON_WIDTH && y <= BUTTON_TOP + i * BUTTON_DISTANCE + BUTTON_WIDTH)
                        btnState[i] = Pressed;
            }
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            for(int i = 0; i < 4; i++) {
                if(btnState[i] == Pressed) {
                    btnState[i] = Idle;
                    if(x >= ScreenWidth / 2 - 100 && x <= ScreenWidth / 2 + 100)
                        if(y >= BUTTON_TOP + i * BUTTON_DISTANCE - BUTTON_WIDTH && y <= BUTTON_TOP + i * BUTTON_DISTANCE + BUTTON_WIDTH) {
                            if (i == 0) return Resume;
                            if (i == 1) return Save;
                            if (i == 2) return ShowMenu;
                        }
                }
            }
        }
    }
}

Action WinHandleEvent() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return Exit;
        }
    }
}


void PauseMenu(Manager *manager) {
    const double FPS = 100;
    Action action;
    int mapMaxX = maxMapX(&manager->map);
    ScreenWidth = PointMapToPixel(mapMaxX) + MAP_MARGIN;
    for(int i = 0; i < 3; i++)
        btnState[i] = Idle;

    char Text[3][10];
    strcpy(Text[0], "Resume");
    strcpy(Text[1], "Save");
    strcpy(Text[2], "Main Menu");

    while (true) {
        action = PauseMenuHandleEvent();
        if(action == Exit || action == Resume)
            break;
        if(action == Save) {
            SaveGame(manager);
            break;
        }
        SDL_SetRenderDrawColor(manager->renderer, 230, 230, 230, 255);
        SDL_RenderClear(manager->renderer);
        for(int i = 0; i < 3; i++)
            if(btnState[i] != Pressed)
                btnState[i] = Idle;

        int x, y;
        SDL_GetMouseState(&x, &y);
        for(int i = 0; i < 3; i++) {
            if(x >= ScreenWidth / 2 - 100 && x <= ScreenWidth / 2 + 100)
                if(y >= BUTTON_TOP + i * BUTTON_DISTANCE - BUTTON_WIDTH && y <= BUTTON_TOP + i * BUTTON_DISTANCE + BUTTON_WIDTH)
                    if(btnState[i] != Pressed) btnState[i] = Hover;
        }

        for(int i = 0; i < 3; i++) {
            Color c = btnState[i] == Idle ? COLOR_BUTTON : (btnState[i] == Hover ? COLOR_BUTTON_HOVER
                                                                                 : COLOR_BUTTON_PRESSED);
            thickLineRGBA(
                    manager->renderer,
                    ScreenWidth / 2 - 100,
                    BUTTON_TOP + i * BUTTON_DISTANCE,
                    ScreenWidth / 2 + 100,
                    BUTTON_TOP + i * BUTTON_DISTANCE,
                    BUTTON_WIDTH * 2,
                    c.red,
                    c.green,
                    c.blue,
                    c.alpha
            );
            thickLineRGBA(
                    manager->renderer,
                    ScreenWidth / 2 - 100,
                    BUTTON_TOP + i * BUTTON_DISTANCE + BUTTON_WIDTH,
                    ScreenWidth / 2 + 100,
                    BUTTON_TOP + i * BUTTON_DISTANCE + BUTTON_WIDTH,
                    3,
                    0, 0, 0, 255
            );
            float scale = 1.5;
            SDL_RenderSetScale(manager->renderer, scale, scale);
            stringRGBA(
                    manager->renderer,
                    (ScreenWidth / 2 - strlen(Text[i]) * 6) / scale,
                    (BUTTON_TOP + i * BUTTON_DISTANCE) / scale,
                    Text[i],
                    0, 0, 0, 255
            );
            SDL_RenderSetScale(manager->renderer, 1, 1);
        }

        SDL_RenderPresent(manager->renderer);

        int start_ticks = SDL_GetTicks();
        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }
}


void WinMenu(Manager *manager, int winner) {
    const double FPS = 100;
    Action action;
    int mapMaxX = maxMapX(&manager->map);
    ScreenWidth = PointMapToPixel(mapMaxX) + MAP_MARGIN;

    while (true) {
        action = WinHandleEvent();
        if(action == Exit || action == Resume)
            break;

        SDL_SetRenderDrawColor(manager->renderer, 230, 230, 230, 255);
        SDL_RenderClear(manager->renderer);

        float scale = 2;
        SDL_RenderSetScale(manager->renderer, scale, scale);
        char s[20];
        sprintf(s, "Player %d win", winner);
        stringRGBA(
                manager->renderer,
                (ScreenWidth / 2 - 12 * 8) / scale,
                (BUTTON_TOP + 2 * BUTTON_DISTANCE) / scale,
                s,
                0, 0, 0, 255
        );
        SDL_RenderSetScale(manager->renderer, 1, 1);


        SDL_RenderPresent(manager->renderer);

        int start_ticks = SDL_GetTicks();
        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }
}


void InitializeGame(Manager *manager) {
    srand(time(0));

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
    items_surfaces[Bomb] = SDL_LoadBMP("../images/bomb.bmp");
    items_surfaces[Mine] = SDL_LoadBMP("../images/mine.bmp");
    items_surfaces[MachineGun] = SDL_LoadBMP("../images/machine_gun.bmp");
    items_surfaces[Laser] = SDL_LoadBMP("../images/laser.bmp");

    Textures[0] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[0]);
    Textures[1] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[1]);
    Textures[2] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[2]);
    Textures[3] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[3]);
    Textures[4] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[4]);
    Textures[5] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[5]);
    items_textures[Bomb] = SDL_CreateTextureFromSurface(manager->renderer, items_surfaces[Bomb]);
    items_textures[Mine] = SDL_CreateTextureFromSurface(manager->renderer, items_surfaces[Mine]);
    items_textures[MachineGun] = SDL_CreateTextureFromSurface(manager->renderer, items_surfaces[MachineGun]);
    items_textures[Laser] = SDL_CreateTextureFromSurface(manager->renderer, items_surfaces[Laser]);


    FILE *f = fopen("../alter_tank.conf", "r");
    int max_score, tank1Color, tank2Color, tank3Color;
    fscanf(f, "%d%d%d%d", &max_score, &tank1Color, &tank2Color, &tank3Color);

    if(manager->isLoaded == false) {
        manager->tanks[0].score = 0;
        manager->tanks[1].score = 0;
        manager->tanks[2].score = 0;
    }

    manager->tanks[0].color = TankColors[tank1Color];
    manager->tanks[1].color = TankColors[tank2Color];
    manager->tanks[2].color = TankColors[tank3Color];
    manager->tanks[0].colorIndex = tank1Color;
    manager->tanks[1].colorIndex = tank2Color;
    manager->tanks[2].colorIndex = tank3Color;


    while(true) {
        if (manager->isLoaded == false)
            manager->mapIndex = rand() % MAP_COUNT;
        LoadMap(&manager->map, MapFiles[manager->mapIndex]);
        int mapMaxX = maxMapX(&manager->map);
        int mapMaxY = maxMapY(&manager->map);

        SDL_SetWindowSize(
                manager->window,
                PointMapToPixel(mapMaxX) + MAP_MARGIN,
                PointMapToPixel(mapMaxY) + MAP_MARGIN + UI_WIDTH
        );

        Bullet small_bullets[3][20];
        Bullet machineGunBullets[30];
        for (int j = 0; j < 3; j++)
            for (int i = 0; i < 20; i++)
                small_bullets[j][i].state = Disable;
        for (int i = 0; i < 30; i++)
            machineGunBullets[i].state = Disable;
        if (manager->isLoaded == false) {
            manager->tanks[0].x = PointMapToPixel(rand() % (mapMaxX - 1) + 0.5);
            manager->tanks[0].y = PointMapToPixel(rand() % (mapMaxY - 1) + 0.5);
            manager->tanks[0].angle = rand() % 31415 / 500.0;
        }
        manager->tanks[0].enable = true;
        manager->tanks[0].right_key = KEY_RIGHT;
        manager->tanks[0].left_key = KEY_LEFT;
        manager->tanks[0].forward_key = KEY_UP;
        manager->tanks[0].backward_key = KEY_DOWN;
        manager->tanks[0].fire_key = KEY_SLASH;
        manager->tanks[0].last_smoke_time = 0;
        manager->tanks[0].hasBomb = false;
        manager->tanks[0].hasMachineGun = false;
        manager->tanks[0].hasMine = false;
        manager->tanks[0].hasLaser = false;
        for (int i = 0; i < BULLET_COUNT; i++) {
            manager->tanks[0].bullets[i].state = Disable;
            manager->tanks[0].bullets[i].isBomb = false;
        }

        if(manager->isLoaded == false) {
            manager->tanks[1].x = PointMapToPixel(rand() % (mapMaxX - 1) + 0.5);
            manager->tanks[1].y = PointMapToPixel(rand() % (mapMaxY - 1) + 0.5);
            manager->tanks[1].angle = rand() % 31415 / 500.0;
        }
        manager->tanks[1].enable = true;
        manager->tanks[1].right_key = KEY_D;
        manager->tanks[1].left_key = KEY_A;
        manager->tanks[1].forward_key = KEY_W;
        manager->tanks[1].backward_key = KEY_S;
        manager->tanks[1].fire_key = KEY_Q;
        manager->tanks[1].last_smoke_time = 0;
        manager->tanks[1].hasBomb = false;
        manager->tanks[1].hasMachineGun = false;
        manager->tanks[1].hasMine = false;
        manager->tanks[1].hasLaser = false;
        for (int i = 0; i < BULLET_COUNT; i++) {
            manager->tanks[1].bullets[i].state = Disable;
            manager->tanks[1].bullets[i].isBomb = false;
        }

        if(manager->isLoaded == false) {
            manager->tanks[2].x = PointMapToPixel(rand() % (mapMaxX - 1) + 0.5);
            manager->tanks[2].y = PointMapToPixel(rand() % (mapMaxY - 1) + 0.5);
            manager->tanks[2].angle = rand() % 31415 / 500.0;
        }
        manager->tanks[2].enable = true;
        manager->tanks[2].right_key = KEY_K;
        manager->tanks[2].left_key = KEY_H;
        manager->tanks[2].forward_key = KEY_U;
        manager->tanks[2].backward_key = KEY_J;
        manager->tanks[2].fire_key = KEY_M;
        manager->tanks[2].last_smoke_time = 0;
        manager->tanks[2].hasBomb = false;
        manager->tanks[2].hasMachineGun = false;
        manager->tanks[2].hasMine = false;
        manager->tanks[2].hasLaser = false;
        for (int i = 0; i < BULLET_COUNT; i++) {
            manager->tanks[2].bullets[i].state = Disable;
            manager->tanks[2].bullets[i].isBomb = false;
        }

        Smoke smoke[SMOKE_COUNT];
        for (int i = 0; i < SMOKE_COUNT; i++) {
            smoke[i].enable = false;
        }

        for (int i = 0; i < MAX_ITEM_COUNT; i++) {
            manager->item[i].enable = false;
            manager->item[i].x = -100;
            manager->item[i].y = -100;
        }


        const double FPS = 100;
        Action action;

        while (true) {
            action = gameHandleEvent();
            if(action == Exit)
                break;
            if(action == Pause)
                PauseMenu(manager);

            int start_ticks = SDL_GetTicks();

            if(rand() % ITEM_FREQUENCY == 0) {
                int x, y;
                if (CreateItem(manager->item, &manager->map, &x, &y, manager) == true) {
                    int disableSmokeId = 0;
                    while (disableSmokeId < SMOKE_COUNT && smoke[disableSmokeId].enable == true)
                        disableSmokeId++;
                    SmallSmoke(&smoke[disableSmokeId], x, y);
                }
            }

            SDL_SetRenderDrawColor(manager->renderer, 230, 230, 230, 255);
            SDL_RenderClear(manager->renderer);

            PhysicsRenderer(manager->tanks, manager->tank_count, &manager->map, smoke, SMOKE_COUNT, manager, small_bullets);
            SmokeRenderer(smoke, SMOKE_COUNT);

            DrawMap(&manager->map, manager->renderer);
            DrawItem(manager->renderer, manager->item, items_textures);
            DrawTank(manager->tanks, manager->tank_count, manager->renderer);
            DrawTanksBullets(manager->tanks, manager->tank_count, manager->renderer);
            DrawSmallBullets(manager->renderer, small_bullets);
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

        for(int i = 0; i < manager->tank_count; i++) {
            if(manager->tanks[i].enable) {
                manager->tanks[i].score++;
            }
        }

        int Winner = -1;
        for(int i = 0; i < manager->tank_count; i++)
            if(manager->tanks[i].score >= max_score)
                Winner = i;

        if(Winner != -1) {
            WinMenu(manager, Winner + 1);
            action = Exit;
        }

        if (action == Exit)
            break;

        manager->isLoaded = false;
    }

    SDL_DestroyRenderer(manager->renderer);
    SDL_DestroyWindow(manager->window);
    SDL_Quit();
}