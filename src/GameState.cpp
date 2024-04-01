
#include "GameState.hpp"

GameState::GameState()
{
}

GameState::~GameState()
{

}

void GameState::loadMedia(SDL_Renderer *renderer)
{
    DMG_font = TTF_OpenFont(font_8bitPLus.c_str(),24);
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

    weapons.push_back(Weapon(AXE));
    weapons.push_back(Weapon(SPIDER_COOKING));
    weapons.push_back(Weapon(CEO_TEARS));
    weapons.push_back(Weapon(FAN_BEAM));
    weapons.push_back(Weapon(BL_BOOK));
    weapons.push_back(Weapon(PSYCHO_AXE));

    playerHUD.initHUD(renderer, player.health);
    playerHUD.HUD_Timer.start();
    playerHUD.HUD_Timer.pause();

}

Tabs GameState::getDirect()
{
    return direct;
}

bool GameState::getPause()
{
    return pause;
}

void GameState::updateSpawnPool(int minuteTimer, int secondTimer)
{

    if (minuteTimer == 0 && secondTimer == 0)
        spawnPool.insert(SHRIMP);
    if (minuteTimer == 3 && secondTimer == 0)
        spawnPool.erase(SHRIMP);

    if (minuteTimer == 0 && secondTimer == 30)
        spawnPool.insert(DEADBEAT);
    if (minuteTimer == 5 && secondTimer == 0)
        spawnPool.erase(DEADBEAT);

    if (minuteTimer == 3 && secondTimer == 0)
        spawnPool.insert(TAKODACHI);
    if (minuteTimer == 5 && secondTimer == 0)
        spawnPool.erase(TAKODACHI);

    if (minuteTimer == 4 && secondTimer == 0)
        spawnPool.insert(KFP_EMPLOYEE);
    if (minuteTimer == 6 && secondTimer == 0)
        spawnPool.erase(KFP_EMPLOYEE);

    spawnRate = (minuteTimer * 60 + secondTimer) / 10 + 10;
}

