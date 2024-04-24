#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "physics.hpp"
// #include "enemy.hpp"
#include "math.hpp"
#include "player.hpp"
#include "AnimatedSprites.hpp"

const int frames = 8;

enum WEAPON_ID {
    NONE,
    AXE,
    NUTS,
    SPIDER_COOKING,
    X_POTATO,
    POTATO_EXPLOSION,
    CEO_TEARS,
    FAN_BEAM,
    BL_BOOK,
    PSYCHO_AXE,
    IDOL_SONG,
    ELITE_LAVA,
    CUTTING_BOARD,
    FALLING_BLOCKS,
    BIG_NUT,
    ATK_UP,
    SPD_UP,
    HP_UP,
    HP_RECOVER,
    FUBU_BEAM,
    BULLET1,
    BULLET2,
    BULLET3,
    BULLET4
};

const std::unordered_set<WEAPON_ID> Exception = {FUBU_BEAM, FALLING_BLOCKS, BIG_NUT, BULLET1, BULLET2, BULLET3, BULLET4};

struct DamagingArea
{
    WEAPON_ID weaponID;
    std::string textureID;
    DamagingArea();
    bool isActive{true};
    bool bounce{false};
    float timePassed{0};
    float duration;
    float damage;
    Vector2f center;
    Vector2f rotatingCenter;
    Vector2f direction;
    Vector2f size;
    float projectileSpeed;
    int hitLimit;
    float knockbackSpeed{0};
    float knockbackTime{0};
    std::unordered_map<int, float> hitID;
    int currentFrame{-1};
    int frames;
    int attackCount{1};
    float frameTime{0};
    float lastFrameTime{-100};
    float angle{0};
    float radius;
    float fallTime;
    float hitCooldown{0};
    float attackDelay{0};
    int count{0};
    bool ofPlayer{true};
    bool isExploded{false};
    float areaMultiplier[2]{0,0};
    void update(float timeStep, Vector2f player_center, SDL_Rect camera, bool &shake, int &shakeTime);
    bool hitEnemy(Circle &enemyCollider, int enemyID);
    void explode();
    void render(SDL_Renderer* renderer, Player player, int camX, int camY);
};

struct Weapon {
    WEAPON_ID ID;
    Weapon(WEAPON_ID type);
    int level{1};
    float timeBetweenAttacks;
    DamagingArea dmgArea;
    float cooldown{0};
    float specialDuration[2] = {5,5};
    float timePassed{0};
    int count{0};
    void setHitLimit(int hitLimit);
    void setHitCooldown(float hitCooldown);
    void setDamage(float damage);
    void setAttackInterval(float interval);
    void setArea(float areaIncrease);
    void setDuration(float durationReduction);
    void setAttackCount(int count);
    void setKnockback(float time, float speed);
    void updateStats();
    void initiateDmgArea(Vector2f playerCenter,float playerArrowAngle, SDL_RendererFlip playerFlip, int count, Vector2f direction = {0,0});
};

int damageCal(DamagingArea weapon, Player player);

bool hitPlayer(DamagingArea& weapon, Player& player);