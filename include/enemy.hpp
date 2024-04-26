#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <string>

#include "math.hpp"
#include "RenderWindow.hpp"
#include "Data.hpp"
#include "Structure.hpp"
#include "ResourceManager.hpp"
#include "weapon.hpp"


const int ANIMATION_FRAMES = 3;

enum ENEMY_TYPE {
    DEADBEAT,
    SHRIMP,
    TAKODACHI,
    KFP_EMPLOYEE,
    DARK_SHRIMP,
    BLOOM,
    GLOOM,
    DEAD_BATTER,
    MIKOP,
    HOSHIYOMI,
    SORATOMO,
    FUBUZILLA,
    A_CHAN,
    YAGOO
};

class Enemy
{
public:
    int ID;
    std::string currentTexture;
    ENEMY_TYPE type;
    Enemy(ENEMY_TYPE m_type, Vector2f m_center, int m_ID);
    int health;
    int atk;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    Circle collider;
    void update(Vector2f player_pos, float timeStep);
    void getKnockedBack(Vector2f direction, float time, float speed);
    void takeDamage(int damage){
        health -= damage;
        isHit = true;
    }
    void render(SDL_Renderer* renderer, int frame, int camX, int camY);
    bool isHit{false};
    int currentFrame{0};
    float cd{0};
    float specialCD[4]{4,4,14,6};
    float specialDuration[3]{2.1,0,6};
    int expValue;
    float frameTime{0.2};
    int frames;
    float timePassed{0.3};
    Vector2f direction;
    Vector2f knockbackDir;
    bool notMoving{false};
    WEAPON_ID attack{BULLET3};
private:
    float speed;
    Vector2f movingCenter{0,0};
    float angle{0};
    float knockbackSpeed{0};
    float knockbackTime{0};
    float temp{1};
};

void spawn(std::vector<Enemy>& gang, Vector2f playerPos, ENEMY_TYPE type, int ID);

bool compareByX(const Enemy &a, const Enemy &b);