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
    FUBU_BEAM,
    AXE,
    SPIDER_COOKING,
    X_POTATO,
    CEO_TEARS,
    FAN_BEAM,
    BL_BOOK,
    PSYCHO_AXE,
    IDOL_SONG,
    ELITE_LAVA
};

struct DamagingArea
{
    WEAPON_ID weaponID;
    DamagingArea();
    float timePassed{0};
    float start;
    float duration;
    float damage;
    Vector2f center;
    Vector2f direction;
    int hitLimit;
    std::unordered_map<int, float> hitID;
    int currentFrame{-1};
    int frames;
    int attackCount{1};
    float frameTime;
    float lastFrameTime{-100};
    int angle{0};
    float radius;
    float hitCooldown;
    SDL_RendererFlip flip{SDL_FLIP_NONE};
    int count{0};
    bool ofPlayer{true};
};

struct Weapon {
    WEAPON_ID ID;
    Weapon(WEAPON_ID type);
    bool isActive{true};
    int level{1};
    float timeBetweenAttacks;
    float lastAttack{-100};
    int damage;
    Vector2f center{0,0};
    std::unordered_set<int> hitID;
    DamagingArea dmgArea;
    float cooldown{0};
};


void renderWeapon(SDL_Renderer* renderer, DamagingArea& weapon, Player player, int frame, int camX, int camY);

int damageCal(DamagingArea weapon, Player player);

// void inflictDamage(DamagingArea& weapon, Player player, Enemy& enemy, float currentTime);

void inflictDamage(DamagingArea &weapon, Player player, int& enemyHealth, bool& isHit, int enemyID);

// bool hitEnemy(DamagingArea& weapon, Enemy& enemy, Player player, float currentTime);

bool hitEnemy(DamagingArea &weapon, Circle enemyCollider,int& enemyHealth, bool& isHit, int enemyID, Player player);

bool hitPlayer(DamagingArea& weapon, Player& player);
