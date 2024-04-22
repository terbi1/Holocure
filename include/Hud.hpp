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
#include "Tabs_LevelUp.hpp"
#include "weapon.hpp"

struct HUD
{
    HUD();
    ~HUD();
    LTexture expBar[2];
    LTexture hp[2];
    LTexture specialSymbol;
    LTexture specialBar[4];
    LTexture weaponSlot;
    SDL_Rect screen{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect expBaseBar{0, 0, SCREEN_WIDTH, 34};
    SDL_Rect expTopBar[2]{{0, 0, 0, 26}, {0, -3, 0, 34}};
    SDL_Rect hpBaseBar{86,40,0,6 * 2};
    SDL_Rect hpTopBar{86,40,0,6 * 2};
    SDL_Rect specialCase{0, 100, 18 * 2, 18 * 2};
    SDL_Rect specialBaseBar{40, 106, 70 * 2, 11 * 2};
    SDL_Rect specialTopBar[2]{{0, 0, 0, 11}, {40, 106, 0, 11 * 2}};
    SDL_Rect specialBarFrame{38,106,144,24};
    SDL_Rect pausePortrait{25, 130, 51 * 3, 115 * 3};
    SDL_FRect weaponRect{52.5f, 55, 25 * 1.5, 20 * 1.5};
    std::stringstream levelText;
    std::stringstream timeText;
    std::string hpText;
    std::string gameOverText {"GAME OVER"};
    void initHUD(SDL_Renderer *renderer, int health);
    void update(Player player, int expForNextLevel, float specialCD);
    void render(SDL_Renderer *renderer, bool pause, bool leveledUp, bool isOver, const std::vector<Weapon>& weapons);
    LTimer HUD_Timer;
    TTF_Font *HUD_font = NULL;
    Uint32 minute;
    Uint32 second;
    SDL_Rect portraitRectSRC{0, 0, 43, 24};
    SDL_Rect portraitRectDST{0, 40, 86, 48};
    SDL_Rect pauseRect{(int)(SCREEN_WIDTH / 2 - 128 * 1.5 / 2), (int)(SCREEN_HEIGHT / 2 - 245 * 1.5 / 2), (int)(128 * 1.5), (int)(245 * 1.5)};
    // SDL_Rect overRect{SCREEN_WIDTH / 2 - 150, 100, 300, 50};
    SDL_FRect levelLabel{0,88, 32, 11};
    LTexture textureText;
    int totalButtons{2};
    LButton button[2];
    int currentButton{0};
    int count{0};
    void handleEvents(bool &isRunning, bool &leveledUp, Tabs& direct, int &choice);
    Tabs_LevelUp tabs_levelup;
};