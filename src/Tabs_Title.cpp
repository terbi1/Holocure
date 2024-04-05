
#include "Tabs_Title.hpp"

Tabs_Title::Tabs_Title() {
}

Tabs_Title::~Tabs_Title() {
}

Tabs Tabs_Title::getDirect() {
    return direct;
}


void Tabs_Title::setUpMenu(SDL_Renderer* renderer) {
    titleBackground.loadFromFile(BG_Title, renderer);
    button[0] = LButton{"Play",SDL_Rect{700,200,250,52}};
    button[1] = LButton{"Quit",SDL_Rect{700,260,250,52}};
    button[0].setCurrentButton();
}

void Tabs_Title::render(SDL_Renderer* renderer) {
    currentButton = abs(currentButton % totalButtons);
    for(int i = 0; i < totalButtons; ++i)
    {
        if(i == currentButton) button[i].setCurrentButton();
        else button[i].notCurrentButton();
    }
    SDL_Rect renderQuad {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
    titleBackground.render(renderer, &renderQuad);
    button[0].render(renderer);
    button[1].render(renderer);
}

void Tabs_Title::handleEvents() {
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_KP_ENTER])
    {
        direct = Room1;
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
    direct = Title;    
}
