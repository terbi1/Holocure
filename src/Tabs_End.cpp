#include "Tabs_End.hpp"

Tabs_End::Tabs_End()
{
    
}

Tabs_End::~Tabs_End()
{

}

Tabs Tabs_End::getDirect() {
    Tabs temp = direct;
    direct = End;
    return temp;
}

void Tabs_End::setUp(SDL_Renderer* renderer)
{
    button[0] = LButton{"", Vector2f{SCREEN_WIDTH / 2, 340}, Vector2f{250,52}, 0};
    button[1] = LButton{"Main Menu", Vector2f{SCREEN_WIDTH / 2, 400}, Vector2f{250,52}, 0};
    button[0].setCurrentButton();
}

void Tabs_End::update(bool isOver)
{
    button[0].setText((isOver ? "Retry":"Play Again"));
    announcement = (isOver ? "Game Over":"You Win!");
}

void Tabs_End::handleEvents()
{
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_KP_ENTER])
    {
        if(button[0].getState()) direct = Room1;
        else if(button[1].getState()) direct = Title;
        currentButton = 0;
        SDL_ResetKeyboard();
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

void Tabs_End::render(SDL_Renderer* renderer, TTF_Font* font)
{
    textureText.renderText(announcement.c_str(), {255, 255, 255}, font, renderer, SCREEN_WIDTH / 2 - 130, 150, 48);
    currentButton = (currentButton + 2) % 2;
    for(int i = 0; i < 2; ++i)
    {
        if(i == currentButton) button[i].setCurrentButton();
        else button[i].notCurrentButton();
        button[i].render(renderer, font);
    }
}