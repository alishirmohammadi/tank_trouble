#include "structs.h"
#include "map.h"

bool CreateItem(Item items[], Map *map, int *x, int *y);
void DrawItem(SDL_Renderer *renderer, Item items[], SDL_Texture *textures[]);