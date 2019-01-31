#include "setting.h"
#include "colors.h"

Color ButtonColor, ButtonHover, ButtonPress;
ButtonState winDec, winInc, Tank1Left, Tank2Left, Tank3Left, Tank1Right, Tank2Right, Tank3Right;
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
    thickLineRGBA(renderer, BUTTON_RIGHTMARGIN, 60, BUTTON_RIGHTMARGIN + 60, 60, 60, WinDecColor.red, WinDecColor.green, WinDecColor.blue, 255);
    thickLineRGBA(renderer, SCREEN_WIDTH - BUTTON_RIGHTMARGIN, 60, SCREEN_WIDTH - BUTTON_RIGHTMARGIN - 60, 60, 60, WinIncColor.red, WinIncColor.green, WinIncColor.blue, 255);
    thickLineRGBA(renderer, BUTTON_RIGHTMARGIN, 130, BUTTON_RIGHTMARGIN + 60, 130, 60, Tank1LeftColor.red, Tank1LeftColor.green, Tank1LeftColor.blue, 255);
    thickLineRGBA(renderer, SCREEN_WIDTH - BUTTON_RIGHTMARGIN, 130, SCREEN_WIDTH - BUTTON_RIGHTMARGIN - 60, 130, 60, Tank1RightColor.red, Tank1RightColor.green, Tank1RightColor.blue, 255);
    thickLineRGBA(renderer, BUTTON_RIGHTMARGIN, 200, BUTTON_RIGHTMARGIN + 60, 200, 60, Tank2LeftColor.red, Tank2LeftColor.green, Tank2LeftColor.blue, 255);
    thickLineRGBA(renderer, SCREEN_WIDTH - BUTTON_RIGHTMARGIN, 200, SCREEN_WIDTH - BUTTON_RIGHTMARGIN - 60, 200, 60, Tank2RightColor.red, Tank2RightColor.green, Tank2RightColor.blue, 255);
    thickLineRGBA(renderer, BUTTON_RIGHTMARGIN, 270, BUTTON_RIGHTMARGIN + 60, 270, 60, Tank3LeftColor.red, Tank3LeftColor.green, Tank3LeftColor.blue, 255);
    thickLineRGBA(renderer, SCREEN_WIDTH - BUTTON_RIGHTMARGIN, 270, SCREEN_WIDTH - BUTTON_RIGHTMARGIN - 60, 270, 60, Tank3RightColor.red, Tank3RightColor.green, Tank3RightColor.blue, 255);
    char ScoreString[4];
    sprintf(ScoreString, "%d", WinScore);
    stringRGBA(renderer, SCREEN_WIDTH / 2 - 4 * strlen(ScoreString), 60, ScoreString, 0, 0, 0, 255);
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
        }
        if(event.type == SDL_MOUSEBUTTONUP) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(x >= BUTTON_RIGHTMARGIN && x <= BUTTON_RIGHTMARGIN + 60) {
                if(y >= 30 && y <= 90)
                    if(winDec == Pressed) WinScore = maximum(WinScore - 1, 5);
                if(y >= 100 && y <= 160)
                    if(Tank1Left == Pressed) Tank1Left = Hover;
                if(y >= 170 && y <= 230)
                    if(Tank2Left == Pressed) Tank2Left = Hover;
                if(y >= 240 && y <= 300)
                    if(Tank3Left == Pressed) Tank3Left = Hover;
            }
            if(x <= SCREEN_WIDTH - BUTTON_RIGHTMARGIN && x >= SCREEN_WIDTH - BUTTON_RIGHTMARGIN - 60) {
                if(y >= 30 && y <= 90)
                    if(winInc == Pressed) WinScore++;
                if(y >= 100 && y <= 160)
                    if(Tank1Right == Pressed) Tank1Right = Hover;
                if(y >= 170 && y <= 230)
                    if(Tank2Right == Pressed) Tank2Right = Hover;
                if(y >= 240 && y <= 300)
                    if(Tank3Right == Pressed) Tank3Right = Hover;
            }
            winDec = Idle;
            winInc = Idle;
            Tank1Left = Idle;
            Tank1Right = Idle;
            Tank2Left = Idle;
            Tank2Right = Idle;
            Tank3Left = Idle;
            Tank3Right = Idle;
        }
    }
    return None;
}

void LoadSetting(Manager *manager) {
    WinScore = 10;

    winDec = Idle;
    winInc = Idle;
    Tank1Left = Idle;
    Tank1Right = Idle;
    Tank2Left = Idle;
    Tank2Right = Idle;
    Tank3Left = Idle;
    Tank3Right = Idle;
    ButtonColor = COLOR_BUTTON;
    ButtonHover = COLOR_BUTTON_HOVER;
    ButtonPress = COLOR_BUTTON_PRESSED;

    Action action;
    const double FPS = 100;
    while (true) {
        action = settingHandle(manager);
        if(action == Exit)
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

        DrawSetting(manager->renderer);

        SDL_RenderPresent(manager->renderer);

        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }

}