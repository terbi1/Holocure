#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "player.hpp"
#include "enemy.hpp"
#include "weapon.hpp"
#include "drop.hpp"
#include "utils.hpp"
#include "ResourceManager.hpp"
#include "Data.hpp"
#include "Structure.hpp"
#include "RenderWindow.hpp"

class GameState 
{
public: 
    GameState();
    ~GameState();
    void loadMedia(SDL_Renderer* renderer);
    Tabs getDirect();
    bool getOver();
    bool getPlaying();
    void setPlaying(bool _playing);
    bool getPause();
    void update(float currentTime);
    void render(SDL_Renderer *renderer);
    void reset();
    void handleEvent();
    void pauseGame();
    void startCD();
    bool gameOver();
    Player getPlayer() {
        return player;
    }
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    int reqNextLevel{61};
private:
    bool playing;
    bool pause;
    int time;
    Tabs direct{Room1};
    // GameOverAnnouncement* gameOverAnnouncement;
    bool isOver;
    bool recordScore;
    Player player;
    int enemyFrame{0};
    float lastSpawnTime{0};
    std::vector<Enemy> enemies;
    std::vector<Weapon> weapons;
    std::vector<Drop> dropItems;
};
