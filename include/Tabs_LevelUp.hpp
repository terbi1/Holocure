#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Data.hpp"
#include "Structure.hpp"
#include "ResourceManager.hpp"
#include "weapon.hpp"

struct Tabs_LevelUp
{
    Tabs_LevelUp();
    ~Tabs_LevelUp();
    Tabs direct = Level_Up;
    Tabs getDirect();
    void setUp(SDL_Renderer* renderer);
    LButton upgrade[4];
    LTexture optionCase;
    LTexture icon[4];
    std::string iconTexture[4];
    void getIcon();
    int currentButton{0};
    void render(SDL_Renderer* renderer);
    void handleEvents(bool &leveledUp,int &choice);
};