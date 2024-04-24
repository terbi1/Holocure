#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "player.hpp"
#include "math.hpp"

Player::Player()
{
}

void Player::setPlayer(Character ID)
{
    playerID = ID;
    switch((int)ID)
    {
        case Suisei:
        atk = 130;
        SPEED = 1.3;
        maxHP = health = 70;
        specialCD = 65;
        return;
        case Risu:
        atk = 110;
        SPEED = 1.5;
        maxHP = health = 60;
        specialCD = 15;
        return;
    }
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

void Player::update(float timeStep)
{
    collider.center += velocity;

    // update sprite states
    if (velocity.x == 0 && velocity.y == 0)
        state = IDLE;
    else
        state = RUN;

    timePassed -= timeStep;
    if (timePassed <= 0)
    {
        currentFrame = (currentFrame + 1) % (int)state;
        timePassed = 0.2;
    }
}

void Player::render(SDL_Renderer *renderer, int frame, int camX, int camY)
{
    SDL_Rect dst;
    dst.x = collider.center.x - camX - 48;
    dst.y = collider.center.y - camY - 54;

    switch ((int)state)
    {
    case IDLE:
        textureID = IdleAnimation[playerID][frame];
        break;
    case RUN:
        textureID = RunAnimation[playerID][frame];
        break;
    }
    SDL_QueryTexture(ResourceManager::getInstance().getTexture(textureID, renderer), NULL, NULL, &dst.w, &dst.h);
    dst.w *= 1.5;
    dst.h *= 1.5;
    ResourceManager::getInstance().Draw(dst.x, dst.y, dst.w, dst.h);
    ResourceManager::getInstance().PlayFrame(0,0,0,0,0);
    ResourceManager::getInstance().Render(PlayerArrow, renderer, SDL_FLIP_NONE, (float)arrowAngle);
    dst.y -= 20;
    ResourceManager::getInstance().Draw(dst.x, dst.y, dst.w, dst.h);
    ResourceManager::getInstance().PlayFrame(0,0,0,0,0);
    ResourceManager::getInstance().Render(textureID, renderer, flip, 0);
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
    if (health > maxHP)
        health = maxHP;
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