#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>

#include "player.hpp"
#include "Data.hpp"
#include "Structure.hpp"

struct HUD 
{
    HUD();
    ~HUD();
    LTexture expBar[2];
    LTexture portrait;
    SDL_Rect expBaseBar{0,0,SCREEN_WIDTH,34};
    SDL_Rect expTopBarSRC{0,0,0,26};
    SDL_FRect expTopBar{0,-3,0,34};
    std::stringstream levelText;
    std::stringstream timeText;
    void initHUD(SDL_Renderer* renderer);
    void update(Player player, int expForNextLevel);
    void render(SDL_Renderer* renderer);
    LTimer HUD_Timer;
    TTF_Font* HUD_font = NULL;
    Uint32 minute;
    Uint32 second;
    SDL_Rect portraitRectSRC {0, 0, 43,24};
    SDL_Rect portraitRectDST {0, 40, 86,48};
    SDL_Rect levelRect{940, 5, 75, 25};
    SDL_Rect timeRect{SCREEN_WIDTH / 2 - 50,50,100, 25};
    LTexture textureText;
};