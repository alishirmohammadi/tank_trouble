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
#include "manager.h"

Manager manager;

int main() {
    Action action = GameMenu(&manager);
    if(action == Exit)
        return 0;
    else if(action == Play2v2) {
        manager.tank_count = 2;
        InitializeGame(&manager);
    } else if(action == Play3v3) {
        manager.tank_count = 3;
        InitializeGame(&manager);
    }
}