void GameState::update(float timeStep, float currentTime)
{
    if (pause)
    {
        playerHUD.HUD_Timer.pause();
        return;
    }
    else if (isOver)
    {
        return;
    }
    else
        playerHUD.HUD_Timer.unpause();

    // spawn enemies
    // if (timeStep - lastSpawnTime >= 1)
    // {

    updateSpawnPool(playerHUD.HUD_Timer.getTicks(Minute), playerHUD.HUD_Timer.getTicks(Second) - 60 * playerHUD.HUD_Timer.getTicks(Minute));

    if (currentTime >= lastSpawn + spawnCooldown)
    {
        int temp = rand() % (int)spawnPool.size();
        std::unordered_set<ENEMY_TYPE>::iterator it;
        it = spawnPool.begin();
        for (int i = 0; i < temp; ++i)
            ++it;
        for (int i = 0; i < spawnRate; ++i)
        {
            lastSpawn = currentTime;
            spawn(enemies, player.collider.center, *it, EnemyCount);
            ++EnemyCount;
        }
    }

    //dmg numbers
    for(auto it = dmgNumbers.begin(); it != dmgNumbers.end(); ++it)
    {
        if(it->duration <= 0) 
        {
            dmgNumbers.erase(it);
            --it;
            continue;
        }
        it->update(timeStep);
    }

    // player event
    Vector2f temp = player.collider.center;
    player.move();
    moved = player.collider.center - temp;

    // initiate attacks
    for (auto it = weapons.begin(); it != weapons.end(); ++it)
    {
        if (currentTime - it->lastAttack < it->timeBetweenAttacks)
            continue;

        it->lastAttack = currentTime;
        it->dmgArea.lastFrameTime = currentTime;
        it->dmgArea.start = currentTime;

        for(int i = 0; i < it->dmgArea.attackCount; ++i)
        {
            switch ((int)it->ID)
        {
        case AXE:
        {
            it->dmgArea.center = player.collider.center;
            it->dmgArea.angle = player.arrowAngle;
            it->dmgArea.flip = player.flip;
            break;
        }
        case SPIDER_COOKING:
        {
            it->dmgArea.center = player.collider.center;
            break;
        }
        case CEO_TEARS:
        {
            it->dmgArea.center = player.collider.center;
            int index = rand() % (int)enemies.size();
            it->dmgArea.direction = vectorNormalize(enemies[index].collider.center - player.collider.center);
            break;
        }
        case FAN_BEAM:
        {
            it->dmgArea.center = player.collider.center;
            it->dmgArea.flip = player.flip;
            break;
        }
        case BL_BOOK:
        {
            Vector2f temp {player.collider.center.x, player.collider.center.y - it->dmgArea.radius};
            circularMotion(temp, player.collider.center, 2 * PI / it->dmgArea.attackCount * i);
            it->dmgArea.center = temp;
            break;
        }
        case PSYCHO_AXE:
        {
            it->dmgArea.center = player.collider.center;
            break;
        }

        }
        activeAttack.push_back(it->dmgArea);
        }
    }

    // active attacks
    for (auto it = activeAttack.begin(); it != activeAttack.end(); ++it)
    {
        if (currentTime - it->start >= it->duration)
        {
            activeAttack.erase(it);
            --it;
            continue;
        }
        switch ((int)it->weaponID)
        {
        case CEO_TEARS:
            it->center += it->direction * 4;
            break;
        case AXE:
            it->center = player.collider.center;
            break;
        case SPIDER_COOKING:
            it->center = player.collider.center;
            break;
        case FAN_BEAM:
            it->center = player.collider.center;
            break;
        case BL_BOOK:
        {
            it->center += moved;
            circularMotion(it->center, player.collider.center, - 0.03);
            break;
        }
        case PSYCHO_AXE:
        {
            ++it->i;
            spiralMotion(it->center, player.collider.center, 0.01, currentTime - it->start);
            break;
        }
        }
        if (currentTime - it->lastFrameTime >= it->frameTime)
        {
            it->lastFrameTime = currentTime;
            ++it->currentFrame;
            if(it->currentFrame > it->frames) it->currentFrame = 0;
        }
        for (auto it2 = enemies.begin(); it2 != enemies.end(); ++it2)
        {
            if (it->hitID.find(it2->ID) != it->hitID.end())
            {
                it->hitID[it2->ID] -= timeStep;
                if (it->hitID[it2->ID] > 0)
                    continue;
                else
                    it->hitID.erase(it2->ID);
            }

            if(hitEnemy(*it, *it2, player, currentTime))
            {
                // Vector2f temp;
                // temp.x = it2->collider.center.x - camera.x;
                // temp.y = it2->collider.center.y - camera.y;
                dmgNumbers.push_back(DamageNumber{damageCal(*it, player),it2->collider.center, {255,255,255}});
            }

            if (it->hitLimit == 0)
            {
                activeAttack.erase(it);
                --it;
                break;
            }
        }
    }

    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        if (it->health <= 0)
        {
            dropItems.push_back(ExpDrop(it->expValue, it->collider.center));
            enemies.erase(it);
            --it;
        }
    }
    // enemy move
    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        it->move(player.collider.center);
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

        if (it->cd > 0)
        {
            it->cd -= timeStep;
        }
        else if (checkCircleCollision(player.collider, it->collider))
        {
            it->cd = EnemyCD;
            --player.health;
        //    Vector2f temp;
        //         temp.x = player.collider.center.x - camera.x;
        //         temp.y = player.collider.center.y - camera.y;
                dmgNumbers.push_back(DamageNumber{1,player.collider.center, {255,0,0}});
            // if (player.health <= 0)
            // {
            //     isOver = true;
            //     SDL_ResetKeyboard();
            // }
        }
    }

    // moving animation frame
    ++player.currentFrame;
    if ((player.currentFrame / 2 / player.state) > (player.state - 1))
    {
        player.currentFrame = 0;
    }

    for (auto itDrop = dropItems.begin(); itDrop != dropItems.end(); ++itDrop)
    {
        if (itDrop->pickedUp(player.collider.center))
        {
            player.currentExp += itDrop->expValue;
            dropItems.erase(itDrop);
            --itDrop;
        }
    }

    while (player.currentExp >= reqNextLevel)
    {
        player.currentExp -= reqNextLevel;
        reqNextLevel = pow(4 * (player.LEVEL + 1), 2.1) - pow(4 * player.LEVEL, 2.1);
        ++player.LEVEL;
    }
    // expTopBarSRC.w = player.currentExp / reqNextLevel * 648;
    // expTopBar.w = player.currentExp / reqNextLevel *(SCREEN_WIDTH +10);

    playerHUD.update(player, reqNextLevel);
}

