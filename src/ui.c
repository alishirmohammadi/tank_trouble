#include "ui.h"
#include "structs.h"
#include "tank.h"
#include "map.h"

void UITankScore(SDL_Renderer *renderer, Tank tank[], int count, int mapMaxX, int mapMaxY) {
    int ScreenWidth = PointMapToPixel(mapMaxX) + MAP_MARGIN;
    int ScreenHeight = PointMapToPixel(mapMaxY) + MAP_MARGIN;
    int UI_Y = ScreenHeight + TANK_RADIUS;
    int UI_X = 0;
    for(int i = 0; i < count; i++) {
        Tank t = tank[i];
        UI_X = ScreenWidth * (i + 1) / (count + 1);
        t.x = UI_X;
        t.y = UI_Y;
        t.angle = 0;
        t.enable = true;
        char score_str[5];
        strcpy(score_str, "");
        sprintf(score_str, "%d", t.score);
        int center_place = strlen(score_str);
        DrawTank((Tank[]) {t}, 1, renderer);
        stringRGBA(
                renderer,
                UI_X - center_place * 4,
                UI_Y + TEXT_HEIGHT + 10,
                score_str,
                0,
                0,
                0,
                255
        );
    }
}