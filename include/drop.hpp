#pragma once

#include <SDL2/SDL.h>

#include "math.hpp"

enum DROP_TYPE {
    EXP,
    COIN
};

struct Drop {
    DROP_TYPE ID;
    Vector2f pos;
    Drop(DROP_TYPE p_ID, Vector2f p_pos)
        :ID(p_ID), pos(p_pos){}
    SDL_Texture* p_texture;
    int SPEED{5};
    void pickedUp(Vector2f player_pos);
};