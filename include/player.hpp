#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "math.hpp"
#include "RenderWindow.hpp"
#include "Structure.hpp"
#include "ResourceManager.hpp"
#include "Data.hpp"

enum PLAYER_TYPE {
    SUISEI
};

enum State {
    IDLE = 4,
    RUN = 6
};

class Player
{
public:
    Player();
    void handleEvent();
    void move();
    Vector2f getPos() {
        return pos;
    }
    LTexture animation;
    LTexture arrow;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    State state{IDLE};
    SDL_Rect hitBox{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 24, 26};
    void render(SDL_Renderer* renderer, int frame, int camX, int camY);
    int maxHP{70};
    int health{maxHP};
    Circle collider{Vector2f{SCREEN_WIDTH / 2 + 16, SCREEN_HEIGHT / 2 + 26}, 10};
    int arrowAngle{0};
    float currentExp{0};
    int LEVEL{1};
    int currentFrame{0};
    float atk{130};
    float crit{10};
    float critMod{50};
    float specialCD{10};
    void increaseSpeed(float increasePercent);
private:
    Vector2f pos{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    float SPEED {1.3};
    Vector2f velocity{0,0};
};

