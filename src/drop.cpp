
#include "drop.hpp"

void Drop::pickedUp(Vector2f player_pos) {
    if(distance(player_pos, pos) > 100) return;
    
    Vector2f moveVector = vectorNormalize(Vector2f{player_pos.x - pos.x, player_pos.y - pos.y});

    pos.x += moveVector.x * SPEED;
    pos.y += moveVector.y * SPEED;
}