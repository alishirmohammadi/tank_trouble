#include "manager.h"
#include "structs.h"
#include "colors.h"
#include "keyboard_handler.h"
#include "map.h"
#include "physics.h"
#include "tank.h"
#include "particle.h"
#include <time.h>

Action gameHandleEvent() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return Exit;
        handleKeyboard(event);
    }
}

Action handleEvents(Manager *manager) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return Exit;
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            for(int i = 0; i < BUTTON_COUNT; i++) {
                if(manager->button[i].state == Pressed)
                continue;
                manager->button[i].state = x > BUTTON_RIGHTMARGIN && x < SCREEN_WIDTH - BUTTON_RIGHTMARGIN && y > BUTTON_TOP + BUTTON_DISTANCE * i - BUTTON_WIDTH && y < BUTTON_TOP + BUTTON_DISTANCE * i + BUTTON_WIDTH
                                           ? Pressed : Idle;
            }
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            for(int i = 0; i < BUTTON_COUNT; i++) {
                if(manager->button[i].state == Pressed && x > BUTTON_RIGHTMARGIN && x < SCREEN_WIDTH - BUTTON_RIGHTMARGIN && y > BUTTON_TOP + BUTTON_DISTANCE * i - BUTTON_WIDTH && y < BUTTON_TOP + BUTTON_DISTANCE * i + BUTTON_WIDTH) {
                    manager->button[i].state = x > BUTTON_RIGHTMARGIN && x < SCREEN_WIDTH - BUTTON_RIGHTMARGIN && y > BUTTON_TOP + BUTTON_DISTANCE * i - BUTTON_WIDTH && y < BUTTON_TOP + BUTTON_DISTANCE * i + BUTTON_WIDTH
                                               ? Hover : Idle;
                    return manager->button[i].action;
                }
                manager->button[i].state = x > BUTTON_RIGHTMARGIN && x < SCREEN_WIDTH - BUTTON_RIGHTMARGIN && y > BUTTON_TOP + BUTTON_DISTANCE * i - BUTTON_WIDTH && y < BUTTON_TOP + BUTTON_DISTANCE * i + BUTTON_WIDTH
                                           ? Hover : Idle;
            }
        }
    }
    return None;
}

void DrawButton(SDL_Renderer *renderer, Button buttons[]) {
    for(int i = 0; i < BUTTON_COUNT; i++) {
        Color c = buttons[i].color;
        if(buttons[i].state == Hover)
            c = buttons[i].hover_color;
        else if(buttons[i].state == Pressed)
            c = buttons[i].pressed_color;
        thickLineRGBA(
                renderer,
                BUTTON_RIGHTMARGIN,
                BUTTON_TOP + BUTTON_DISTANCE * i,
                SCREEN_WIDTH - BUTTON_RIGHTMARGIN,
                BUTTON_TOP + BUTTON_DISTANCE * i,
                BUTTON_WIDTH * 2,
                c.red,
                c.green,
                c.blue,
                c.alpha
        );
        int center_place = strlen(buttons[i].text);
        stringRGBA(
                renderer,
                SCREEN_WIDTH / 2 - center_place * 4,
                BUTTON_TOP + BUTTON_DISTANCE * i,
                buttons[i].text,
                buttons[i].text_color.red,
                buttons[i].text_color.green,
                buttons[i].text_color.blue,
                buttons[i].text_color.alpha
        );
        thickLineRGBA(
                renderer,
                BUTTON_RIGHTMARGIN,
                BUTTON_TOP + BUTTON_DISTANCE * i + BUTTON_WIDTH,
                SCREEN_WIDTH - BUTTON_RIGHTMARGIN,
                BUTTON_TOP + BUTTON_DISTANCE * i + BUTTON_WIDTH,
                3,
                buttons[i].text_color.red,
                buttons[i].text_color.green,
                buttons[i].text_color.blue,
                buttons[i].text_color.alpha
        );
    }
}

