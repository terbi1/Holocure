#pragma once

#include <SDL2/SDL.h>
#include <algorithm>

#include "math.hpp"

bool checkPlayerCollision(SDL_Rect& wall);

bool checkCollision(SDL_Rect object1, SDL_Rect object2);

bool checkCircleCollision(Circle object1, Circle object2);

void collisionEvent(Circle& ene1, Circle& ene2);

bool checkAABBCircleCollision(SDL_Rect rect, Circle cir);

bool checkInside(SDL_Rect rect, Circle cir);
