
#include "Hud.hpp"

HUD::HUD()
{
}

HUD::~HUD()
{
}

void HUD::initHUD(SDL_Renderer *renderer, int health)
{
    tabs_levelup.setUp(renderer);
    HUD_font = TTF_OpenFont(font_8bitPLus.c_str(), 28);
    specialBar[0].loadFromFile(Special_Bar[0], renderer);
    specialBar[1].loadFromFile(Special_Bar[1], renderer);
    specialBar[2].loadFromFile(Special_Bar[2], renderer);
    specialBar[3].loadFromFile(Special_Bar[3], renderer);
    specialSymbol.loadFromFile(SuiseiSpecial, renderer);
    weaponSlot.loadFromFile(EmptyWeaponSlot, renderer);
    weaponSlot.setAlpha(100);
    SDL_SetTextureAlphaMod(ResourceManager::getInstance().getTexture(Black_Screen, renderer),100);
    SDL_SetTextureAlphaMod(ResourceManager::getInstance().getTexture(Title_Suisei, renderer), 100);
    hp[0].loadFromFile(HealthBar[0], renderer);
    hpBaseBar.w = 230;
    hp[1].loadFromFile(HealthBar[1], renderer);
    button[0] = {"Resume", Vector2f{SCREEN_WIDTH / 2, 200}, Vector2f{125, 35}, 0};
    button[1] = {"Quit", Vector2f{SCREEN_WIDTH / 2, 240}, Vector2f{125, 35}, 0};
}

void HUD::update(Player player, int reqNextLevel, float specialCD)
{
    if(specialCD <= 0) ++count;
    hpTopBar.w = (float)player.health / (float)player.maxHP * 230;
    expTopBar[0].w = player.currentExp / reqNextLevel * 648;
    expTopBar[1].w = player.currentExp / reqNextLevel * (SCREEN_WIDTH + 10);
    specialTopBar[0].w = (player.specialCD - specialCD) / player.specialCD * 70;
    specialTopBar[1].w = (player.specialCD - specialCD) / player.specialCD * 140;
    levelText.str("");
    levelText << "LV:" << player.LEVEL;
    timeText.str("");
    minute = HUD_Timer.getTicks(Minute);
    second = HUD_Timer.getTicks(Second) - minute * 60;
    if (minute < 10)
        timeText << 0;
    timeText << minute << " : ";
    if (second < 10)
        timeText << 0;
    timeText << second;
    hpText = std::to_string(player.health) + "/" + std::to_string(player.maxHP);
}

