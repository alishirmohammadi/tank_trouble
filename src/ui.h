//
// Created by ali on 12/01/19.
//

#ifndef ALTER_TANK_UI_H
#define ALTER_TANK_UI_H

#define UI_MARGIN 5
#define TEXT_HEIGHT 10
#define UI_WIDTH (UI_MARGIN*2+34+TEXT_HEIGHT)
#include <SDL_render.h>
#include "structs.h"

void UITankScore(SDL_Renderer *renderer, Tank tank[], int count, int mapMaxX, int mapMaxY, SDL_Texture *Textures[]);

#endif //ALTER_TANK_UI_H
