#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Data.hpp"
#include "Structure.hpp"
#include "ResourceManager.hpp"

struct Tabs_End
{
    Tabs_End();
    ~Tabs_End();
    Tabs direct = End;
    Tabs getDirect();
    void setUp(SDL_Renderer* renderer);
    LButton button[2];
    std::string announcement;
    LTexture textureText;
    int currentButton{0};
    void update(bool isOver);
    void render(SDL_Renderer* renderer, TTF_Font* font);
    void handleEvents();
};