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
#include "Hud.hpp"



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
    void updateSpawnPool(int minuteTimer, int secondTimer);
    void bossSpawn(int minuteTimer, int secondTimer);
    void update(float timeStep);
    void render(SDL_Renderer *renderer);
    void reset();
    void handleEvent();
    void startCD();
    bool gameOver();
    int EnemyCount{0};
    Player getPlayer() {
        return player;
    }
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    int reqNextLevel{61};
private:
    TTF_Font *DMG_font = NULL;
    LTexture dmgText;
    bool playing;
    bool pause{false};
    int time;
    Tabs direct{Room1};
    // GameOverAnnouncement* gameOverAnnouncement;
    bool isOver{false};
    bool recordScore;
    Vector2f moved;
    Player player;
    HUD playerHUD;
    int enemyFrame{0};
    std::vector<Enemy> enemies;
    std::vector<Weapon> weapons;
    std::vector<ExpDrop> dropItems;
    std::vector<DamagingArea> activeAttack;
    std::unordered_set<ENEMY_TYPE> spawnPool;
    std::vector<ENEMY_TYPE> bosses; 
    std::vector<DamageNumber> dmgNumbers;
    float spawnCooldown{0};
    float spawnRate;
    bool boss {false};
};
