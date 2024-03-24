#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "GameState.hpp"
#include "utils.hpp"
#include "Data.hpp"

class Game {

public:
    Game();
    ~Game();

    void init(const char* p_title, int p_w, int p_h);
    void loadmedia();
    void handleEvents();
    void playMusic();
    void update();
    void render();
    void clean();
    bool running()
    {
        return isRunning;
    }
private:
    bool isRunning{true};
    SDL_Window *window;
    SDL_Renderer *renderer;
    Game_State *gameState;
    int tabs;
    Tabs_Title* tabs_title;
    Tabs_Room1* tabs_room1;
    TTF_Font* font;
};
