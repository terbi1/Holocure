#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "GameStates.hpp"
#include "utils.hpp"
#include "Data.hpp"
#include "Tabs_Title.hpp"
#include "Room1.hpp"
#include "Hud.hpp"
#include "Tabs_LevelUp.hpp"
#include "Tabs_End.hpp"
#include "Tabs_CharacterSelect.hpp"

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
    GameStates gameState;
    Tabs_Title tabs_title;
    Tabs_CharacterSelect tabs_characterSelect;
    Tabs_Room1 tabs_room1;
    Tabs_LevelUp tabs_levelup;
    Tabs_End tabs_end;
    TTF_Font* font;
    Mix_Music* titleMusic = NULL;
    Mix_Music* roomMusic = NULL;
};
