#include "ui.h"
#include "structs.h"
#include "tank.h"
#include "map.h"

void UITankScore(SDL_Renderer *renderer, Tank tank[], int count, int mapMaxX, int mapMaxY, SDL_Texture *Textures[]) {
    int ScreenWidth = PointMapToPixel(mapMaxX) + MAP_MARGIN;
    int ScreenHeight = PointMapToPixel(mapMaxY) + MAP_MARGIN;
    int UI_Y = ScreenHeight + TANK_RADIUS;
    int UI_X = 0;
    for(int i = 0; i < count; i++) {
        Tank t = tank[i];
        UI_X = ScreenWidth * (i + 1) / (count + 1);

        SDL_Rect rect = {UI_X - 31, UI_Y - 17, 62, 34};
        SDL_RenderCopy(renderer, Textures[tank[i].colorIndex], NULL, &rect);


        char score_str[5];
        strcpy(score_str, "");
        sprintf(score_str, "%d", t.score);
        int center_place = strlen(score_str);
        float Scale = 1.5;
        SDL_RenderSetScale(renderer, Scale, Scale);
        stringRGBA(
                renderer,
                (UI_X - center_place * 6) / Scale,
                (UI_Y + TEXT_HEIGHT + 13) / Scale,
                score_str,
                0,
                0,
                0,
                255
        );
        SDL_RenderSetScale(renderer, 1, 1);
    }
}