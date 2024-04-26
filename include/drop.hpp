#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "Data.hpp"
#include "ResourceManager.hpp"
#include "math.hpp"

enum DROP_TYPE {
    EXP,
    FOOD
};

struct Drop 
{
    Drop();
    DROP_TYPE ID;
    Vector2f pos;
    Drop(DROP_TYPE p_ID, Vector2f p_pos)
        :ID(p_ID), pos(p_pos){}
    SDL_Texture* p_texture;
    int SPEED{5};
};

struct ExpDrop : public Drop 
{
    ExpDrop(int expValue, Vector2f m_pos);
    float maximumLifeTime{120};
    bool pickedUp(Vector2f player_pos);
    void render(SDL_Renderer* renderer, int camX, int camY);
    int expValue;
    int textureID;
};
