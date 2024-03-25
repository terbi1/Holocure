#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "player.hpp"
#include "math.hpp"

Player::Player()
{
}

void Player::loadTexture(PLAYER_TYPE type, SDL_Renderer* renderer)
{
    idleAnimation[0].importTexture(ResourceManager::getInstance().getTexture(IdleAnimation_Suisei[0], renderer));
    idleAnimation[1].importTexture(ResourceManager::getInstance().getTexture(IdleAnimation_Suisei[1], renderer));
    idleAnimation[2].importTexture(ResourceManager::getInstance().getTexture(IdleAnimation_Suisei[2], renderer));
    idleAnimation[3].importTexture(ResourceManager::getInstance().getTexture(IdleAnimation_Suisei[3], renderer));        
    runAnimation[0].importTexture(ResourceManager::getInstance().getTexture(RunAnimation_Suisei[0], renderer));      
    runAnimation[1].importTexture(ResourceManager::getInstance().getTexture(RunAnimation_Suisei[1], renderer));      
    runAnimation[2].importTexture(ResourceManager::getInstance().getTexture(RunAnimation_Suisei[2], renderer));      
    runAnimation[3].importTexture(ResourceManager::getInstance().getTexture(RunAnimation_Suisei[3], renderer));
    runAnimation[4].importTexture(ResourceManager::getInstance().getTexture(RunAnimation_Suisei[4], renderer));
    runAnimation[5].importTexture(ResourceManager::getInstance().getTexture(RunAnimation_Suisei[5], renderer));
}

void Player::handleEvent()
{
    velocity.x = velocity.y = 0;
    bool flippable = true;
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_Z])
    {
        flippable = false;
    }
    if (currentKeyStates[SDL_SCANCODE_UP])
    {
        if (flippable)
        {
            // if (arrowAngle == 180)
            //     arrowAngle = -135;
            // else if (arrowAngle == 0)
            //     arrowAngle = -45;
            // else
                arrowAngle = -90;
        }
        velocity.y -= SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_DOWN])
    {
        if (flippable)
        {
            // if (arrowAngle == 180)
            //     arrowAngle = 135;
            // else if (arrowAngle == 0)
            //     arrowAngle = 45;
            // else
                arrowAngle = 90;
        }
        velocity.y += SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        if (flippable)
        {
            // if (arrowAngle == -90)
            //     arrowAngle = -135;
            // else if (arrowAngle == 90)
            //     arrowAngle = 135;
            // else
                arrowAngle = 180;
            flip = SDL_FLIP_HORIZONTAL;
        }
        velocity.x -= SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        if (flippable)
        {
            // if (arrowAngle == -90)
            //     arrowAngle = -45;
            // else if (arrowAngle == 90)
            //     arrowAngle = 45;
            // else
                arrowAngle = 0;
            flip = SDL_FLIP_NONE;
        }
        velocity.x += SPEED;
    }

    currentKeyStates = NULL;
}

void Player::move()
{

    // update the position
    pos.x += velocity.x;
    pos.y += velocity.y;
    centerPoint.x += velocity.x;
    centerPoint.y += velocity.y;
    // update sprite states
    if (velocity.x == 0 && velocity.y == 0)
        state = IDLE;
    else
        state = RUN;

    // move hitbox
    hitBox.x = pos.x + 2;
    hitBox.y = pos.y + 8;
}

void Player::render(SDL_Renderer *renderer, int frame, int camX, int camY)
{

    SDL_Rect dst;
    dst.x = pos.x - camX - 34;
    dst.y = pos.y - camY - 30;
    // dst.w = 34;
    // dst.h = 34;

    SDL_Rect hitBoxDST = {centerPoint.x - 75, centerPoint.y - 75, 150, 150};
    hitBoxDST.x -= camX;
    hitBoxDST.y -= camY;

    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // SDL_RenderCopy(renderer, health.base, &health.src, &health.dst);
    // SDL_RenderCopy(renderer, health.hp, &health.src, &health.dst);

    // std::cout << pos.x << ' ' << pos.y << '\n';

    switch (state)
    {
    case IDLE:
        SDL_QueryTexture(idleAnimation[frame].getTexture(), NULL, NULL, &dst.w, &dst.h);
        dst.w *= 1.5;
        dst.h *= 1.5;
        SDL_RenderCopyEx(renderer, arrow.getTexture(), NULL, &dst, (float)arrowAngle, NULL, SDL_FLIP_NONE);
        dst.y -= 20;
        SDL_RenderCopyEx(renderer, idleAnimation[frame].getTexture(), NULL, &dst, 0, NULL, flip);
        // return;
        break;
    case RUN:
        SDL_QueryTexture(runAnimation[frame].getTexture(), NULL, NULL, &dst.w, &dst.h);
        dst.w *= 1.5;
        dst.h *= 1.5;
        SDL_RenderCopyEx(renderer, arrow.getTexture(), NULL, &dst, (float)arrowAngle, NULL, SDL_FLIP_NONE);
        dst.y -= 20;
        SDL_RenderCopyEx(renderer, runAnimation[frame].getTexture(), NULL, &dst, 0, NULL, flip);
        // return;
        break;
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
    // SDL_RenderDrawPoint(renderer, pos.x + 32 - camX, pos.y + 32 - camY);
    SDL_RenderDrawPoint(renderer, centerPoint.x - camX, centerPoint.y - camY);

    SDL_RenderDrawRect(renderer, &hitBoxDST);
}
