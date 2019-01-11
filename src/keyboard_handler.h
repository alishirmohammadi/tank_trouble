#define KEY_UP 0
#define KEY_DOWN 1
#define KEY_LEFT 2
#define KEY_RIGHT 3
#define KEY_M 4
#define KEY_E 5
#define KEY_D 6
#define KEY_S 7
#define KEY_F 8
#define KEY_Q 9
#define KEY_A 10
#define KEY_W 11
#define KEY_U 15
#define KEY_J 16
#define KEY_H 17
#define KEY_K 18
#define KEY_SLASH 19
#define KEY_T 20

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>


void handleKeyboard(SDL_Event event);
void disableKey(int keyCode);
bool getKeyState(int keyCode);