#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "GameState.hpp"
#include "utils.hpp"
#include "Data.hpp"
#include "Tabs_Title.hpp"
#include "Room1.hpp"
#include "Hud.hpp"
#include "Tabs_LevelUp.hpp"

class Game {

public:
    Game();
    ~Game();

    void init(const char* p_title, int p_w, int p_h);
    void loadmedia();
    void handleEvents();
    void playMusic();
    void update(float timeStep);
    void render();
    void clean();
    bool running()
    {
        return isRunning;
    }
private:
    bool shake{false};
    bool isRunning{true};
    SDL_Window *window;
    SDL_Renderer *renderer;
    int tabs;
    Tabs currentTab{Title};
    GameState gameState;
    Tabs_Title tabs_title;
    Tabs_Room1 tabs_room1;
    Tabs_LevelUp tabs_levelup;
    TTF_Font* font;
};
