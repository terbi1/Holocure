#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "math.hpp"
#include "RenderWindow.hpp"
#include "Structure.hpp"
#include "ResourceManager.hpp"
#include "Data.hpp"

const int IDLE_FRAMES = 4;
const int RUN_FRAMES = 6;

enum PLAYER_TYPE {
    SUISEI
};

enum State {
    IDLE = 4,
    RUN = 6
};

// struct healthBar{
//     float value;
//     SDL_Texture* base;
//     SDL_Texture* hp;
//     SDL_Rect src;
//     SDL_Rect dst;
// };

class Player
{
public:
    Player();
    void loadTexture(PLAYER_TYPE, SDL_Renderer* renderer);
    void handleEvent();
    // bool attack(Entity enemy);
    void move();
    Vector2f getPos() {
        return pos;
    }
    // SDL_Texture* idleAnimation[IDLE_FRAMES];
    // SDL_Texture* runAnimation[RUN_FRAMES];
    LTexture idleAnimation[IDLE_FRAMES];
    LTexture runAnimation[RUN_FRAMES];
    LTexture arrow;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    State state{IDLE};
    SDL_Rect hitBox{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 24, 26};
    void render(SDL_Renderer* renderer, int frame, int camX, int camY);
    int health{70};
    Circle collider{Vector2f{SCREEN_WIDTH / 2 + 16, SCREEN_HEIGHT / 2 + 26}, 10};
    Vector2f centerPoint{SCREEN_WIDTH / 2 + 16, SCREEN_HEIGHT / 2 + 26};
    int arrowAngle{0};
    float currentExp{0};
    int LEVEL{1};
    int currentFrame{0};
    float atk{130};
    float crit{10};
    float critMod{50};
private:
    Vector2f pos{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    float SPEED {1.3};
    Vector2f velocity{0,0};
};

