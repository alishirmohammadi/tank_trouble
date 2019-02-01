#include <time.h>
#include "items.h"
#include "tank.h"

double minimum(double a, double b) {
    return (a > b ? b : a);
}

double local_magnitude(double x, double y) {
    return sqrt(x * x + y * y);
}

bool CreateItem(Item items[], Map *map, int *x, int *y, Manager *manager) {
    srand(time(NULL));
    int i = 0;
    while(items[i].enable == true && i < MAX_ITEM_COUNT) i++;
    if(i == MAX_ITEM_COUNT) {
        items[i].enable = false;
        return false;
    }
    int mapMaxX = maxMapX(map);
    int mapMaxY = maxMapY(map);
    int ItemX = PointMapToPixel(rand() % (mapMaxX - 1) + 0.5);
    int ItemY = PointMapToPixel(rand() % (mapMaxY - 1) + 0.5);
    int ItemType = rand() % 4;
    for(int j = 0; j < MAX_ITEM_COUNT; j++) {
        if(items[j].enable == true && items[j].x == items[i].x && items[j].y == items[i].y) {
            items[i].enable = false;
            items[i].x = -100;
            items[i].y = -100;
            return false;
        }
        if(items[j].enable == true && items[j].type == ItemType) {
            items[i].enable = false;
            items[i].x = -100;
            items[i].y = -100;
            return false;
        }
    }
    double minDistance = 10000;
    for(int j = 0; j < manager->tank_count; j++) {
        minDistance = minimum(minDistance, local_magnitude(ItemX - manager->tanks[j].x, ItemY - manager->tanks[j].y));
    }
    if(minDistance < 59) {
        items[i].enable = false;
        items[i].x = -100;
        items[i].y = -100;
        return false;
    } else {
        items[i].enable = true;
        items[i].x = ItemX;
        items[i].y = ItemY;
        items[i].type = ItemType;
        *x = ItemX;
        *y = ItemY;
        return true;
    }
}

void DrawItem(SDL_Renderer *renderer, Item items[], SDL_Texture *textures[]) {
    for(int i = 0; i < MAX_ITEM_COUNT; i++) {
        if(items[i].enable == false) continue;
        SDL_Rect rect = {items[i].x - 19, items[i].y - 19, 38, 38};
        if(items[i].type == Bomb) {
            rect.x = items[i].x - 16;
            rect.y = items[i].y - 16;
            rect.w = 32;
            rect.h = 32;
        }
        if(items[i].type == MachineGun) {
            rect.x = items[i].x - 18;
            rect.y = items[i].y - 18;
            rect.w = 36;
            rect.h = 36;
        }
        if(items[i].type == Mine) {
            rect.x = items[i].x - 16;
            rect.y = items[i].y - 16;
            rect.w = 32;
            rect.h = 32;
        }

        SDL_RenderCopy(renderer, textures[items[i].type], NULL, &rect);
    }
}