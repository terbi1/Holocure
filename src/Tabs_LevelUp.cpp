#include "Tabs_LevelUp.hpp"

Tabs_LevelUp::Tabs_LevelUp()
{
    
}

Tabs_LevelUp::~Tabs_LevelUp()
{

}

Tabs Tabs_LevelUp::getDirect() {
    return direct;
}

void Tabs_LevelUp::setUp(SDL_Renderer* renderer)
{
    optionCase.loadFromFile(OptionCase, renderer);
    upgrade[0] = LButton{"",Vector2f{600, 150}, Vector2f{700,100}, 1};
    upgrade[1] = LButton{"",Vector2f{600, 260}, Vector2f{700,100}, 1};
    upgrade[2] = LButton{"",Vector2f{600, 370}, Vector2f{700,100}, 1};
    upgrade[3] = LButton{"",Vector2f{600, 480}, Vector2f{700,100}, 1};
    upgrade[0].setCurrentButton();
}

void Tabs_LevelUp::handleEvents(bool &leveledUp, int &choice)
{
    // direct = Level_Up;
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_KP_ENTER])
    {
        for(int i = 0; i < 4; ++i)
        {
            if(upgrade[i].getState()) 
            {
                choice = i;
                break;
            }
        }
        leveledUp = false;
        return;
    }
    else if (currentKeyStates[SDL_SCANCODE_UP])
    {
        --currentButton;
    }
    else if(currentKeyStates[SDL_SCANCODE_DOWN])
    {
        ++currentButton;
    }
    SDL_ResetKeyboard();

}

void Tabs_LevelUp::render(SDL_Renderer* renderer, TTF_Font* font)
{
    SDL_Rect caseRect{275, 20, 64, 64};
    SDL_Rect iconRect{282, 32, 50, 40};
    currentButton = (currentButton + 4) % 4;
    for(int i = 0; i < 4; ++i)
    {
        if(i == currentButton) upgrade[i].setCurrentButton();
        else upgrade[i].notCurrentButton();
        upgrade[i].render(renderer, font);
        caseRect.y += 110;
        iconRect.y += 110;
        optionCase.render(renderer, &caseRect);
        SDL_RenderCopy(renderer, ResourceManager::getInstance().getTexture(iconTexture[i], renderer), NULL, &iconRect);
    }
    for(int i = 0; i < 4; ++i)
    {
        textureText.renderText(optionName[i], {255,255,255}, font, renderer, 260, 105 + 110 * i,20);
    }
}