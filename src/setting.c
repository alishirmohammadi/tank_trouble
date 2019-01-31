#include "setting.h"
#include "colors.h"
#define TANK_COLOR_COUNT 6

Color ButtonColor, ButtonHover, ButtonPress;
ButtonState winDec, winInc, Tank1Left, Tank2Left, Tank3Left, Tank1Right, Tank2Right, Tank3Right, SaveBtn;
int Tank1ColorIndex, Tank2ColorIndex, Tank3ColorIndex;
Color TankColors[TANK_COLOR_COUNT];
SDL_Surface *Surfaces[TANK_COLOR_COUNT];
SDL_Texture *Textures[TANK_COLOR_COUNT];

int WinScore;

int maximum(int a, int b) {
    return (a > b ? a : b);
}

void DrawSetting(SDL_Renderer *renderer) {
    Color WinDecColor = (winDec == Idle ? ButtonColor : (winDec == Hover ? ButtonHover : ButtonPress));
    Color WinIncColor = (winInc == Idle ? ButtonColor : (winInc == Hover ? ButtonHover : ButtonPress));
    Color Tank1LeftColor = (Tank1Left == Idle ? ButtonColor : (Tank1Left == Hover ? ButtonHover : ButtonPress));
    Color Tank2LeftColor = (Tank2Left == Idle ? ButtonColor : (Tank2Left == Hover ? ButtonHover : ButtonPress));
    Color Tank3LeftColor = (Tank3Left == Idle ? ButtonColor : (Tank3Left == Hover ? ButtonHover : ButtonPress));
    Color Tank1RightColor = (Tank1Right == Idle ? ButtonColor : (Tank1Right == Hover ? ButtonHover : ButtonPress));
    Color Tank2RightColor = (Tank2Right == Idle ? ButtonColor : (Tank2Right == Hover ? ButtonHover : ButtonPress));
    Color Tank3RightColor = (Tank3Right == Idle ? ButtonColor : (Tank3Right == Hover ? ButtonHover : ButtonPress));
    Color SaveBtnColor = (SaveBtn == Idle ? ButtonColor : (SaveBtn == Hover ? ButtonHover : ButtonPress));
    thickLineRGBA(renderer, BUTTON_RIGHTMARGIN, 60, BUTTON_RIGHTMARGIN + 60, 60, 60, WinDecColor.red, WinDecColor.green, WinDecColor.blue, 255);
    thickLineRGBA(renderer, SCREEN_WIDTH - BUTTON_RIGHTMARGIN, 60, SCREEN_WIDTH - BUTTON_RIGHTMARGIN - 60, 60, 60, WinIncColor.red, WinIncColor.green, WinIncColor.blue, 255);
    thickLineRGBA(renderer, BUTTON_RIGHTMARGIN, 130, BUTTON_RIGHTMARGIN + 60, 130, 60, Tank1LeftColor.red, Tank1LeftColor.green, Tank1LeftColor.blue, 255);
    thickLineRGBA(renderer, SCREEN_WIDTH - BUTTON_RIGHTMARGIN, 130, SCREEN_WIDTH - BUTTON_RIGHTMARGIN - 60, 130, 60, Tank1RightColor.red, Tank1RightColor.green, Tank1RightColor.blue, 255);
    thickLineRGBA(renderer, BUTTON_RIGHTMARGIN, 200, BUTTON_RIGHTMARGIN + 60, 200, 60, Tank2LeftColor.red, Tank2LeftColor.green, Tank2LeftColor.blue, 255);
    thickLineRGBA(renderer, SCREEN_WIDTH - BUTTON_RIGHTMARGIN, 200, SCREEN_WIDTH - BUTTON_RIGHTMARGIN - 60, 200, 60, Tank2RightColor.red, Tank2RightColor.green, Tank2RightColor.blue, 255);
    thickLineRGBA(renderer, BUTTON_RIGHTMARGIN, 270, BUTTON_RIGHTMARGIN + 60, 270, 60, Tank3LeftColor.red, Tank3LeftColor.green, Tank3LeftColor.blue, 255);
    thickLineRGBA(renderer, SCREEN_WIDTH - BUTTON_RIGHTMARGIN, 270, SCREEN_WIDTH - BUTTON_RIGHTMARGIN - 60, 270, 60, Tank3RightColor.red, Tank3RightColor.green, Tank3RightColor.blue, 255);
    thickLineRGBA(renderer, BUTTON_RIGHTMARGIN, 340, SCREEN_WIDTH - BUTTON_RIGHTMARGIN, 340, 50, SaveBtnColor.red, SaveBtnColor.green, SaveBtnColor.blue, 255);

    char ScoreString[4];
    sprintf(ScoreString, "%d", WinScore);
    float Scale = 1.5;
    SDL_RenderSetScale(renderer, Scale, Scale);
    stringRGBA(renderer, (SCREEN_WIDTH / 2 - 4 * strlen(ScoreString)) / Scale, 60 / Scale, ScoreString, 0, 0, 0, 255);
    stringRGBA(renderer, (SCREEN_WIDTH / 2 - 50) / Scale, 40 / Scale, "Max Score", 0, 0, 0, 255);
    stringRGBA(renderer, (SCREEN_WIDTH / 2 - 24) / Scale, 334 / Scale, "Save", 0, 0, 0, 255);
    stringRGBA(renderer, (BUTTON_RIGHTMARGIN + 30 - 6) / Scale, 60 / Scale, "-", 0, 0, 0, 255);
    stringRGBA(renderer, (BUTTON_RIGHTMARGIN + 30 - 6) / Scale, 130 / Scale, "<", 0, 0, 0, 255);
    stringRGBA(renderer, (BUTTON_RIGHTMARGIN + 30 - 6) / Scale, 200 / Scale, "<", 0, 0, 0, 255);
    stringRGBA(renderer, (BUTTON_RIGHTMARGIN + 30 - 6) / Scale, 270 / Scale, "<", 0, 0, 0, 255);
    stringRGBA(renderer, (SCREEN_WIDTH - BUTTON_RIGHTMARGIN - 30 - 4) / Scale, 60 / Scale, "+", 0, 0, 0, 255);
    stringRGBA(renderer, (SCREEN_WIDTH - BUTTON_RIGHTMARGIN - 30 - 4) / Scale, 130 / Scale, ">", 0, 0, 0, 255);
    stringRGBA(renderer, (SCREEN_WIDTH - BUTTON_RIGHTMARGIN - 30 - 4) / Scale, 200 / Scale, ">", 0, 0, 0, 255);
    stringRGBA(renderer, (SCREEN_WIDTH - BUTTON_RIGHTMARGIN - 30 - 4) / Scale, 270 / Scale, ">", 0, 0, 0, 255);
    SDL_RenderSetScale(renderer, 1, 1);
    SDL_Rect tank1Rect = {SCREEN_WIDTH / 2 - 46, 105, 93, 51};
    SDL_Rect tank2Rect = {SCREEN_WIDTH / 2 - 46, 175, 93, 51};
    SDL_Rect tank3Rect = {SCREEN_WIDTH / 2 - 46, 245, 93, 51};
    SDL_RenderCopy(renderer, Textures[Tank1ColorIndex], NULL, &tank1Rect);
    SDL_RenderCopy(renderer, Textures[Tank2ColorIndex], NULL, &tank2Rect);
    SDL_RenderCopy(renderer, Textures[Tank3ColorIndex], NULL, &tank3Rect);

}