void GameState::render(SDL_Renderer *renderer)
{

    // Center the camera over the player
    // camera.x = (player.collider.center.x + player.hitBox.w / 2) - SCREEN_WIDTH / 2;
    // camera.y = (player.collider.center.y + player.hitBox.h / 2) - SCREEN_HEIGHT / 2;
    camera.x = (player.collider.center.x) - SCREEN_WIDTH / 2;
    camera.y = (player.collider.center.y) - SCREEN_HEIGHT / 2;
    camera.w = SCREEN_WIDTH;
    camera.h = SCREEN_HEIGHT;

    player.render(renderer, player.currentFrame / 2 / player.state, camera.x, camera.y);

    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        it->render(renderer, it->currentFrame / 4 / 3, camera.x, camera.y);
    }

    // // sui.health.dst = {sui.hitBox.x, sui.hitBox.y + sui.hitBox.h, sui.hitBox.w, 6};
    // // inflictDamage(axe, deadbeat, sui, window.getRenderer(), camera.x, camera.y);

    for (auto it = dropItems.begin(); it != dropItems.end(); ++it)
    {
        // SDL_Rect dst{it->pos.x - camera.x, it->pos.y - camera.y, int(12 * 1.5), int(13 * 1.5)};
        // SDL_RenderCopy(renderer, ResourceManager::getInstance().getTexture(EXP_Drop, renderer), NULL, &dst);
        it->render(renderer, camera.x, camera.y);
    }

    for (auto it = activeAttack.begin(); it != activeAttack.end(); ++it)
    {
        // if (!it->isActive) continue;
        renderWeapon(renderer, *it, player, it->currentFrame, camera.x, camera.y);
    }

    for(auto it = dmgNumbers.begin(); it != dmgNumbers.end(); ++it)
    {
        SDL_Rect temp{it->dmgBox.x - camera.x, it->dmgBox.y - camera.y, it->dmgBox.w, it->dmgBox.h};
        dmgText.loadFromRenderedText(std::to_string(it->dmg), it->color, DMG_font, renderer);
        dmgText.render(renderer, &temp);
        std::cout << it->dmgBox.x << ' ' << it->dmgBox.y << '\n';
    }

    playerHUD.render(renderer, pause, isOver);


}

void GameState::reset()
{
    playerHUD.HUD_Timer.stop();
    player.health = 70;
    player.currentExp = 0;
    player.LEVEL = 1;
    reqNextLevel = 61;
    isOver = false;
}

void GameState::handleEvent()
{
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_ESCAPE] && !pause)
    {
        pause = true;
    }
    else if (currentKeyStates[SDL_SCANCODE_X] && pause)
    {
        pause = false;
    }

    if (currentKeyStates[SDL_SCANCODE_Z] && isOver)
    {
        reset();
        direct = Title;
        return;
    }

    direct = Room1;

    if (pause)
        return;

    player.handleEvent();
}
