
#include "GameState.hpp"

GameState::GameState()
{
}

GameState::~GameState()
{
}

void GameState::loadMedia(SDL_Renderer *renderer)
{
    player.idleAnimation[0].importTexture(ResourceManager::getInstance().getTexture(IdleAnimation_Suisei[0], renderer));
    player.idleAnimation[1].importTexture(ResourceManager::getInstance().getTexture(IdleAnimation_Suisei[1], renderer));
    player.idleAnimation[2].importTexture(ResourceManager::getInstance().getTexture(IdleAnimation_Suisei[2], renderer));
    player.idleAnimation[3].importTexture(ResourceManager::getInstance().getTexture(IdleAnimation_Suisei[3], renderer));
    player.runAnimation[0].importTexture(ResourceManager::getInstance().getTexture(RunAnimation_Suisei[0], renderer));
    player.runAnimation[1].importTexture(ResourceManager::getInstance().getTexture(RunAnimation_Suisei[1], renderer));
    player.runAnimation[2].importTexture(ResourceManager::getInstance().getTexture(RunAnimation_Suisei[2], renderer));
    player.runAnimation[3].importTexture(ResourceManager::getInstance().getTexture(RunAnimation_Suisei[3], renderer));
    player.runAnimation[4].importTexture(ResourceManager::getInstance().getTexture(RunAnimation_Suisei[4], renderer));
    player.runAnimation[5].importTexture(ResourceManager::getInstance().getTexture(RunAnimation_Suisei[5], renderer));
    player.arrow.importTexture(ResourceManager::getInstance().getTexture(PlayerArrow, renderer));
}

Tabs GameState::getDirect()
{
    return direct;
}

void GameState::update(float currentTime)
{

    // player event

    // spawn enemies
    if (currentTime - lastSpawnTime >= 1)
    {
        while (enemies.size() < 100)
        {
            for (int i = 0; i < 5; ++i)
                spawn(enemies, player.getPos(), SHRIMP);
            break;
        }
        lastSpawnTime = currentTime;
    }

    // player event
    player.handleEvent();
    player.move();

    // enemy move
    // for (int i = 0; i < (int)enemies.size(); ++i)
    // {
    //     enemies[i].move(player.getPos());
    //     ++enemies[i].currentFrame;
    //     if (enemies[i].currentFrame / 4 / 3 > 2)
    //     {
    //         enemies[i].currentFrame = 0;
    //     }
    // }
    // for (int i = 0; i < (int)enemies.size(); ++i)
    // {
    //     for (int j = 0; j < (int)enemies.size(); ++j)
    //     {
    //         if (i == j)
    //             continue;
    //         if (checkCircleCollision(enemies[i].collider, enemies[j].collider))
    //         {
    //             collisionEvent(enemies[i], enemies[j]);
    //         }
    //     }
    // }
    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        it->move(player.getPos());
        ++it->currentFrame;
        if (it->currentFrame / 4 / 3 > 2)
        {
            it->currentFrame = 0;
        }
        for (auto it2 = enemies.begin(); it2 != enemies.end(); ++it2)
        {
            if (it == it2)
                continue;
            if (checkCircleCollision(it->collider, it2->collider))
            {
                collisionEvent(*it, *it2);
            }
        }
    }

    // moving animation frame
    // ++frame;
    ++player.currentFrame;
    if ((player.currentFrame / 2 / player.state) > (player.state - 1))
    {
        player.currentFrame = 0;
    }
    //
    // ++enemyFrame;
    // if (enemyFrame / 4 / 3 > 2)
    // {
    //     enemyFrame = 0;
    // }
    // if(axe.isActive)
    // {
    //     if(attackFrame == 4)
    //         for(int i = 0; i < enemies.size(); ++i)
    //             inflictDamage(axe, enemies[i], player,windowgetRenderer(), camera.x, camera.y);
    //     ++attackFrame;
    //     if ((attackFrame / 4) > 5)
    //     {
    //         attackFrame = 0;
    //         axe.isActive = false;
    //         axe.lastAttack = SDL_GetTicks();
    //     }
    // }
    // for (auto itGang = enemies.begin(); itGang != enemies.end()++itGang)
    // {
    //     inflictDamage(spiderCooking, *itGang, player, windowgetRendere(), camera.x, camera.y);
    //     if(itGang -> health <= 0) {
    //         dropItems.push_back(Drop(EXP, itGang -> collidercenter));
    //         enemies.erase(itGang);
    //     }
    // }
    if (dropItems.size() > 0)
        for (auto itDrop = dropItems.begin(); itDrop != dropItems.end(); ++itDrop)
        {
            if (dropItems.size() <= 0)
                break;
            Vector2f temp = itDrop->pos;
            float dis = distance(player.centerPoint, temp);
            std::cout << dis;
            if (dis <= 10.0)
            {
                dropItems.erase(itDrop);
                player.currentExp += 1000;
                --itDrop;
            }
            else
                itDrop->pickedUp(player.centerPoint);
        }

    while (player.currentExp >= reqNextLevel)
    {
        player.currentExp -= reqNextLevel;
        reqNextLevel = pow(4 * (player.LEVEL + 1), 2.1) - pow(4 * player.LEVEL, 2.1);
        ++player.LEVEL;
        std::cout << reqNextLevel << '\n';
    }
    // expTopBarSRC.w = player.currentExp / reqNextLevel * 648;
    // expTopBar.w = player.currentExp / reqNextLevel *(SCREEN_WIDTH +10);
}

void GameState::render(SDL_Renderer *renderer)
{

    // Center the camera over the player
    camera.x = (player.getPos().x + player.hitBox.w / 2) - SCREEN_WIDTH / 2;
    camera.y = (player.getPos().y + player.hitBox.h / 2) - SCREEN_HEIGHT / 2;
    camera.w = SCREEN_WIDTH;
    camera.h = SCREEN_HEIGHT;

    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        it->render(renderer, it->currentFrame / 4 / 3, camera.x, camera.y);
    }

    player.render(renderer, player.currentFrame / 2 / player.state, camera.x, camera.y);

    // // sui.health.dst = {sui.hitBox.x, sui.hitBox.y + sui.hitBox.h, sui.hitBox.w, 6};
    // // inflictDamage(axe, deadbeat, sui, window.getRenderer(), camera.x, camera.y);

    for(auto it = dropItems.begin(); it != dropItems.end(); ++it) {
        SDL_Rect dst{it->pos.x - camera.x, it->pos.y - camera.y, int(12 * 1.5), int(13 * 1.5)};
        SDL_RenderCopy(renderer, ResourceManager::getInstance().getTexture(EXP_Drop, renderer), NULL, &dst);
        SDL_RenderDrawPoint(renderer, it->pos.x - camera.x, it->pos.y - camera.y);
    }

}

void GameState::reset()
{
}

void GameState::handleEvent()
{
}