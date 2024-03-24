#pragma once

#include <SDL2/SDL.h>
#include <vector>

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
    CEO_TEARS
};

struct damagingArea {
    WEAPON_ID weaponID;
    SDL_Texture* texture[frames];
    AnimatedSprite sprites;
    float damage;
    int maxHit;
    std::vector<int> hitEnemiesID;
    void render(SDL_Renderer* renderer, Player player, int frame, int camX, int camY);
    std::vector<int> enemy_ID;
    int frames;
    int currentFrame{0};
};

struct Weapon {
    WEAPON_ID ID;
    Weapon(WEAPON_ID type, SDL_Renderer* renderer);
    bool isActive{true};
    int level{1};
    damagingArea aoe;
    SDL_Rect area{};
    float duration;
    float cd;
    float timePassed{0};
    float lastAttack;
};

void renderWeapon(SDL_Renderer* renderer, Weapon& weapon, Player player, int frame, int camX, int camY);

void inflictDamage(Weapon& weapon, Enemy& enemy, Player player, SDL_Renderer* renderer, int camX, int camY);
