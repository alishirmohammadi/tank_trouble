//
// Created by ali on 11/01/19.
//

#ifndef ALTER_TANK_MANAGER_H
#define ALTER_TANK_MANAGER_H
#include "structs.h"
#define BUTTON_DISTANCE 70
#define BUTTON_TOP BUTTON_WIDTH + 20
#define BUTTON_RIGHTMARGIN 20
#define BUTTON_WIDTH 30
#define SCREEN_HEIGHT 380
#define SCREEN_WIDTH 300
#define BUTTON_COUNT 5
#define SMOKE_COUNT 20

void InitializeGame(Manager *manager);
Action GameMenu(Manager *manager);

#endif //ALTER_TANK_MANAGER_H
