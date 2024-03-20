#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <sstream>

namespace utils
{
    inline float hireTimeInSeconds()
    {
        float t = SDL_GetTicks();
        t /= 1000.0f;

        return t;
    }

    inline float timeInMinutes(float time)
    {
        return (float)(time / 60000);
    }

    inline float timeInSeconds(float time)
    {
        return (float)(time / 1000);
    }
    
}