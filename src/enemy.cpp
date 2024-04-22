
#include "enemy.hpp"

Enemy::Enemy(ENEMY_TYPE m_type, Vector2f m_center, int m_ID)
{
    collider.center = movingCenter = m_center;
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
        collider.radius = 15;
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
    case DEAD_BATTER:
    {
        health = 150;
        atk = 7;
        speed = 0.6;
        expValue = 9;
        collider.radius = 22;
        frames = 2;
        break;
    }
    case MIKOP:
    {
        health = 200;
        atk = 8;
        speed = 0.9;
        expValue = 10;
        collider.radius = 18;
        frames = 2;
        break;
    }
    case HOSHIYOMI:
    {
        health = 1000;
        atk = 10;
        speed = 0.4f;
        expValue = 13;
        collider.radius = 17;
        frames = 2;
        break;
    }
    case SORATOMO:
    {
        health = 250;
        atk = 6;
        speed = 0.9;
        expValue = 10;
        collider.radius = 9;
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
    case A_CHAN:
    {
        health = 20000;
        atk = 5;
        speed = 1.0;
        expValue = 6000;
        collider.radius = 14;
        frames = 3;
        break;
    }
    }
}

void Enemy::update(Vector2f player_center, float timeStep)
{
    timePassed += timeStep;
    frameTime -= timeStep;
    cd -= timeStep;
    if (frameTime <= 0)
    {
        currentFrame = (currentFrame + 1) % (frames + 1);
        frameTime = enemyFrameTime;
    }
    if(notMoving)
    {
        if(specialCD[3] <= 0)
        {
            specialCD[3] = 6;
            notMoving = false;
        }
        specialCD[3] -= timeStep;
        return;
    }
    if(timePassed >= 0.3)
    {
        flip = collider.center.x >= player_center.x ? SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE;
        
        direction = vectorNormalize(player_center - collider.center);
        
        timePassed = 0;
    }
    if(type == A_CHAN)
    {
        direction = vectorNormalize(player_center - movingCenter);
        angle += 0.3 * temp;

        collider.center.x = 400 * sinf(angle / 180.0f * M_PI) + movingCenter.x;
        collider.center.y = 400 * sinf(angle / 180.0f * M_PI) * cosf(angle / 180.0f * M_PI) + movingCenter.y;
        // circularMotion(collider.center, player_center, 0.01 * speed);
        specialCD[0] -= timeStep;
        specialCD[1] -= timeStep;
        specialCD[2] -= timeStep;
        specialDuration[0] -= timeStep;
        if(specialCD[2] <= 0) notMoving = true;
        movingCenter += direction * speed;
        if(notMoving)
        {
            temp = (movingCenter.x < player_center.x ? 1:-1);
        }
        return;
    }

    collider.center += direction * speed;

    if(knockbackTime > 0)
    {
        collider.center += knockbackDir * knockbackSpeed;
        knockbackTime -= timeStep;
    }
}

void Enemy::getKnockedBack(Vector2f direction, float time, float speed)
{
    if(type == FUBUZILLA) return;
    knockbackDir = direction;
    knockbackTime = time;
    knockbackSpeed = speed;
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
        multiplier = 1.5;
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
    case A_CHAN:
        currentTexture = AChan_Animation[frame];
        multiplier = 1.5;
        break;
    case DEAD_BATTER:
        currentTexture = DeadBatter_Animation[frame];
        multiplier = 1.5;
        break;
    case MIKOP:
        currentTexture = MikoP_Animation[frame];
        multiplier = 1.5;
        break;
    case HOSHIYOMI:
        currentTexture = Hoshiyomi_Animation[frame];
        multiplier = 1.5;
        break;
    case SORATOMO:
        currentTexture = Soratomo_Animation[frame];
        multiplier = 1.5;
        break;
    }

    SDL_Rect dst;

    SDL_QueryTexture(ResourceManager::getInstance().getTexture(currentTexture, renderer), NULL, NULL, &dst.w, &dst.h);
    dst.w *= multiplier;
    dst.h *= multiplier;

    dst.x = collider.center.x - dst.w / 2 - camX;
    dst.y = collider.center.y - dst.h / 2 - camY;

    if (isHit)
    {
        SDL_SetTextureColorMod(ResourceManager::getInstance().getTexture(currentTexture, renderer), 255,0,0);
    }
    ResourceManager::getInstance().Draw(dst.x,dst.y,dst.w,dst.h);
    ResourceManager::getInstance().PlayFrame(0,0,0,0,0);
    ResourceManager::getInstance().Render(currentTexture, renderer, flip, 0);

    if (isHit)
    {
        SDL_SetTextureColorMod(ResourceManager::getInstance().getTexture(currentTexture, renderer), 255,255,255);
        isHit = false;
    }
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
