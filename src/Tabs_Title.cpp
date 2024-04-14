
#include "Tabs_Title.hpp"

Tabs_Title::Tabs_Title() {
}

Tabs_Title::~Tabs_Title() {
}

Tabs Tabs_Title::getDirect() {
    return direct;
}


void Tabs_Title::setUpMenu(SDL_Renderer* renderer) {
    titleFont = TTF_OpenFont(font_8bitPLus.c_str(),12);
    titleBackground.loadFromFile(Black_Screen, renderer);
    // button[1] = LButton{"Quit",SDL_Rect{700,260,250,52}};
    // button[0] = LButton{"Play",SDL_Rect{700,200,250,52}};
    button[0] = LButton{"Play",Vector2f{825, 226}, Vector2f{250,52}, 0};
    button[1] = LButton{"Quit",Vector2f{825, 286}, Vector2f{250,52}, 0};
    button[0].setCurrentButton();
}

void Tabs_Title::render(SDL_Renderer* renderer) {
    SDL_Rect renderQuad {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
    titleBackground.render(renderer, &renderQuad);

    currentButton = (currentButton + totalButtons) % totalButtons;
    for(int i = 0; i < totalButtons; ++i)
    {
        if(i == currentButton) button[i].setCurrentButton();
        else button[i].notCurrentButton();
        button[i].render(renderer, titleFont);
    }
    // button[0].render(renderer, titleFont);
    // button[1].render(renderer, titleFont);
}

void Tabs_Title::handleEvents(bool &isRunning) {
    direct = Title;    
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_KP_ENTER] || currentKeyStates[SDL_SCANCODE_Z])
    {
        if(button[0].getState()) {
            direct = Room1; 
            
            Mix_HaltMusic();
        }
        else if(button[1].getState()) isRunning = false;

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
