
#include "Tabs_CharacterSelect.hpp"

Tabs_CharacterSelect::Tabs_CharacterSelect()
{
}

Tabs_CharacterSelect::~Tabs_CharacterSelect()
{
}

Tabs Tabs_CharacterSelect::getDirect()
{
    Tabs temp = direct;
    direct = Character_Select;
    return temp;
}

void Tabs_CharacterSelect::update(float timeStep)
{
    for (int i = 0; i < totalCharacter; ++i)
    {
        if (character[i].getState())
        {
            labelTexts[0] = Player_Name[i];
            descriptions[0] = Weapon_Description[i];
            descriptions[1] = Special_Description[i];
            icons[0] = WeaponIcon[i];
            icons[1] = SpecialIcon[i];
            uniqueAttackName[0] = Weapon_Name[i];
            uniqueAttackName[1] = Special_Name[i];
        }
    }
    timePassed -= timeStep;
    if (timePassed <= 0)
    {
        currentFrame = (currentFrame + 1) % 4;
        timePassed = 0.2;
    }
}

void Tabs_CharacterSelect::setUp(SDL_Renderer *renderer)
{
    character[0] = LButton{"", Vector2f{410, 226}, Vector2f{86, 76}, 2};
    character[1] = LButton{"", Vector2f{500, 226}, Vector2f{86, 76}, 2};
    character[2] = LButton{"", Vector2f{590, 226}, Vector2f{86, 76}, 2};
    character[0].setCurrentButton();
}

void Tabs_CharacterSelect::render(SDL_Renderer *renderer, TTF_Font *font)
{
    ResourceManager::getInstance().PlayFrame(0, 0, 0, 0, 0);
    ResourceManager::getInstance().Draw(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    ResourceManager::getInstance().Render("res/gfx/menu_charselecBG.png", renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRects(renderer, panels, 3);
    SDL_RenderFillRects(renderer, labels, 3);
    for (int i = 0; i < 3; ++i)
        textTexture.renderText(labelTexts[i], {0, 183, 235}, font, renderer, labels[i].x + 8, labels[i].y + 8, 24);

    ResourceManager::getInstance().Draw(labels[1].x + 8, labels[1].y + 50, 25 * 1.5, 20 * 1.5);
    ResourceManager::getInstance().Render(icons[0], renderer);
    textTexture.renderText(descriptions[0], {255, 255, 255}, font, renderer, labels[1].x + 8, labels[1].y + 100, 20, 270);
    textTexture.renderText(uniqueAttackName[0], {255, 255, 255}, font, renderer, labels[1].x + 50, labels[1].y + 60, 20, 270);

    ResourceManager::getInstance().Draw(labels[2].x + 8, labels[2].y + 50, 25 * 1.5, 20 * 1.5);
    ResourceManager::getInstance().Render(icons[1], renderer);
    textTexture.renderText(descriptions[1], {255, 255, 255}, font, renderer, labels[2].x + 8, labels[2].y + 100, 20, 270);
    textTexture.renderText(uniqueAttackName[1], {255, 255, 255}, font, renderer, labels[2].x + 50, labels[2].y + 60, 20, 270);

    currentCharacter = (currentCharacter + totalCharacter) % totalCharacter;
    for (int i = 0; i < totalCharacter; ++i)
    {
        ResourceManager::getInstance().Draw(character[i].getCenter().x - 43, character[i].getCenter().y - 38, 86, 76);
        ResourceManager::getInstance().Render(characterIcon[i], renderer);
        if (i == currentCharacter)
            character[i].setCurrentButton();
        else
            character[i].notCurrentButton();
        character[i].render(renderer, NULL);
    }

    SDL_Rect dst;
    dst.x = 0;
    dst.y = 50;

    SDL_QueryTexture(ResourceManager::getInstance().getTexture(IdleAnimation[currentCharacter][currentFrame], renderer), NULL, NULL, &dst.w, &dst.h);
    dst.w *= 5;
    dst.h *= 5;
    ResourceManager::getInstance().Draw(dst.x, dst.y, dst.w, dst.h);
    ResourceManager::getInstance().PlayFrame(0,0,0,0,0);
    ResourceManager::getInstance().Render(IdleAnimation[currentCharacter][currentFrame], renderer, SDL_FLIP_NONE, 0);
}

void Tabs_CharacterSelect::handleEvents(Character &player)
{
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_KP_ENTER] || currentKeyStates[SDL_SCANCODE_Z])
    {
        for (int i = 0; i < totalCharacter; ++i)
        {
            if (character[i].getState())
            {
                player = (Character)i;
            }
        }
        direct = Mode_Select;
        SDL_ResetKeyboard();
        return;
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        ++currentCharacter;
    }
    else if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        --currentCharacter;
    }

    SDL_ResetKeyboard();
}
