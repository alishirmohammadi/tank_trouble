#include <SDL.h>
#include "manager.h"
#include "main_manu.h"

Manager manager;

void LoadGame() {
    FILE *f = fopen("../game.dat", "r");
    fscanf(f, "%d", &manager.tank_count);
    for(int i = 0; i < manager.tank_count; i++) {
        float x, y, angle;
        int score;
        fscanf(f, "%f%f%f%d", &x, &y, &angle, &score);
        manager.tanks[i].x = x;
        manager.tanks[i].y = y;
        manager.tanks[i].angle = angle;
        manager.tanks[i].score = score;
    }
    fscanf(f, "%d", &manager.mapIndex);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    manager.window = SDL_CreateWindow(
            "Alter Tank",
            100,
            30,
            0,
            0,
            SDL_WINDOW_OPENGL
    );
    manager.renderer = SDL_CreateRenderer(manager.window, -1, SDL_RENDERER_ACCELERATED);

    Action action = GameMenu(&manager);
    if(action == Exit) {
        return 0;
    } else if(action == Play2v2) {
        manager.isLoaded = false;
        manager.tank_count = 2;
    } else if(action == Play3v3) {
        manager.isLoaded = false;
        manager.tank_count = 3;
    } else if(action == Load) {
        LoadGame();
        manager.isLoaded = true;
    }

    InitializeGame(&manager);
}
