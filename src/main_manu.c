//
// Created by ali on 1/31/19.
//

#include "main_manu.h"
#include "setting.h"

Action handleEvents(Manager *manager) {
    SDL_Event event;
    manager->tanks[0].score = 0;
    manager->tanks[1].score = 0;
    manager->tanks[2].score = 0;
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
        SDL_RenderSetScale(renderer, 1.5, 1.5);
        stringRGBA(
                renderer,
                ((SCREEN_WIDTH / 2) - center_place * 6) / 1.5,
                (BUTTON_TOP + BUTTON_DISTANCE * i - 2) / 1.5,
                buttons[i].text,
                buttons[i].text_color.red,
                buttons[i].text_color.green,
                buttons[i].text_color.blue,
                buttons[i].text_color.alpha
        );
        SDL_RenderSetScale(renderer, 1, 1);
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
    SDL_SetWindowSize(
            manager->window,
            SCREEN_WIDTH,
            SCREEN_HEIGHT
    );

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

    strcpy(manager->button[2].text, "Load Game");
    manager->button[2].action = Load;
    manager->button[2].color = COLOR_BUTTON;
    manager->button[2].hover_color = COLOR_BUTTON_HOVER;
    manager->button[2].pressed_color = COLOR_BUTTON_PRESSED;
    manager->button[2].text_color = COLOR_BLACK;
    manager->button[2].state = Idle;

    strcpy(manager->button[3].text, "Setting");
    manager->button[3].action = Setting;
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

    Action action;

    const double FPS = 100;
    while (true) {
        action = handleEvents(manager);
        if(action == Exit || action == Play2v2 || action == Play3v3)
            break;
        if(action == Setting)
            LoadSetting(manager);

        int start_ticks = SDL_GetTicks();

        SDL_SetRenderDrawColor(manager->renderer, 230, 230, 230, 255);
        SDL_RenderClear(manager->renderer);

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

        DrawButton(manager->renderer, manager->button);

        SDL_RenderPresent(manager->renderer);

        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }

    return action;
}
