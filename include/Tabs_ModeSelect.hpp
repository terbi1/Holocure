#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "Data.hpp"
#include "Structure.hpp"
#include "ResourceManager.hpp"

class Tabs_ModeSelect{
public:
    Tabs_ModeSelect();
    ~Tabs_ModeSelect();
    Tabs getDirect();
    void update(float timeStep);
    void handleEvents(bool &endless);
    void setUp(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer, TTF_Font* font);
    LButton mode[2];
private:
    LTexture textTexture;
    std::string modeName[2]{"STAGE MODE", "ENDLESS MODE"};
    std::string modeDescriptions[2]{"Defeat the last boss to complete the stage!", "Survive for as long as you can!"};
    Tabs direct{Mode_Select};
    int currentMode{0};
};