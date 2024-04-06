#pragma once

#include <SDL2/SDL.h>

#include "Data.hpp"
#include "Structure.hpp"
#include "ResourceManager.hpp"

class Tabs_Title{
    // public:
    //     LButton button[allButtonsOfMenu];
    //     LTexture keyUp[4], keyDown[4];
public:
    Tabs_Title();
    ~Tabs_Title();
    Tabs getDirect();
    void resetDirect();
    void handleEvents();
    void setUpMenu(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
    LButton button[2];
private:
    LTexture titleBackground;
    int totalButtons{2};
    Tabs direct{Title};
    int currentButton{0};
    TTF_Font* titleFont;
};