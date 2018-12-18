#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

const int EXIT = 12345;
bool up_key = false;
bool left_key = false;
bool right_key = false;
bool down_key = false;

int handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
    	if (event.type == SDL_QUIT)
    	    return EXIT;
    	else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    up_key = true;
                    break;
                case SDLK_DOWN:
                    down_key = true;
                    break;
                case SDLK_LEFT:
                    left_key = true;
                    break;
                case SDLK_RIGHT:
                    right_key = true;
                    break;
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    up_key = false;
                    break;
                case SDLK_DOWN:
                    down_key = false;
                    break;
                case SDLK_LEFT:
                    left_key = false;
                    break;
                case SDLK_RIGHT:
                    right_key = false;
                    break;
            }
    	}
    }
}

int main() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Alter Tank", 20, 20, 800, 600, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    int x = 100;
    int y = 100;
    int dx = 140;
    int dy = 140;
    int speed = 5;

    const double FPS = 40;
    while (1) {
        int start_ticks = SDL_GetTicks();

        if (handleEvents() == EXIT) break;

        SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);

    	SDL_RenderClear(renderer);

    	boxRGBA(renderer, x, y, dx, dy, 255, 0, 0, 255);
        if(up_key) { y -= speed; dy -= speed; }
        if(down_key) { y += speed; dy += speed; }
        if(left_key) { x -= speed; dx -= speed; }
        if(right_key) { x += speed; dx += speed; }

    	SDL_RenderPresent(renderer);

        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
