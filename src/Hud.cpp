
#include "Hud.hpp"

HUD::HUD()
{
}

HUD::~HUD()
{
}

void HUD::initHUD(SDL_Renderer* renderer, int health) 
{
    HUD_font = TTF_OpenFont(font_8bitPLus.c_str(),28);
    expBar[0].loadFromFile(HUD_expBarBase, renderer);
    expBar[1].loadFromFile(HUD_expBarTop, renderer);
    portrait.loadFromFile(Portrait_Suisei, renderer);
    portrait.loadFromFile(Portrait_Suisei, renderer);
    pauseScreen.loadFromFile(Black_Screen, renderer);
    pauseScreen.setAlpha(100);
    title.loadFromFile(Title_Suisei, renderer);
    title.setAlpha(200);
    pauseMenu.loadFromFile(Pause_Menu, renderer);
    hp[0].loadFromFile(HealthBar[0], renderer);
    hpBaseBar.w = health * 4;
    hp[1].loadFromFile(HealthBar[1], renderer);
    button[0] = {"Resume", Vector2f{SCREEN_WIDTH / 2, 200}, Vector2f{125,35}};
    button[1] = {"Quit", Vector2f{SCREEN_WIDTH / 2, 240}, Vector2f{125,35}};
}

void HUD::update(Player player, int reqNextLevel)
{
    hpTopBar.w = player.health * 4;
    expTopBarSRC.w = player.currentExp / reqNextLevel * 648;
    expTopBar.w = player.currentExp / reqNextLevel * (SCREEN_WIDTH + 10);
    levelText.str("");
    levelText << "LV:"<< player.LEVEL;
    timeText.str("");
    minute = HUD_Timer.getTicks(Minute);
    second = HUD_Timer.getTicks(Second) - minute * 60;
    if (minute < 10) timeText << 0;
    timeText << minute << " : ";
    if (second < 10) timeText << 0;
    timeText << second;

}

void HUD::render(SDL_Renderer* renderer, bool pause, bool isOver) 
{
    if(pause) 
    {
        pauseScreen.render(renderer, &screen);
        title.render(renderer, &pausePortrait);
        pauseMenu.render(renderer, &pauseRect);
        currentButton = abs(currentButton % totalButtons);
        for(int i = 0; i < totalButtons; ++i)
        {
            if(i == currentButton) button[i].setCurrentButton();
            else button[i].notCurrentButton();
        }
        for(int i = 0; i < totalButtons; ++i)
        {
            button[i].render(renderer,HUD_font);
        }
    }
    else if(isOver)
    {
        pauseScreen.render(renderer, &screen);
        textureText.renderText(gameOverText.c_str(), {255,255,255}, HUD_font, renderer, SCREEN_WIDTH / 2 - 130, 100, 48);
    }

    expBar[0].render(renderer, &expBaseBar);
    expBar[1].renderF(renderer, &expTopBar, &expTopBarSRC);

    portrait.render(renderer, &portraitRectDST, &portraitRectSRC);

    hp[0].render(renderer, &hpBaseBar);
    hp[1].render(renderer, &hpTopBar);

    textureText.renderText(levelText.str().c_str(), {255,255,255}, HUD_font, renderer, 940, 10, 28);
    textureText.renderText(timeText.str().c_str(), {255,255,255}, HUD_font, renderer, SCREEN_WIDTH / 2 - 70, 50, 36);
}

void HUD::handleEvents(bool &pause, Tabs& direct) {
    direct = Room1;    
    if(!pause) return;

    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_KP_ENTER] || currentKeyStates[SDL_SCANCODE_Z])
    {
        if(button[0].getState()) pause = false;
        else if(button[1].getState()) {direct = Title; pause = false;}
        currentButton = 0;
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