Action GameMenu(Manager *manager) {
    manager->tank_count = 3;

    strcpy(manager->button[0].text, "2 Players");
    manager->button[0].action = Play2v2;
    manager->button[0].color = COLOR_BUTTON;
    manager->button[0].hover_color = COLOR_BUTTON_HOVER;
    manager->button[0].pressed_color = COLOR_BUTTON_PRESSED;
    manager->button[0].text_color = COLOR_BLACK;
    manager->button[0].state = Idle;

    strcpy(manager->button[1].text, "3 Players");
    manager->button[1].action = Play3v3;
    manager->button[1].color = COLOR_BUTTON;
    manager->button[1].hover_color = COLOR_BUTTON_HOVER;
    manager->button[1].pressed_color = COLOR_BUTTON_PRESSED;
    manager->button[1].text_color = COLOR_BLACK;
    manager->button[1].state = Idle;

    strcpy(manager->button[2].text, "About Game");
    manager->button[2].action = About;
    manager->button[2].color = COLOR_BUTTON;
    manager->button[2].hover_color = COLOR_BUTTON_HOVER;
    manager->button[2].pressed_color = COLOR_BUTTON_PRESSED;
    manager->button[2].text_color = COLOR_BLACK;
    manager->button[2].state = Idle;

    strcpy(manager->button[3].text, "Help");
    manager->button[3].action = Help;
    manager->button[3].color = COLOR_BUTTON;
    manager->button[3].hover_color = COLOR_BUTTON_HOVER;
    manager->button[3].pressed_color = COLOR_BUTTON_PRESSED;
    manager->button[3].text_color = COLOR_BLACK;
    manager->button[3].state = Idle;

    strcpy(manager->button[4].text, "Quit");
    manager->button[4].action = Exit;
    manager->button[4].color = COLOR_BUTTON;
    manager->button[4].hover_color = COLOR_BUTTON_HOVER;
    manager->button[4].pressed_color = COLOR_BUTTON_PRESSED;
    manager->button[4].text_color = COLOR_BLACK;
    manager->button[4].state = Idle;



    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(
            "Alter Tank",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_OPENGL
    );

    // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Action action;

    const double FPS = 100;
    while (true) {
        action = handleEvents(manager);
        if(action == Exit || action == Play2v2 || action == Play3v3)
            break;

        int start_ticks = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
        SDL_RenderClear(renderer);

        int x, y;
        SDL_GetMouseState(&x, &y);
        for(int i = 0; i < BUTTON_COUNT; i++) {
            if(manager->button[i].state == Pressed)
                continue;
            if(x > BUTTON_RIGHTMARGIN && x < SCREEN_WIDTH - BUTTON_RIGHTMARGIN && y > BUTTON_TOP + BUTTON_DISTANCE * i - BUTTON_WIDTH && y < BUTTON_TOP + BUTTON_DISTANCE * i + BUTTON_WIDTH)
                manager->button[i].state = Hover;
            else
                manager->button[i].state = Idle;
        }

        DrawButton(renderer, manager->button);

        SDL_RenderPresent(renderer);

        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return action;
}

void InitializeGame(Manager *manager) {
    srand(time(NULL));

    LoadMap(&manager->map, "/home/ali/Desktop/3.txt");
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
    manager->tanks[0].score = 0;
    for(int i = 0; i < BULLET_COUNT; i++)
        manager->tanks[0].bullets[i].state = Disable;

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
    manager->tanks[1].score = 0;
    for(int i = 0; i < BULLET_COUNT; i++)
        manager->tanks[1].bullets[i].state = Disable;

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
    manager->tanks[2].score = 0;
    for(int i = 0; i < BULLET_COUNT; i++)
        manager->tanks[2].bullets[i].state = Disable;

    Smoke smoke[SMOKE_COUNT];
    for(int i = 0; i < SMOKE_COUNT; i++) {
        smoke[i].enable = false;
    }

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

    while (gameHandleEvent() != Exit) {
        int start_ticks = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
        SDL_RenderClear(renderer);

        PhysicsRenderer(manager->tanks, manager->tank_count, &manager->map, smoke, SMOKE_COUNT);
        SmokeRenderer(smoke, SMOKE_COUNT);

        DrawMap(&manager->map, renderer);
        DrawTank(manager->tanks, manager->tank_count, renderer);
        DrawTanksBullets(manager->tanks, manager->tank_count, renderer);
        DrawSmoke(renderer, smoke, SMOKE_COUNT);

        SDL_RenderPresent(renderer);

        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}