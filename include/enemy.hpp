#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <vector>
#include <unordered_map>

#include "math.hpp"
#include "RenderWindow.hpp"
#include "Data.hpp"
#include "Structure.hpp"
#include "ResourceManager.hpp"


const int ANIMATION_FRAMES = 3;

enum ENEMY_TYPE {
    DEADBEAT,
    SHRIMP
};

class Enemy
{
public:
    ENEMY_TYPE type;
    Enemy(ENEMY_TYPE m_type, Vector2f m_center, RenderWindow window);
    float health{20};
    float atk;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    Circle collider;
    void move(Vector2f player_pos);
    void render(SDL_Renderer* renderer, int frame, int camX, int camY);
    bool isHit{false};
private:
    SDL_Texture* runAnimation[ANIMATION_FRAMES];
    float SPEED{0.5};
    Vector2f velocity;
};

void spawn(std::vector<Enemy>& gang, RenderWindow window, Vector2f playerPos, ENEMY_TYPE type);