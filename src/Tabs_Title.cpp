
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
}

void Tabs_Title::render(SDL_Renderer* renderer) {
    SDL_Rect renderQuad {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
    titleBackground.render(renderer, &renderQuad);
}

void Tabs_Title::handleEvents() {
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_KP_ENTER])
    {
        direct = Room1;
        return;
    }
    direct = Title;    
}
