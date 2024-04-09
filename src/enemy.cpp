
#include "enemy.hpp"

Enemy::Enemy(ENEMY_TYPE m_type, Vector2f m_center, int m_ID)
{
    collider.center = m_center;
    type = m_type;
    ID = m_ID;

    switch ((int)type)
    {
    case SHRIMP:
    {
        health = 8;
        atk = 2;
        speed = 0.35;
        expValue = 6;
        collider.radius = 18;
        frames = 2;
        break;
    }
    case DEADBEAT:
    {
        health = 40;
        atk = 4;
        speed = 0.4;
        expValue = 7;
        collider.radius = 21;
        frames = 2;
        break;
    }
    case TAKODACHI:
    {
        health = 80;
        atk = 4;
        speed = 0.4;
        expValue = 8;
        collider.radius = 18;
        frames = 2;
        break;
    }
    case KFP_EMPLOYEE:
    {
        health = 20;
        atk = 2;
        speed = 1;
        expValue = 3;
        collider.radius = 14;
        frames = 2;
        break;
    }
    case DARK_SHRIMP:
    {
        health = 125;
        atk = 5;
        speed = 0.6;
        expValue = 12;
        collider.radius = 18;
        frames = 2;
        break;
    }
    case BLOOM:
    case GLOOM:
    {
        health = 30;
        atk = 6;
        speed = 0.7;
        expValue = 12;
        collider.radius = 15;
        frames = 2;
        break;
    }
    case FUBUZILLA:
    {
        health = 8000;
        atk = 15;
        speed = 0.8;
        expValue = 2000;
        collider.radius = 110;
        frames = 11;
        break;
    }
    }
}

void Enemy::move(Vector2f player_center)
{
    if (collider.center.x >= player_center.x)
        flip = SDL_FLIP_HORIZONTAL;
    else
        flip = SDL_FLIP_NONE;
    Vector2f moveVector = vectorNormalize(player_center - collider.center);
    collider.center += moveVector * speed;
}

void Enemy::render(SDL_Renderer *renderer, int frame, int camX, int camY)
{

    float multiplier;

    switch ((int)type)
    {
    case SHRIMP:
        currentTexture = Shrimp_Animation[frame];
        multiplier = 1.5;
        break;
    case DEADBEAT:
        currentTexture = Deadbeat_Animation[frame];
        multiplier = 2;
        break;
    case TAKODACHI:
        currentTexture = Takodachi_Animation[frame];
        multiplier = 2;
        break;
    case KFP_EMPLOYEE:
        currentTexture = KFP_Animation[frame];
        multiplier = 1.5;
        break;
    case DARK_SHRIMP:
        currentTexture = DarkShrimp_Animation[frame];
        multiplier = 1.5;
        break;
    case FUBUZILLA:
        currentTexture = Fubuzilla_Animation[frame];
        multiplier = 4;
        break;
    case BLOOM:
        currentTexture = Bloom_Animation[frame];
        multiplier = 1.5;
        break;
    case GLOOM:
        currentTexture = Gloom_Animation[frame];
        multiplier = 1.5;
        break;
    }

    animation.importTexture(ResourceManager::getInstance().getTexture(currentTexture, renderer));

    SDL_Rect dst;

    SDL_QueryTexture(animation.getTexture(), NULL, NULL, &dst.w, &dst.h);
    dst.w *= multiplier;
    dst.h *= multiplier;

    dst.x = collider.center.x - dst.w / 2 - camX;
    dst.y = collider.center.y - dst.h / 2 - camY;

    if (isHit)
    {
        SDL_SetTextureColorMod(animation.getTexture(), 255, 0, 0);
        isHit = false;
    }
    else
        SDL_SetTextureColorMod(animation.getTexture(), 255, 255, 255);

    SDL_RenderCopyEx(renderer, animation.getTexture(), NULL, &dst, 0, NULL, flip);
}

void spawn(std::vector<Enemy> &enemies, Vector2f playerPos, ENEMY_TYPE type, int ID)
{

    float randomAngle = (float)(rand() % 360) * 3.14f / 180.0f;

    Vector2f spawnDirection = {cosf(randomAngle), sinf(randomAngle)};

    Vector2f spawnPos = playerPos + spawnDirection * Vector2f{SCREEN_WIDTH, SCREEN_HEIGHT};

    enemies.push_back(Enemy{type, spawnPos, ID});
}

bool compareByX(const Enemy &a, const Enemy &b)
{
    return a.collider.center.x + a.collider.radius < b.collider.center.x + b.collider.radius;
}
