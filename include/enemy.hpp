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
    FUBUZILLA
};

class Enemy
{
public:
    int ID;
    ENEMY_TYPE type;
    Enemy(ENEMY_TYPE m_type, Vector2f m_center, int m_ID);
    int health;
    int atk;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    Circle collider;
    void move(Vector2f player_pos);
    void render(SDL_Renderer* renderer, int frame, int camX, int camY);
    bool isHit{false};
    int currentFrame{0};
    LTexture animation;
    float cd{0};
    int expValue;
    float frameTime{0.2};
    int frames;
    float timePassed{0};
private:
    SDL_Texture* runAnimation[ANIMATION_FRAMES];
    std::string currentTexture;
    float speed;
    Vector2f velocity;
};

void spawn(std::vector<Enemy>& gang, Vector2f playerPos, ENEMY_TYPE type, int ID);

bool compareByX(const Enemy &a, const Enemy &b);