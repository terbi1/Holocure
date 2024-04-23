
#include "Tabs_CharacterSelect.hpp"

Tabs_CharacterSelect::Tabs_CharacterSelect() {
}

Tabs_CharacterSelect::~Tabs_CharacterSelect() {
}

Tabs Tabs_CharacterSelect::getDirect() {
    Tabs temp = direct;
    direct = Character_Select;
    return temp;
}


void Tabs_CharacterSelect::setUp(SDL_Renderer* renderer) {
    // CharacterSelectFont = TTF_OpenFont(font_8bitPLus.c_str(),12);
    character[0] = LButton{"",Vector2f{825, 226}, Vector2f{86, 76}, 2};
    character[1] = LButton{"",Vector2f{915, 226}, Vector2f{86, 76}, 2};
    character[0].setCurrentButton();
}

void Tabs_CharacterSelect::render(SDL_Renderer* renderer) {
    ResourceManager::getInstance().PlayFrame(0,0,0,0,0);
    ResourceManager::getInstance().Draw(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    ResourceManager::getInstance().Render("res/gfx/menu_charselecBG.png", renderer);
    currentCharacter = (currentCharacter + totalCharacter) % totalCharacter;
    for(int i = 0; i < totalCharacter; ++i)
    {
        ResourceManager::getInstance().Draw(character[i].getCenter().x - 43 , character[i].getCenter().y - 38, 86, 76);
        ResourceManager::getInstance().Render(characterIcon[i], renderer);
        if(i == currentCharacter) character[i].setCurrentButton();
        else character[i].notCurrentButton();
        character[i].render(renderer, NULL);
    }
}

void Tabs_CharacterSelect::handleEvents(Character &player) {
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_KP_ENTER] || currentKeyStates[SDL_SCANCODE_Z])
    {
        for(int i = 0; i < totalCharacter; ++i)
        {
            if(character[i].getState()) {
                player = (Character)i;
            }
        }
        direct = Room1;      
        return;
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        ++currentCharacter;
    }
    else if(currentKeyStates[SDL_SCANCODE_LEFT])
    {
        --currentCharacter;
    }

    SDL_ResetKeyboard();
}
