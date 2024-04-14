#pragma once

#include <string>
#include <SDL2/SDL.h>

class GameState
{
public:
    virtual void update() = 0;
    virtual void render() = 0;
    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;
    virtual void onKeyDown(SDL_Event* e) = 0;
    virtual void onKeyUp(SDL_Event* e) = 0;
    virtual void onMouseButtonUp(SDL_Event& e) = 0;
    virtual void onMouseButtonDown(SDL_Event& e) = 0;
    virtual void onMouseMove(SDL_Event& e) = 0;
    virtual std::string getStateID() const = 0;
protected:

};