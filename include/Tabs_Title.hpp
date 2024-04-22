#pragma once

#include <SDL2/SDL.h>

#include "Data.hpp"
#include "Structure.hpp"
#include "ResourceManager.hpp"

class Tabs_Title{
public:
    Tabs_Title();
    ~Tabs_Title();
    Tabs getDirect();
    void resetDirect();
    void handleEvents(bool &isRunning);
    void setUpMenu(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
    LButton button[2];
private:
    int totalButtons{2};
    Tabs direct{Title};
    int currentButton{0};
    TTF_Font* titleFont;
    Mix_Music* gMusic;
};