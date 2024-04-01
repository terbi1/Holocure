#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "physics.hpp"
#include "enemy.hpp"
#include "math.hpp"
#include "player.hpp"
#include "AnimatedSprites.hpp"

const int frames = 8;

enum WEAPON_ID {
    AXE,
    SPIDER_COOKING,
    X_POTATO,
    CEO_TEARS,
    FAN_BEAM,
    BL_BOOK,
    PSYCHO_AXE
};

struct DamagingArea
{
    WEAPON_ID weaponID;
    DamagingArea();
    float timePassed;
    float start;
    float duration;
    float damage;
    Vector2f center;
    Vector2f direction;
    int hitLimit;
    std::unordered_map<int, float> hitID;
    int currentFrame{0};
    int frames;
    int attackCount{1};
    float frameTime;
    float lastFrameTime;
    int angle{0};
    float radius;
    float hitCooldown;
    SDL_RendererFlip flip{SDL_FLIP_NONE};
    int i{0};
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
};


void renderWeapon(SDL_Renderer* renderer, DamagingArea& weapon, Player player, int frame, int camX, int camY);

int damageCal(DamagingArea weapon, Player player);

void inflictDamage(DamagingArea& weapon, Player player, Enemy& enemy, float currentTime);

bool hitEnemy(DamagingArea& weapon, Enemy& enemy, Player player, float currentTime);
