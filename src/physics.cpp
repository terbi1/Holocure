
#include "physics.hpp"

bool checkCollision(SDL_Rect object1, SDL_Rect object2) {
    if(
        (object1.x < (object2.x + object2.w))
    &&  (object2.x < (object1.x + object1.w))
    &&  (object1.y < (object2.y + object2.h))
    &&  (object2.y < (object1.y + object1.h))) {
        return true;
    }
    
    return false;
}

bool checkCircleCollision(Circle object1, Circle object2) {
    
    float centerDistance = distance(object1.center, object2.center);
    
    if(centerDistance > (object1.radius + object2.radius)) return false;
    
    return true;
}

void collisionEvent(Circle& ene1, Circle& ene2) {
    // ene1.pos.x -= cos(pointDirection(ene1.pos, ene2.pos));
    // ene1.pos.y -= sin(pointDirection(ene1.pos, ene2.pos));
    // ene1.hitBox.x = ene1.pos.x;
    // ene1.hitBox.y = ene1.pos.y;
    ene1.center.x -= 2 * cos(pointDirection(ene1.center, ene2.center));
    ene1.center.y -= 2 * sin(pointDirection(ene1.center, ene2.center));
}

bool checkAABBCircleCollision(SDL_Rect rect, Circle cir) {
    
    Vector2f point;
    
    point.x = std::clamp((int)cir.center.x, rect.x, rect.x + rect.w);
    point.y = std::clamp((int)cir.center.y, rect.y, rect.y + rect.h);

    float length = distance(point, cir.center);

    if(length > cir.radius) return false;

    return true;
}
