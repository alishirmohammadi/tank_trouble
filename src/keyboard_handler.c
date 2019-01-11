#include "keyboard_handler.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <stdbool.h>

bool keyboard[30] = {false};

void handleKeyboard(SDL_Event event) {
    bool keyValue = false;
    if(event.type == SDL_KEYDOWN)
        keyValue = true;
    else if(event.type == SDL_KEYUP)
        keyValue = false;
    if(event.type == SDL_KEYUP || event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_UP) keyboard[KEY_UP] = keyValue;
        if(event.key.keysym.sym == SDLK_DOWN) keyboard[KEY_DOWN] = keyValue;
        if(event.key.keysym.sym == SDLK_LEFT) keyboard[KEY_LEFT] = keyValue;
        if(event.key.keysym.sym == SDLK_RIGHT) keyboard[KEY_RIGHT] = keyValue;
        if(event.key.keysym.sym == SDLK_m) keyboard[KEY_M] = keyValue;
        if(event.key.keysym.sym == SDLK_e) keyboard[KEY_E] = keyValue;
        if(event.key.keysym.sym == SDLK_d) keyboard[KEY_D] = keyValue;
        if(event.key.keysym.sym == SDLK_s) keyboard[KEY_S] = keyValue;
        if(event.key.keysym.sym == SDLK_q) keyboard[KEY_Q] = keyValue;
        if(event.key.keysym.sym == SDLK_f) keyboard[KEY_F] = keyValue;
        if(event.key.keysym.sym == SDLK_u) keyboard[KEY_U] = keyValue;
        if(event.key.keysym.sym == SDLK_j) keyboard[KEY_J] = keyValue;
        if(event.key.keysym.sym == SDLK_h) keyboard[KEY_H] = keyValue;
        if(event.key.keysym.sym == SDLK_t) keyboard[KEY_T] = keyValue;
        if(event.key.keysym.sym == SDLK_k) keyboard[KEY_K] = keyValue;
        if(event.key.keysym.sym == SDLK_w) keyboard[KEY_W] = keyValue;
        if(event.key.keysym.sym == SDLK_a) keyboard[KEY_A] = keyValue;
        if(event.key.keysym.sym == SDLK_SLASH) keyboard[KEY_SLASH] = keyValue;
    }
}

bool getKeyState(int keyCode) {
    return keyboard[keyCode];
}

void disableKey(int keyCode) {
    keyboard[keyCode] = false;
}