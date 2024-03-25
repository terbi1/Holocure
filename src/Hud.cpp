
#include "Hud.hpp"

HUD::HUD()
{
}

HUD::~HUD()
{
}

void HUD::initHUD(SDL_Renderer* renderer) 
{
    HUD_font = TTF_OpenFont(font_8bitPLus.c_str(),12);
    expBar[0].loadFromFile(HUD_expBarBase, renderer);
    expBar[1].loadFromFile(HUD_expBarTop, renderer);
    portrait.loadFromFile(Portrait_Suisei, renderer);
}

void HUD::update(Player player, int reqNextLevel)
{
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

void HUD::render(SDL_Renderer* renderer) 
{
    expBar[0].render(renderer, &expBaseBar);
    expBar[1].renderF(renderer, &expTopBar, &expTopBarSRC);

    portrait.render(renderer, &portraitRectDST, &portraitRectSRC);

    textureText.loadFromRenderedText(levelText.str().c_str(),{255,255,255},HUD_font, renderer);
    textureText.render(renderer, &levelRect);

    textureText.loadFromRenderedText(timeText.str().c_str(),{255,255,255},HUD_font, renderer);
    textureText.render(renderer, &timeRect);  
}
