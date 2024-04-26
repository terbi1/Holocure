#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "math.hpp"
#include "Structure.hpp"
#include "ResourceManager.hpp"
#include "Data.hpp"

enum State {
    IDLE = 4,
    RUN = 6
};

class Player
{
private:
    std::string textureID;
    float atk{130};
    Vector2f pos{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    float SPEED {1.3};
    Vector2f velocity{0,0};
    float timePassed{0};
public:
    Player();
    Character playerID;
    void setPlayer(Character ID);
    void handleEvent();
    void update(float timeStep);
    Vector2f getPos() {
        return pos;
    }
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    State state{IDLE};
    void render(SDL_Renderer* renderer, int frame, int camX, int camY);
    int maxHP{70};
    int health{maxHP};
    Circle collider{Vector2f{SCREEN_WIDTH / 2 + 16, SCREEN_HEIGHT / 2 + 26}, 10};
    int arrowAngle{0};
    float currentExp{0};
    int LEVEL{1};
    int currentFrame{0};
    float crit{10};
    float critMod{50};
    float specialCD{15};
    float getATK()
    {
        return atk;
    }
    void increaseATK(float increase);
    void increaseSpeed(float increasePercent);
    void heal(float healPercent);
    void increaseMaxHP(float increasePercent);
    void resetStats();
};

