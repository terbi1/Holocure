
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
    if(rand() % 200 == 0)
    {
        expValue = -1;
        ID = FOOD;
    }
    else
    {
        expValue = m_expValue;
        ID = EXP;
    }
    if(expValue == -1) textureID = 6;
    else if(expValue <= 10) textureID = 0;
    else if(expValue >= 11 && expValue <= 19) textureID = 1;
    else if(expValue >= 20 && expValue <= 49) textureID = 2;
    else if(expValue >= 50 && expValue <= 99) textureID = 3;
    else if(expValue >= 100 && expValue <= 199) textureID = 4;
    else textureID = 5;
}

void ExpDrop::render(SDL_Renderer* renderer, int camX, int camY)
{
    ResourceManager::getInstance().Draw((int)pos.x - camX, (int)pos.y - camY, int(12 * 1.5), int(13 * 1.5));
    ResourceManager::getInstance().PlayFrame(0,0,0,0,0);
    ResourceManager::getInstance().Render(EXP_Drop[textureID], renderer);
}