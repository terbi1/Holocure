#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>

#include "Data.hpp"
#include "Structure.hpp"
#include "math.hpp"
#include "ResourceManager.hpp"

class Tabs_Room1
{
public:
    Tabs_Room1();
    ~Tabs_Room1();
    Tabs getDirect();
    void resetDirect();
    void handleEvents();
    void roomInit(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer, Vector2f player_pos, bool shake);
private:
    LTexture roomBackground;
    Tabs direct{Room1};
};