#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <deque>
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

const int chunkSize = 16;

bool isOutsideOfView(Circle object, int camX, int camY);

class GameStates 
{
private:
    std::unordered_map<WEAPON_ID, int> optionPool{{PSYCHO_AXE, 1}, {BL_BOOK, 1}, {SPIDER_COOKING, 1}, {ELITE_LAVA, 1}, {FAN_BEAM, 1}, {CEO_TEARS, 1}, {AXE, 2}, {IDOL_SONG,1}, {ATK_UP, 0}, {HP_UP, 0}, {HP_RECOVER, 0}, {SPD_UP, 0}};
    // std::unordered_map<WEAPON_ID, int> optionPool{{PSYCHO_AXE, 1}, {SPIDER_COOKING, 1}, {AXE, 2}, {ELITE_LAVA,1}};
    // std::unordered_map<WEAPON_ID, int> option;
    std::vector<WEAPON_ID> optionKey;
    std::vector<int> optionLevel;
    int shakeStrength{1};
    int shakeTime{0};
    TTF_Font *DMG_font = NULL;
    LTexture dmgText;
    bool playing;
    bool pause{false};
    int time;
    Tabs direct{Room1};
    bool isOver{false};
    bool recordScore;
    bool leveledUp{false};
    Vector2f moved;
    Player player;
    HUD playerHUD;
    std::unordered_set<int> trace;
    std::vector<Enemy> enemies;
    std::vector<Weapon> weapons;
    std::vector<ExpDrop> dropItems;
    std::vector<DamagingArea> activeAttack;
    std::unordered_set<ENEMY_TYPE> spawnPool;
    // std::vector<ENEMY_TYPE> bosses; 
    std::vector<DamageNumber> dmgNumbers;
    int MAX_WEAPON{6};
    float spawnCooldown{0};
    float spawnRate;
    bool boss {false};
public: 
    GameStates();
    ~GameStates();
    void loadMedia(SDL_Renderer* renderer);
    Tabs getDirect();
    void start();
    bool getOver();
    bool getPlaying();
    void setPlaying(bool _playing);
    bool getPause();
    void updateSpawnPool(int minuteTimer, int secondTimer);
    void bossSpawn(int minuteTimer, int secondTimer);
    void update(float timeStep, bool &shake);
    void render(SDL_Renderer *renderer, bool shake);
    void reset();
    void handleEvent();
    void startCD();
    bool gameOver();
    float specialCD{0};
    int EnemyCount{0};
    Player getPlayer() {
        return player;
    }
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    int reqNextLevel{79};
    int choice{-1};
};
