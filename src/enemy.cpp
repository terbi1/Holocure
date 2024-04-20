
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
    case A_CHAN:
    {
        health = 45000;
        atk = 20;
        speed = 1.0;
        expValue = 6000;
        collider.radius = 32;
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
        circularMotion(collider.center, player_center, 0.01 * speed);
        specialCD[0] -= timeStep;
        specialCD[1] -= timeStep;
        specialCD[2] -= timeStep;
        specialDuration[0] -= timeStep;
        if(specialCD[2] <= 0) notMoving = true;
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
    case A_CHAN:
        currentTexture = AChan_Animation[frame];
        multiplier = 1.5;
        break;
    }

    // animation.importTexture(ResourceManager::getInstance().getTexture(currentTexture, renderer));

    SDL_Rect dst;

    SDL_QueryTexture(ResourceManager::getInstance().getTexture(currentTexture, renderer), NULL, NULL, &dst.w, &dst.h);
    dst.w *= multiplier;
    dst.h *= multiplier;

    dst.x = collider.center.x - dst.w / 2 - camX;
    dst.y = collider.center.y - dst.h / 2 - camY;

    if (isHit)
    {
        // SDL_SetTextureColorMod(animation.getTexture(), 255, 0, 0);
        SDL_SetTextureColorMod(ResourceManager::getInstance().getTexture(currentTexture, renderer), 255,0,0);
        // isHit = false;
    }
    // SDL_RenderCopyEx(renderer, animation.getTexture(), NULL, &dst, 0, NULL, flip);
    ResourceManager::getInstance().Draw(dst.x,dst.y,dst.w,dst.h);
    ResourceManager::getInstance().PlayFrame(0,0,0,0,0);
    ResourceManager::getInstance().Render(currentTexture, renderer, flip, 0);

    if (isHit)
    {
        // SDL_SetTextureColorMod(animation.getTexture(), 255, 0, 0);
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
