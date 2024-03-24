#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "player.hpp"
#include "enemy.hpp"
#include "weapon.hpp"
#include "Tabs_Title.hpp"
#include "Room1.hpp"
#include "drop.hpp"
#include "utils.hpp"

class Game_State 
{
public: 
    Game_State();
    ~Game_State();
    Tabs getDirect();
    bool getOver();
    bool getPlaying();
    void setPlaying(bool _playing);
    bool getPause();
    void setUpPlayRoom(SDL_Renderer* renderer);
    void updateGameState(short int updateLines);
    void render (SDL_Renderer *renderer);
    void reset();
    void handleEvent();
    void pauseGame();
    void startCD();
    bool gameOver();
    void update();
    Player getPlayer() {
        return player;
    }
private:
    bool playing;
    bool pause;
    int time;
    Tabs direct;
    // GameOverAnnouncement* gameOverAnnouncement;
    bool isOver;
    bool recordScore;
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Weapon> weapons;
    std::vector<Drop> dropItems;
};
