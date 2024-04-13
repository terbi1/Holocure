
#include "drop.hpp"

bool ExpDrop::pickedUp(Vector2f player_center) {
    if(distance(player_center, pos) <= 10) return true;

    if(distance(player_center, pos) > 100) return false;
    
    Vector2f moveVector = vectorNormalize(player_center - pos);

    moveVector *= SPEED;
    pos += moveVector;
    
    return false;
}

Drop::Drop()
{
    
}

ExpDrop::ExpDrop(int m_expValue, Vector2f m_pos) 
{
    pos = m_pos;
    expValue = m_expValue;
    ID = EXP;
}

void ExpDrop::render(SDL_Renderer* renderer, int camX, int camY)
{
    std::string expTexture;

    if(expValue <= 10) expTexture = 
    EXP_Drop[0];
    else if(expValue >= 11 && expValue <= 19) expTexture = EXP_Drop[1];
    else if(expValue >= 20 && expValue <= 49) expTexture = EXP_Drop[2];
    else if(expValue >= 50 && expValue <= 99) expTexture = EXP_Drop[3];
    else if(expValue >= 100 && expValue <= 199) expTexture = EXP_Drop[4];
    else expTexture = EXP_Drop[5];

    SDL_Rect dst{(int)pos.x - camX, (int)pos.y - camY, int(12 * 1.5), int(13 * 1.5)};
    SDL_RenderCopy(renderer, ResourceManager::getInstance().getTexture(expTexture, renderer), NULL, &dst);
}