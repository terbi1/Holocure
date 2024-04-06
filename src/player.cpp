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

}

void Player::move()
{

    // update the position
    // pos.x += velocity.x;
    // pos.y += velocity.y;
    collider.center += velocity;
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
