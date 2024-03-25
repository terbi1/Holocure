
#include "enemy.hpp"

Enemy::Enemy(ENEMY_TYPE m_type,Vector2f m_center)
    // : pos(pos.x, pos.y)
{
    // hitBox.x = pos.x;
    // hitBox.y = pos.y;
    // hitBox.w = 30;
    // hitBox.h = 40;
    collider.center = m_center;
    type = m_type;

    switch((int)type) {
        case DEADBEAT:
        collider.radius = 10;
        // runAnimation[0] = window.loadTexture(Deadbeat_Animation[0].c_str());
        // runAnimation[1] = window.loadTexture(Deadbeat_Animation[1].c_str());
        // runAnimation[2] = window.loadTexture(Deadbeat_Animation[2].c_str());
        // runAnimation[0].loadFromFile("res/gfx/spr_Deadbeat/spr_Deadbeat_0.png", renderer);
        // runAnimation[1].loadFromFile("res/gfx/spr_Deadbeat/spr_Deadbeat_1.png", renderer);
        // runAnimation[2].loadFromFile("res/gfx/spr_Deadbeat/spr_Deadbeat_2.png", renderer);
        break;
        case SHRIMP:
        collider.radius = 14;
        // runAnimation[0].loadFromFile("res/gfx/spr_Shrimp/spr_Shrimp_0.png", renderer);
        // runAnimation[1].loadFromFile("res/gfx/spr_Shrimp/spr_Shrimp_1.png", renderer);
        // runAnimation[2].loadFromFile("res/gfx/spr_Shrimp/spr_Shrimp_2.png", renderer);
        break;
    }
}


void Enemy::move(Vector2f player_pos) {
    if(collider.center.x >= player_pos.x + 32) flip = SDL_FLIP_HORIZONTAL;
    else flip = SDL_FLIP_NONE;
    Vector2f moveVector = vectorNormalize(Vector2f{player_pos.x + 32 - collider.center.x, player_pos.y + 32 - collider.center.y});

    moveVector *= SPEED;
    collider.center += moveVector;
    // collider.center.x += moveVector.x * SPEED;
    // collider.center.y += moveVector.y * SPEED;
    // hitBox.x = pos.x;
    // hitBox.y = pos.y;
    // std::cout << pos.x << ' ' << pos.y << "\n";
}

void Enemy::render(SDL_Renderer* renderer, int frame, int camX, int camY) {
    // SDL_Rect dst;
    // dst.x = pos.x - camX;
    // dst.y = pos.y - camY;
    // SDL_QueryTexture(runAnimation[frame], NULL, NULL, &dst.w, &dst.h);
    // dst.w*=1.5; dst.h*=1.5;
    // SDL_RenderCopyEx(renderer, runAnimation[frame], NULL, &dst, 0, NULL, flip);
    // dst.w = hitBox.w;
    // dst.h = hitBox.h;
    // SDL_RenderDrawRect(renderer, &dst);

    switch((int)type)
    {
        // case DEADBEAT: runAnimation[frame] = ResourceManager::getInstance().getTexture(Deadbeat_Animation[frame], renderer); break;
        // case SHRIMP: runAnimation[frame] = ResourceManager::getInstance().getTexture(Shrimp_Animation[frame], renderer); break;
        case SHRIMP: currentTexture = Shrimp_Animation[frame];
        case DEADBEAT: currentTexture = Deadbeat_Animation[frame];
    }

    LTexture animation;
    animation.importTexture(ResourceManager::getInstance().getTexture(currentTexture,renderer));

    SDL_Rect dst;

    SDL_QueryTexture(animation.getTexture(), NULL, NULL, &dst.w, &dst.h);
    dst.w *= 1.5; dst.h *= 1.5;

    dst.x = collider.center.x - dst.w / 2 - camX;
    dst.y = collider.center.y - dst.h / 2 - camY;
    

    if(isHit) {
        SDL_SetTextureColorMod(animation.getTexture(), 255, 0, 0);
        // runAnimation[frame].setColor( 255, 0, 0);
        isHit = false;
    }
    else SDL_SetTextureColorMod(animation.getTexture(), 255, 255, 255);

    SDL_RenderCopyEx(renderer, animation.getTexture(), NULL, &dst, 0, NULL, flip);
    // runAnimation[frame].render(renderer, &dst, NULL, 0, NULL, flip);

    // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    // SDL_RenderDrawPoint(renderer, collider.center.x - camX, collider.center.y - camY);
}

void spawn(std::vector<Enemy>& enemies, Vector2f playerPos, ENEMY_TYPE type) {

    float randomAngle = (float)(rand() % 360) * 3.14f / 180.0f;

    Vector2f spawnDirection = {cosf(randomAngle), sinf(randomAngle)};

    // Vector2f spawnPos = {playerPos.x + spawnDirection.x * SCREEN_WIDTH, playerPos.y + spawnDirection.y * SCREEN_HEIGHT};
    Vector2f spawnPos = playerPos + spawnDirection * Vector2f{SCREEN_WIDTH, SCREEN_HEIGHT};

    enemies.push_back(Enemy{DEADBEAT, spawnPos});
}
