#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>

#include "player.hpp"
#include "Data.hpp"
#include "Structure.hpp"
#include "ResourceManager.hpp"

struct HUD
{
    HUD();
    ~HUD();
    LTexture expBar[2];
    LTexture portrait;
    LTexture title;
    LTexture pauseScreen;
    LTexture pauseMenu;
    LTexture hp[2];
    SDL_Rect expBaseBar{0, 0, SCREEN_WIDTH, 34};
    SDL_Rect screen{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect expTopBarSRC{0, 0, 0, 26};
    SDL_FRect expTopBar{0, -3, 0, 34};
    SDL_Rect hpBaseBar{86,40,0,6 * 2};
    SDL_Rect hpTopBar{86,40,0,6 * 2};
    SDL_Rect pausePortrait{25, 100, 51 * 3, 115 * 3};
    std::stringstream levelText;
    std::stringstream timeText;
    std::string gameOverText {"GAME OVER"};
    void initHUD(SDL_Renderer *renderer, int health);
    void update(Player player, int expForNextLevel);
    void render(SDL_Renderer *renderer, bool pause, bool isOver);
    LTimer HUD_Timer;
    TTF_Font *HUD_font = NULL;
    Uint32 minute;
    Uint32 second;
    SDL_Rect portraitRectSRC{0, 0, 43, 24};
    SDL_Rect portraitRectDST{0, 40, 86, 48};
    SDL_Rect pauseRect{(int)(SCREEN_WIDTH / 2 - 128 * 1.5 / 2), (int)(SCREEN_HEIGHT / 2 - 245 * 1.5 / 2), (int)(128 * 1.5), (int)(245 * 1.5)};
    SDL_Rect overRect{SCREEN_WIDTH / 2 - 150, 100, 300, 50};
    LTexture textureText;
    int totalButtons{2};
    LButton button[2];
    int currentButton{0};
    void handleEvents(bool &isRunning, Tabs& direct);
};