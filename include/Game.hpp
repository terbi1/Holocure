#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
// #include "GameState.h"
// #include "Tabs_Settings.h"

class Game {

public:
    Game();
    ~Game();

    void init(const char* title, int xPos, int yPos, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen);
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
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    // FPS_Processor* gFPS_Processor;
    // Game_State *gameState;
    // BallteProcessor* battleProcessor;
    // int tabs;
    // Tabs_Menu tabs_menu;
    // HelpsAndCredit* helpsAndCredit;
    // UserSettings* userSettings;
};