void HUD::render(SDL_Renderer *renderer, bool pause, bool leveledUp, bool isOver, const std::vector<Weapon>& weapons)
{
    ResourceManager::getInstance().PlayFrame(0,0,0,0,0);
    if (pause)
    {
        ResourceManager::getInstance().PlayFrame(0,0,0,0,0);
        ResourceManager::getInstance().Draw(screen.x, screen.y, screen.w, screen.h);
        ResourceManager::getInstance().Render(Black_Screen, renderer);

        ResourceManager::getInstance().Draw(pausePortrait.x, pausePortrait.y, pausePortrait.w, pausePortrait.h);
        ResourceManager::getInstance().Render(Title_Suisei, renderer);

        ResourceManager::getInstance().Draw(pauseRect.x, pauseRect.y, pauseRect.w, pauseRect.h);
        ResourceManager::getInstance().Render(Pause_Menu, renderer);
        currentButton = (currentButton + totalButtons) % totalButtons;
        for (int i = 0; i < totalButtons; ++i)
        {
            if (i == currentButton)
                button[i].setCurrentButton();
            else
                button[i].notCurrentButton();
        }
        for (int i = 0; i < totalButtons; ++i)
        {
            button[i].render(renderer, HUD_font);
        }
    }
    else if(leveledUp)
    {
        ResourceManager::getInstance().PlayFrame(0,0,0,0,0);
        ResourceManager::getInstance().Draw(screen.x, screen.y, screen.w, screen.h);
        ResourceManager::getInstance().Render(Black_Screen, renderer);

        ResourceManager::getInstance().Draw(pausePortrait.x, pausePortrait.y, pausePortrait.w, pausePortrait.h);
        ResourceManager::getInstance().Render(Title_Suisei, renderer);

        tabs_levelup.render(renderer, HUD_font);
    }
    else if (isOver)
    {
        ResourceManager::getInstance().PlayFrame(0,0,0,0,0);
        ResourceManager::getInstance().Draw(screen.x, screen.y, screen.w, screen.h);
        ResourceManager::getInstance().Render(Black_Screen, renderer);
        textureText.renderText(gameOverText.c_str(), {255, 255, 255}, HUD_font, renderer, SCREEN_WIDTH / 2 - 130, 100, 48);
    }



    ResourceManager::getInstance().Draw(expBaseBar.x, expBaseBar.y, expBaseBar.w, expBaseBar.h);
    ResourceManager::getInstance().Render(HUD_expBarBase, renderer);

    ResourceManager::getInstance().Draw(expTopBar[1].x, expTopBar[1].y, expTopBar[1].w, expTopBar[1].h);
    ResourceManager::getInstance().PlayFrame(0,0,expTopBar[0].w,expTopBar[0].h,0);
    ResourceManager::getInstance().Render(HUD_expBarTop, renderer);

    ResourceManager::getInstance().PlayFrame(0,0,0,0,0);
    ResourceManager::getInstance().Draw(portraitRectDST.x, portraitRectDST.y, portraitRectDST.w, portraitRectDST.h);
    ResourceManager::getInstance().Render(Portrait_Suisei, renderer);

    int temp{0};
    weaponRect = {52.5f, 55, 25 * 1.5, 20 * 1.5};
    levelLabel.x = 55.5f;
    for(int i = 0; i < (int)weapons.size(); ++i)
    {
        if(weapons[i].ID == FALLING_BLOCKS || weapons[i].ID == FUBU_BEAM || weapons[i].ID == BULLET1 || weapons[i].ID == BULLET2 || weapons[i].ID == BULLET3 || weapons[i].ID == BULLET4) continue;
        std::string icon;
        weaponRect.x += 37.5f;
        switch ((int)weapons[i].ID)
        {
        case AXE: icon = SuiseiWeapon_Icon[weapons[i].level / 7]; break;
        case PSYCHO_AXE: icon = PsychoAxe_Icon; break;
        case SPIDER_COOKING: icon = SpiderCooking_Icon; break;
        case BL_BOOK: icon = BLBook_Icon; break;
        case ELITE_LAVA: icon = LavaPool_Icon; break;
        case FAN_BEAM: icon = FanBeam_Icon; break;
        case CEO_TEARS: icon = CEOTears_Icon; break;
        case IDOL_SONG: icon = IdolSong_Icon; break;
        case CUTTING_BOARD: icon = CuttingBoard_Icon; break;
        case X_POTATO: icon = XPotato_Icon; break;
        }
        SDL_RenderCopyF(renderer, ResourceManager::getInstance().getTexture(icon, renderer), NULL, &weaponRect);
        levelLabel.x += 37.5;
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderFillRectF(renderer, &levelLabel);
        textureText.renderText("LV: " + std::to_string(weapons[i].level), {0,0,0}, HUD_font, renderer, 95.0f + 37.5f * temp, 88, 12);
        ++temp;
    }
    for(; temp < 6; ++temp)
    {
        weaponRect = {100.0f + 37.5f * temp, 65, 12 * 1.5 , 11 * 1.5};
        weaponSlot.renderF(renderer, &weaponRect);
    }

    specialSymbol.render(renderer, &specialCase);

    if (specialTopBar[1].w < 138)
    {
        specialBar[0].render(renderer, &specialBaseBar);
        specialBar[1].render(renderer, &specialTopBar[1], &specialTopBar[0]);
    }
    else
    {
        if(count / 10 > 2) count = 0;
        switch (count / 10)
        {
        case 0: specialBar[2].setColor(255, 0, 0); break;
        case 1: specialBar[2].setColor(0, 255, 0); break;
        case 2: specialBar[2].setColor(0, 0, 255); break;
        } 
        specialBar[2].render(renderer, &specialBaseBar);
    }
    specialBar[3].render(renderer, &specialBarFrame);

    hp[0].render(renderer, &hpBaseBar);
    hp[1].render(renderer, &hpTopBar);

    textureText.renderText(levelText.str().c_str(), {255, 255, 255}, HUD_font, renderer, 940, 10, 28);
    textureText.renderText(timeText.str().c_str(), {255, 255, 255}, HUD_font, renderer, SCREEN_WIDTH / 2 - 70, 50, 36);
    textureText.renderText(hpText, {255,255,255}, HUD_font, renderer, 320,40, 20);
}

void HUD::handleEvents(bool &pause, bool &leveledUp, Tabs &direct, int &choice)
{
    if(leveledUp)
    {
        tabs_levelup.handleEvents(leveledUp, choice);
        // direct = Level_Up;
        // leveledUp = false;
        // SDL_ResetKeyboard();
        return;
    }
    direct = Room1;
    if (!pause) return;

    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_KP_ENTER] || currentKeyStates[SDL_SCANCODE_Z])
    {
        if (button[0].getState())
            pause = false;
        else if (button[1].getState())
        {
            direct = Title;
            pause = false;
            Mix_HaltMusic();
        }
        currentButton = 0;
    }
    else if (currentKeyStates[SDL_SCANCODE_UP])
    {
        ++currentButton;
    }
    else if (currentKeyStates[SDL_SCANCODE_DOWN])
    {
        --currentButton;
    }

    SDL_ResetKeyboard();
}