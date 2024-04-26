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
    void update(float timeStep);
    void handleEvents(Character &player);
    void setUp(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer, TTF_Font* font);
    LButton character[3];
private:
    LTexture textTexture;
    SDL_Rect panels[3]{{20,100,300,450}, {700,100,300,200}, {700,300,300,250}};
    SDL_Rect labels[3]{{20,100,300,40}, {700,100,300,40}, {700,300,300,40}};
    std::string labelTexts[3]{Player_Name[0], "ATTACK", "SPECIAL"};
    std::string icons[2]{WeaponIcon[0], SpecialIcon[0]};
    std::string uniqueAttackName[2]{Weapon_Name[0], Special_Name[0]};
    std::string descriptions[2]{Weapon_Description[0],Special_Description[0]};
    std::string characterIcon[3]{Portrait_Suisei, Portrait_Risu, Portrait_Ayame};
    int totalCharacter{3}; 
    int currentFrame{0};
    float timePassed{0.2};
    Tabs direct{Character_Select};
    int currentCharacter{0};
    TTF_Font* titleFont;
    Mix_Music* gMusic;
};