Action settingHandle() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return Exit;
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(x >= BUTTON_RIGHTMARGIN && x <= BUTTON_RIGHTMARGIN + 60) {
                if(y >= 30 && y <= 90)
                    winDec = Pressed;
                if(y >= 100 && y <= 160)
                    Tank1Left = Pressed;
                if(y >= 170 && y <= 230)
                    Tank2Left = Pressed;
                if(y >= 240 && y <= 300)
                    Tank3Left = Pressed;
            }
            if(x <= SCREEN_WIDTH - BUTTON_RIGHTMARGIN && x >= SCREEN_WIDTH - BUTTON_RIGHTMARGIN - 60) {
                if(y >= 30 && y <= 90)
                    winInc = Pressed;
                if(y >= 100 && y <= 160)
                    Tank1Right = Pressed;
                if(y >= 170 && y <= 230)
                    Tank2Right = Pressed;
                if(y >= 240 && y <= 300)
                    Tank3Right = Pressed;
            }
            if(x >= BUTTON_RIGHTMARGIN && x <= SCREEN_WIDTH - BUTTON_RIGHTMARGIN)
                if(y >= 315 && y <= 365)
                    SaveBtn = Pressed;
        }
        if(event.type == SDL_MOUSEBUTTONUP) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(x >= BUTTON_RIGHTMARGIN && x <= BUTTON_RIGHTMARGIN + 60) {
                if(y >= 30 && y <= 90)
                    if(winDec == Pressed) WinScore = maximum(WinScore - 1, 5);
                if(y >= 100 && y <= 160)
                    if(Tank1Left == Pressed) Tank1ColorIndex = (Tank1ColorIndex + TANK_COLOR_COUNT - 1) % TANK_COLOR_COUNT;
                if(y >= 170 && y <= 230)
                    if(Tank2Left == Pressed) Tank2ColorIndex = (Tank2ColorIndex + TANK_COLOR_COUNT - 1) % TANK_COLOR_COUNT;
                if(y >= 240 && y <= 300)
                    if(Tank3Left == Pressed) Tank3ColorIndex = (Tank3ColorIndex + TANK_COLOR_COUNT - 1) % TANK_COLOR_COUNT;
            }
            if(x <= SCREEN_WIDTH - BUTTON_RIGHTMARGIN && x >= SCREEN_WIDTH - BUTTON_RIGHTMARGIN - 60) {
                if(y >= 30 && y <= 90)
                    if(winInc == Pressed) WinScore++;
                if(y >= 100 && y <= 160)
                    if(Tank1Right == Pressed) Tank1ColorIndex = (Tank1ColorIndex + 1) % TANK_COLOR_COUNT;
                if(y >= 170 && y <= 230)
                    if(Tank2Right == Pressed) Tank2ColorIndex = (Tank2ColorIndex + 1) % TANK_COLOR_COUNT;
                if(y >= 240 && y <= 300)
                    if(Tank3Right == Pressed) Tank3ColorIndex = (Tank3ColorIndex + 1) % TANK_COLOR_COUNT;
            }
            if(x >= BUTTON_RIGHTMARGIN && x <= SCREEN_WIDTH - BUTTON_RIGHTMARGIN)
                if(y >= 315 && y <= 365)
                    return Save;
            winDec = Idle;
            winInc = Idle;
            Tank1Left = Idle;
            Tank1Right = Idle;
            Tank2Left = Idle;
            Tank2Right = Idle;
            Tank3Left = Idle;
            Tank3Right = Idle;
            SaveBtn = Idle;
        }
    }
    return None;
}

