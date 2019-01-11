#include "manager.h"
#include "structs.h"
#include "colors.h"
#include "keyboard_handler.h"
#include "map.h"
#include "physics.h"
#include "tank.h"
#include <time.h>

const int EXIT = 12345;

int handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return EXIT;
        handleKeyboard(event);
    }
}

void InitializeGame(Manager *manager) {
    srand(time(NULL));
    manager->tank_count = 3;

    LoadMap(&manager->map, "/home/ali/Desktop/2.txt");
    // mapGenerator(&manager->map);

    manager->tanks[0].x = PointMapToPixel(rand() % (maxMapX(&manager->map) - 1) + 0.5);
    manager->tanks[0].y = PointMapToPixel(rand() % (maxMapY(&manager->map) - 1) + 0.5);
    manager->tanks[0].enable = true;
    manager->tanks[0].color = COLOR_RED;
    manager->tanks[0].right_key = KEY_RIGHT;
    manager->tanks[0].left_key = KEY_LEFT;
    manager->tanks[0].forward_key = KEY_UP;
    manager->tanks[0].backward_key = KEY_DOWN;
    manager->tanks[0].fire_key = KEY_SLASH;
    manager->tanks[0].angle = rand() % 31415 / 500.0;

    manager->tanks[1].x = PointMapToPixel(rand() % (maxMapX(&manager->map) - 1) + 0.5);
    manager->tanks[1].y = PointMapToPixel(rand() % (maxMapY(&manager->map) - 1) + 0.5);
    manager->tanks[1].enable = true;
    manager->tanks[1].color = COLOR_BLUE;
    manager->tanks[1].right_key = KEY_D;
    manager->tanks[1].left_key = KEY_A;
    manager->tanks[1].forward_key = KEY_W;
    manager->tanks[1].backward_key = KEY_S;
    manager->tanks[1].fire_key = KEY_Q;
    manager->tanks[1].angle = rand() % 31415 / 500.0;

    manager->tanks[2].x = PointMapToPixel(rand() % (maxMapX(&manager->map) - 1) + 0.5);
    manager->tanks[2].y = PointMapToPixel(rand() % (maxMapY(&manager->map) - 1) + 0.5);
    manager->tanks[2].enable = true;
    manager->tanks[2].color = COLOR_GREEN;
    manager->tanks[2].right_key = KEY_K;
    manager->tanks[2].left_key = KEY_H;
    manager->tanks[2].forward_key = KEY_U;
    manager->tanks[2].backward_key = KEY_J;
    manager->tanks[2].fire_key = KEY_M;
    manager->tanks[2].angle = rand() % 31415 / 500.0;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(
            "Alter Tank",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            PointMapToPixel(maxMapX(&manager->map)) + MAP_MARGIN + 100,
            PointMapToPixel(maxMapY(&manager->map)) + MAP_MARGIN,
            SDL_WINDOW_OPENGL
    );

    // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    const double FPS = 100;
    while (handleEvents() != EXIT) {
        int start_ticks = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
        SDL_RenderClear(renderer);

        PhysicsRenderer(manager->tanks, manager->tank_count, &manager->map);
        DrawMap(&manager->map, renderer);
        DrawTank(manager->tanks, manager->tank_count, renderer);
        DrawTanksBullets(manager->tanks, manager->tank_count, renderer);


        SDL_RenderPresent(renderer);

        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}