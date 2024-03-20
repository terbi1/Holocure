#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "math.hpp"
#include "RenderWindow.hpp"

const int IDLE_FRAMES = 4;
const int RUN_FRAMES = 6;

enum PLAYER_TYPE {
    SUISEI
};

enum State {
    IDLE = 4,
    RUN = 6
};

struct healthBar{
    float value;
    SDL_Texture* base;
    SDL_Texture* hp;
    SDL_Rect src;
    SDL_Rect dst;
};

class Player
{
public:
    Player(PLAYER_TYPE, RenderWindow window);
    void handleEvent();
    // bool attack(Entity enemy);
    void move();
    Vector2f getPos() {
        return pos;
    }
    SDL_Texture* idleAnimation[IDLE_FRAMES];
    SDL_Texture* runAnimation[RUN_FRAMES];
    SDL_Texture* arrow;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    State state{IDLE};
    SDL_Rect hitBox{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 24, 26};
    void render(SDL_Renderer* renderer, int frame, int camX, int camY);
    healthBar health;
    Vector2f centerPoint{SCREEN_WIDTH / 2 + 16, SCREEN_HEIGHT / 2 + 26};
    int arrowAngle{0};
    float currentExp{0};
    int LEVEL{1};
private:
    Vector2f pos{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    float SPEED {3};
    Vector2f velocity{0,0};
};