void LoadSetting(Manager *manager) {
    FILE *f = fopen("../alter_tank.conf", "r");
    fscanf(f, "%d", &WinScore);
    fscanf(f, "%d", &Tank1ColorIndex);
    fscanf(f, "%d", &Tank2ColorIndex);
    fscanf(f, "%d", &Tank3ColorIndex);
    fclose(f);


    winDec = Idle;
    winInc = Idle;
    Tank1Left = Idle;
    Tank1Right = Idle;
    Tank2Left = Idle;
    Tank2Right = Idle;
    Tank3Left = Idle;
    Tank3Right = Idle;
    SaveBtn = Idle;

    ButtonColor = COLOR_BUTTON;
    ButtonHover = COLOR_BUTTON_HOVER;
    ButtonPress = COLOR_BUTTON_PRESSED;

    TankColors[0] = COLOR_RED;
    TankColors[1] = COLOR_BLUE;
    TankColors[2] = COLOR_GREEN;
    TankColors[3] = COLOR_YELLOW;
    TankColors[4] = COLOR_ORANGE;
    TankColors[5] = COLOR_BROWN;

    Surfaces[0] = SDL_LoadBMP("../images/tank_red.bmp");
    Surfaces[1] = SDL_LoadBMP("../images/tank_blue.bmp");
    Surfaces[2] = SDL_LoadBMP("../images/tank_green.bmp");
    Surfaces[3] = SDL_LoadBMP("../images/tank_yellow.bmp");
    Surfaces[4] = SDL_LoadBMP("../images/tank_orange.bmp");
    Surfaces[5] = SDL_LoadBMP("../images/tank_brown.bmp");

    Textures[0] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[0]);
    Textures[1] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[1]);
    Textures[2] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[2]);
    Textures[3] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[3]);
    Textures[4] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[4]);
    Textures[5] = SDL_CreateTextureFromSurface(manager->renderer, Surfaces[5]);

    Action action;
    const double FPS = 100;
    while (true) {
        action = settingHandle(manager);
        if(action == Exit || action == Save)
            break;

        int start_ticks = SDL_GetTicks();

        SDL_SetRenderDrawColor(manager->renderer, 230, 230, 230, 255);
        SDL_RenderClear(manager->renderer);

        if(winDec != Pressed) winDec = Idle;
        if(winInc != Pressed) winInc = Idle;
        if(Tank1Left != Pressed) Tank1Left = Idle;
        if(Tank1Right != Pressed) Tank1Right = Idle;
        if(Tank2Left != Pressed) Tank2Left = Idle;
        if(Tank2Right != Pressed) Tank2Right = Idle;
        if(Tank3Left != Pressed) Tank3Left = Idle;
        if(Tank3Right != Pressed) Tank3Right = Idle;
        if(SaveBtn != Pressed) SaveBtn = Idle;
        // BUTTON HOVER CHECK
        int x, y;
        SDL_GetMouseState(&x, &y);
        if(x >= BUTTON_RIGHTMARGIN && x <= BUTTON_RIGHTMARGIN + 60) {
            if(y >= 30 && y <= 90)
                if(winDec != Pressed) winDec = Hover;
            if(y >= 100 && y <= 160)
                if(Tank1Left != Pressed) Tank1Left = Hover;
            if(y >= 170 && y <= 230)
                if(Tank2Left != Pressed) Tank2Left = Hover;
            if(y >= 240 && y <= 300)
                if(Tank3Left != Pressed) Tank3Left = Hover;
        }
        if(x <= SCREEN_WIDTH - BUTTON_RIGHTMARGIN && x >= SCREEN_WIDTH - BUTTON_RIGHTMARGIN - 60) {
            if(y >= 30 && y <= 90)
                if(winInc != Pressed) winInc = Hover;
            if(y >= 100 && y <= 160)
                if(Tank1Right != Pressed) Tank1Right = Hover;
            if(y >= 170 && y <= 230)
                if(Tank2Right != Pressed) Tank2Right = Hover;
            if(y >= 240 && y <= 300)
                if(Tank3Right != Pressed) Tank3Right = Hover;
        }
        if(x >= BUTTON_RIGHTMARGIN && x <= SCREEN_WIDTH - BUTTON_RIGHTMARGIN)
            if(y >= 315 && y <= 365)
                SaveBtn = Hover;

        DrawSetting(manager->renderer);

        SDL_RenderPresent(manager->renderer);

        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }
    if(action == Save) {
        f = fopen("../alter_tank.conf", "w");
        fprintf(f, "%d\n", WinScore);
        fprintf(f, "%d\n", Tank1ColorIndex);
        fprintf(f, "%d\n", Tank2ColorIndex);
        fprintf(f, "%d\n", Tank3ColorIndex);
        fclose(f);
    }

}