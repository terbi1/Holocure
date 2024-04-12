#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "player.hpp"
#include "math.hpp"

Player::Player()
{
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
            arrowAngle = -90;
        }
        velocity.y -= SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_DOWN])
    {
        if (flippable)
        {
            arrowAngle = 90;
        }
        velocity.y += SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        if (flippable)
        {
            arrowAngle = 180;
            flip = SDL_FLIP_HORIZONTAL;
        }
        velocity.x -= SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        if (flippable)
        {
            arrowAngle = 0;
            flip = SDL_FLIP_NONE;
        }
        velocity.x += SPEED;
    }
}

void Player::move()
{
    collider.center += velocity;
    // update sprite states
    if (velocity.x == 0 && velocity.y == 0)
        state = IDLE;
    else
        state = RUN;
}

void Player::render(SDL_Renderer *renderer, int frame, int camX, int camY)
{
    SDL_Rect dst;
    dst.x = collider.center.x - camX - 48;
    dst.y = collider.center.y - camY - 54;

    switch((int)state)
    {
        case IDLE: animation.importTexture(ResourceManager::getInstance().getTexture(IdleAnimation_Suisei[frame].c_str(), renderer)); break;
        case RUN: animation.importTexture(ResourceManager::getInstance().getTexture(RunAnimation_Suisei[frame].c_str(), renderer)); break;
    }
    SDL_QueryTexture(animation.getTexture(), NULL, NULL, &dst.w, &dst.h);
    dst.w *= 1.5;
    dst.h *= 1.5;
    SDL_RenderCopyEx(renderer, ResourceManager::getInstance().getTexture(PlayerArrow, renderer), NULL, &dst, (float)arrowAngle, NULL, SDL_FLIP_NONE);
    dst.y -= 20;
    SDL_RenderCopyEx(renderer, animation.getTexture(), NULL, &dst, 0, NULL, flip);
}

void Player::increaseATK(float increase)
{
    atk += increase;
}

void Player::increaseSpeed(float increasePercent)
{
    SPEED *= (100 + increasePercent) / 100;
}

void Player::heal(float healPercent)
{
    health += (float)maxHP * healPercent / 100.0f; 
    if(health > maxHP) health = maxHP;
}

void Player::increaseMaxHP(float increasePercent)
{
    maxHP *= (100.0f + increasePercent) / 100.0f;
}

void Player::resetStats()
{
    health = maxHP = 70;
    LEVEL = 1;
    arrowAngle = 0;
    currentExp = 0;
    atk = 130;
    SPEED = 1.3;
    flip = SDL_FLIP_NONE;
}