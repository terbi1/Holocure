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
#include "Hud.hpp"

bool isOutsideOfView(Circle object, int camX, int camY);

class GameStates 
{
private:
    std::unordered_map<WEAPON_ID, int> optionPool;
    int shakeStrength{1};
    int shakeTime{0};
    TTF_Font *DMG_font = NULL;
    LTexture dmgText;
    bool playing;
    bool pause{false};
    int time;
    Tabs direct{Room1};
    bool isOver{false};
    bool isWon{false};
    bool recordScore;
    Vector2f moved;
    Player player;
    HUD playerHUD;
    std::unordered_set<int> trace;
    std::vector<Enemy> enemies;
    std::vector<Enemy> bosses;
    std::vector<Weapon> weapons;
    std::vector<ExpDrop> dropItems;
    std::vector<DamagingArea> activeAttack;
    std::vector<DamagingArea> bossAttack;
    std::unordered_set<ENEMY_TYPE> spawnPool;
    std::vector<DamageNumber> dmgNumbers;
    int MAX_WEAPON{6};
    float spawnCooldown{200};
    float spawnRate;
    bool boss {false};
    bool finalBoss{false};
    int bossIndex{0};
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
    void weaponUpdate();
    void checkWeaponLimit();
    void update(float timeStep, bool &shake);
    void render(SDL_Renderer *renderer, bool shake);
    void reset();
    void handleEvent();
    void startCD();
    bool gameOver();
    bool leveledUp{false};
    bool endless{false};
    std::vector<WEAPON_ID> optionKey;
    std::vector<int> optionLevel;
    float specialCD{0};
    int EnemyCount{0};
    Character ID = None;
    Player getPlayer() {
        return player;
    }
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    int reqNextLevel{79};
    int choice{-1};
};
