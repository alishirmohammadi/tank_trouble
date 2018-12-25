#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "tank.h"
#include "map.h"
#include "keyboard_handler.h"
#include "colors.h"
#include "physics.h"


const int EXIT = 12345;

Tank tanks[3];
const int TANKS_COUNT = 3;
Map map;

int handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
    	if (event.type == SDL_QUIT)
    	    return EXIT;
    	handleKeyboard(event);
    }
}

int main() {
    tanks[0].x = 100;
    tanks[0].y = 100;
    tanks[0].color = COLOR_RED;
    tanks[0].right_key = KEY_RIGHT;
    tanks[0].left_key = KEY_LEFT;
    tanks[0].forward_key = KEY_UP;
    tanks[0].backward_key = KEY_DOWN;
    tanks[0].fire_key = KEY_SLASH;
    tanks[0].angle = 0;

    tanks[1].x = 230;
    tanks[1].y = 230;
    tanks[1].color = COLOR_BLUE;
    tanks[1].right_key = KEY_F;
    tanks[1].left_key = KEY_S;
    tanks[1].forward_key = KEY_E;
    tanks[1].backward_key = KEY_D;
    tanks[1].fire_key = KEY_Q;
    tanks[1].angle = 0;

    tanks[2].x = 100;
    tanks[2].y = 230;
    tanks[2].color = COLOR_GREEN;
    tanks[2].right_key = KEY_K;
    tanks[2].left_key = KEY_H;
    tanks[2].forward_key = KEY_U;
    tanks[2].backward_key = KEY_J;
    tanks[2].fire_key = KEY_M;
    tanks[2].angle = 0;

    LoadMap(&map, "/home/ali/Desktop/1.txt");

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(
            "Alter Tank",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            pointMapToPixel(maxMapX(&map)) + MAP_MARGIN + 100,
            pointMapToPixel(maxMapY(&map)) + MAP_MARGIN,
            SDL_WINDOW_OPENGL
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    const double FPS = 60;
    while (handleEvents() != EXIT) {
        int start_ticks = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
    	SDL_RenderClear(renderer);

        physics_renderer(tanks, TANKS_COUNT, &map);
        DrawMap(&map, renderer);
        DrawTanksBullets(tanks, TANKS_COUNT, renderer);
        DrawTank(tanks, TANKS_COUNT, renderer);


        SDL_RenderPresent(renderer);

        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
