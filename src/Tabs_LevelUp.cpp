#include "Tabs_LevelUp.hpp"

Tabs_LevelUp::Tabs_LevelUp()
{
    
}

Tabs_LevelUp::~Tabs_LevelUp()
{

}

Tabs Tabs_LevelUp::getDirect() {
    return direct;
}

void Tabs_LevelUp::setUp(SDL_Renderer* renderer)
{
    optionCase.loadFromFile(OptionCase, renderer);
    upgrade[0] = LButton{"",Vector2f{600, 150}, Vector2f{700,100}, 1};
    upgrade[1] = LButton{"",Vector2f{600, 260}, Vector2f{700,100}, 1};
    upgrade[2] = LButton{"",Vector2f{600, 370}, Vector2f{700,100}, 1};
    upgrade[3] = LButton{"",Vector2f{600, 480}, Vector2f{700,100}, 1};
    upgrade[0].setCurrentButton();
}

void Tabs_LevelUp::getResource(WEAPON_ID type, int level, int i)
{
    switch ((int)type)
            {
            case PSYCHO_AXE:
                optionName[i] = "Psycho Axe LV " + std::to_string(level);
                upgrade[i].setText(PsychoAxeDescription[level - 1]);
                iconTexture[i] = PsychoAxe_Icon;
                break;
            case SPIDER_COOKING:
                optionName[i] = "Spider Cooking LV " + std::to_string(level);
                upgrade[i].setText(SpiderCookingDescription[level - 1]);
                iconTexture[i] = SpiderCooking_Icon;
                break;
            case BL_BOOK:
                optionName[i] = "BL Book LV " + std::to_string(level);
                upgrade[i].setText(BLBookDescription[level - 1]);
                iconTexture[i] = BLBook_Icon;
                break;
            case ELITE_LAVA:
                optionName[i] = "Elite Lava LV " + std::to_string(level);
                upgrade[i].setText(EliteLavaDescription[level - 1]);
                iconTexture[i] = LavaPool_Icon;
                break;
            case FAN_BEAM:
                optionName[i] = "Fan Beam LV " + std::to_string(level);
                upgrade[i].setText(FanBeamDescription[level - 1]);
                iconTexture[i] = FanBeam_Icon;
                break;
            case CEO_TEARS:
                optionName[i] = "CEO's Tears LV " + std::to_string(level);
                upgrade[i].setText(CeoTearsDescription[level - 1]);
                iconTexture[i] = CEOTears_Icon;
                break;
            case IDOL_SONG:
                optionName[i] = "Idol Song LV " + std::to_string(level);
                upgrade[i].setText(IdolSongDescription[level - 1]);
                iconTexture[i] = IdolSong_Icon;
                break;
            case CUTTING_BOARD:
                optionName[i] = "Cutting Board LV " + std::to_string(level);
                upgrade[i].setText(CuttingBoardDescription[level - 1]);
                iconTexture[i] = CuttingBoard_Icon;
                break;
            case X_POTATO:
                optionName[i] = "X Potato LV " + std::to_string(level);
                upgrade[i].setText(XPotatoDescription[level - 1]);
                iconTexture[i] = XPotato_Icon;
                break;
            case AXE:
                optionName[i] = "Axe Swing LV " + std::to_string(level);
                upgrade[i].setText(SuiseiWeaponDescription[level - 1]);
                if (level == 7)
                    iconTexture[i] = SuiseiWeapon_Icon[1];
                else
                    iconTexture[i] = SuiseiWeapon_Icon[0];
                break;
            case ATK_UP:
                optionName[i] = "ATK Up";
                upgrade[i].setText("Increase ATK by 8%.");
                iconTexture[i] = AttackUp_Icon;
                break;
            case HP_UP:
                optionName[i] = "Max HP Up";
                upgrade[i].setText("Increase Max HP by 10%.");
                iconTexture[i] = MaxHPUp_Icon;
                break;
            case SPD_UP:
                optionName[i] = "SPD Up";
                upgrade[i].setText("Increase SPD by 12%.");
                iconTexture[i] = SpeedUp_Icon;
                break;
            case HP_RECOVER:
                optionName[i] = "Food";
                upgrade[i].setText("Recover 20% of Max HP.");
                iconTexture[i] = HPRecover_Icon;
                break;
            }
}

void Tabs_LevelUp::handleEvents(bool &leveledUp, int &choice)
{
    // direct = Level_Up;
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_KP_ENTER])
    {
        for(int i = 0; i < 4; ++i)
        {
            if(upgrade[i].getState()) 
            {
                choice = i;
                break;
            }
        }
        leveledUp = false;
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

void Tabs_LevelUp::render(SDL_Renderer* renderer, TTF_Font* font)
{
    SDL_Rect caseRect{275, 20, 64, 64};
    SDL_Rect iconRect{282, 32, 50, 40};
    currentButton = (currentButton + 4) % 4;
    for(int i = 0; i < 4; ++i)
    {
        if(i == currentButton) upgrade[i].setCurrentButton();
        else upgrade[i].notCurrentButton();
        upgrade[i].render(renderer, font);
        caseRect.y += 110;
        iconRect.y += 110;
        optionCase.render(renderer, &caseRect);
        SDL_RenderCopy(renderer, ResourceManager::getInstance().getTexture(iconTexture[i], renderer), NULL, &iconRect);
    }
    for(int i = 0; i < 4; ++i)
    {
        textureText.renderText(optionName[i], {255,255,255}, font, renderer, 260, 105 + 110 * i,20);
    }
}