#pragma once

#include "GameState.hpp"
#include <string>

class MenuState : public GameState
{
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual void onKeyDown(SDL_Event *e);
    virtual void onKeyUp(SDL_Event *e);
    virtual void onMouseButtonUp(SDL_Event &e);
    virtual void onMouseButtonDown(SDL_Event &e);
    virtual void onMouseMove(SDL_Event &e);

    virtual std::string getStateID() const { return menuID; }

private:
    static const std::string menuID;
};