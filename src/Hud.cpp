
#include "Hud.hpp"

HUD::HUD()
{
}

HUD::~HUD()
{
}

void HUD::initHUD(SDL_Renderer* renderer, int health) 
{
    HUD_font = TTF_OpenFont(font_8bitPLus.c_str(),12);
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
}

void HUD::update(Player player, int reqNextLevel)
{
    hpTopBar.w = player.health * 4;
    expTopBarSRC.w = player.currentExp / reqNextLevel * 648;
    expTopBar.w = player.currentExp / reqNextLevel * (SCREEN_WIDTH + 10);
    levelText.str("");
    levelText << "LV: "<< player.LEVEL;
    timeText.str("");
    minute = HUD_Timer.getTicks(Minute);
    second = HUD_Timer.getTicks(Second) - minute * 60;
    if (minute < 10) timeText << 0;
    timeText << minute << ":";
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
    }
    else if(isOver)
    {
        pauseScreen.render(renderer, &screen);
        textureText.loadFromRenderedText(gameOverText.c_str(),{255,255,255},HUD_font, renderer);
        textureText.render(renderer, &overRect);  
    }

    expBar[0].render(renderer, &expBaseBar);
    expBar[1].renderF(renderer, &expTopBar, &expTopBarSRC);

    portrait.render(renderer, &portraitRectDST, &portraitRectSRC);

    hp[0].render(renderer, &hpBaseBar);
    hp[1].render(renderer, &hpTopBar);

    textureText.loadFromRenderedText(levelText.str().c_str(),{255,255,255},HUD_font, renderer);
    textureText.render(renderer, &levelRect);

    textureText.loadFromRenderedText(timeText.str().c_str(),{255,255,255},HUD_font, renderer);
    textureText.render(renderer, &timeRect);  
}
