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
    void update();
    void handleEvents(Character &player);
    void setUp(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer, TTF_Font* font);
    LButton character[2];
private:
    LTexture textTexture;
    SDL_Rect panels[3]{{20,100,300,450}, {700,100,300,200}, {700,300,300,250}};
    SDL_Rect labels[3]{{20,100,300,40}, {700,100,300,40}, {700,300,300,40}};
    std::string labelTexts[3]{Player_Name[0], "ATTACK", "SPECIAL"};
    std::string icons[2]{WeaponIcon[0], SpecialIcon[0]};
    std::string descriptions[2]{Weapon_Description[0],Special_Description[0]};
    std::string characterIcon[2]{Portrait_Suisei, Portrait_Risu};
    int totalCharacter{2};
    Tabs direct{Character_Select};
    int currentCharacter{0};
    TTF_Font* titleFont;
    Mix_Music* gMusic;
};