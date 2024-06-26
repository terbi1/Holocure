
#include "Tabs_Title.hpp"

Tabs_Title::Tabs_Title() {
}

Tabs_Title::~Tabs_Title() {
}

Tabs Tabs_Title::getDirect() {
    Tabs temp = direct;
    direct = Title;
    return temp;
}


void Tabs_Title::setUpMenu(SDL_Renderer* renderer) {
    titleFont = TTF_OpenFont(font_8bitPLus.c_str(),12);
    button[0] = LButton{"Play",Vector2f{825, 226}, Vector2f{250,52}, 0};
    button[1] = LButton{"Quit",Vector2f{825, 286}, Vector2f{250,52}, 0};
    button[0].setCurrentButton();
}

void Tabs_Title::render(SDL_Renderer* renderer) {
    ResourceManager::getInstance().PlayFrame(0,0,0,0,0);
    ResourceManager::getInstance().Draw(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    ResourceManager::getInstance().Render(BG_Title, renderer);
    ResourceManager::getInstance().Draw(600,20,615 / 3 * 2,259 / 3 * 2);
    ResourceManager::getInstance().Render("res/gfx/spr_HoloCureTitle_full.png", renderer);
    currentButton = (currentButton + totalButtons) % totalButtons;
    for(int i = 0; i < totalButtons; ++i)
    {
        if(i == currentButton) button[i].setCurrentButton();
        else button[i].notCurrentButton();
        button[i].render(renderer, titleFont);
    }
}

void Tabs_Title::handleEvents(bool &isRunning) {
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_KP_ENTER] || currentKeyStates[SDL_SCANCODE_Z])
    {
        if(button[0].getState()) {
            direct = Character_Select; 
        }
        else if(button[1].getState()) isRunning = false;
        SDL_ResetKeyboard();
        return;
    }
    else if (currentKeyStates[SDL_SCANCODE_UP])
    {
        ++currentButton;
    }
    else if(currentKeyStates[SDL_SCANCODE_DOWN])
    {
        --currentButton;
    }

    SDL_ResetKeyboard();
}
