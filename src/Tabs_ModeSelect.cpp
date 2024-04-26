
#include "Tabs_ModeSelect.hpp"

Tabs_ModeSelect::Tabs_ModeSelect()
{
}

Tabs_ModeSelect::~Tabs_ModeSelect()
{
}

Tabs Tabs_ModeSelect::getDirect()
{
    Tabs temp = direct;
    direct = Mode_Select;
    return temp;
}

void Tabs_ModeSelect::update(float timeStep)
{
}

void Tabs_ModeSelect::setUp(SDL_Renderer *renderer)
{
    mode[0] = LButton{"", Vector2f{300, 226}, Vector2f{400, 200}, 1};
    mode[1] = LButton{"", Vector2f{750, 226}, Vector2f{400, 200}, 1};
    mode[0].setCurrentButton();
}

void Tabs_ModeSelect::render(SDL_Renderer *renderer, TTF_Font *font)
{
    ResourceManager::getInstance().PlayFrame(0, 0, 0, 0, 0);
    ResourceManager::getInstance().Draw(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    ResourceManager::getInstance().Render("res/gfx/menu_charselecBG.png", renderer);


    currentMode= (currentMode + 2) % 2;
    for (int i = 0; i < 2; ++i)
    {
        if (i == currentMode)
            mode[i].setCurrentButton();
        else
            mode[i].notCurrentButton();
        mode[i].render(renderer);
    }

    textTexture.renderText(modeName[0], {255,255,255}, font, renderer, 200,136,30,350);
    textTexture.renderText(modeName[1], {255,255,255}, font, renderer, 650,136,30,350);
    textTexture.renderText(modeDescriptions[0], {255,255,255}, font, renderer, 130,200,30,350);
    textTexture.renderText(modeDescriptions[1], {255,255,255}, font, renderer, 580,200,30,350);
}

void Tabs_ModeSelect::handleEvents(bool &endless)
{
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_KP_ENTER] || currentKeyStates[SDL_SCANCODE_Z])
    {
        if(mode[1].getState()) endless = true;
        direct = Room1;
        Mix_HaltMusic();
        SDL_ResetKeyboard();
        return;
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        ++currentMode;
    }
    else if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        --currentMode;
    }

    SDL_ResetKeyboard();
}
