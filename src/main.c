#include <SDL.h>
#include "manager.h"

Manager manager;

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    manager.window = SDL_CreateWindow(
            "Alter Tank",
            100,
            30,
            100,
            100,
            SDL_WINDOW_OPENGL
    );
    manager.renderer = SDL_CreateRenderer(manager.window, -1, SDL_RENDERER_ACCELERATED);

    Action action = GameMenu(&manager);
    if(action == Exit)
        return 0;
    else if(action == Play2v2)
        manager.tank_count = 2;
    else if(action == Play3v3)
        manager.tank_count = 3;

    InitializeGame(&manager);
}
