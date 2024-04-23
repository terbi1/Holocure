#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "Data.hpp"
#include "Structure.hpp"
#include "ResourceManager.hpp"

class Tabs_CharacterSelect{
public:
    Tabs_CharacterSelect();
    ~Tabs_CharacterSelect();
    Tabs getDirect();
    void handleEvents(Character &player);
    void setUp(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
    LButton character[2];
private:
    std::string characterIcon[2]{Portrait_Suisei, Portrait_Risu};
    int totalCharacter{2};
    Tabs direct{Character_Select};
    int currentCharacter{0};
    TTF_Font* titleFont;
    Mix_Music* gMusic;
};