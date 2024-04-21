#pragma once

#include "GameState.hpp"
#include <vector>
#include <SDL2/SDL.h>

class GameStateMachine
{
public:
    GameStateMachine() {}
    ~GameStateMachine() {}

    void pushState(GameState* state);
    void changeState(GameState* state);
    void popState();

    void update();
    void render();
    void onKeyDown(SDL_Event* e);
    void onKeyUp(SDL_Event* e);
    void onMouseButtonUp(SDL_Event& e);
    void onMouseButtonDown(SDL_Event& e);
    void onMouseMove(SDL_Event& e);
private:
    std::vector<GameState*> gameStates;
};