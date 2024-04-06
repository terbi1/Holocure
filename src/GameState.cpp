
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

    weapons.push_back(Weapon(AXE));
    // weapons.push_back(Weapon(SPIDER_COOKING));
    // weapons.push_back(Weapon(CEO_TEARS));
    // weapons.push_back(Weapon(FAN_BEAM));
    // weapons.push_back(Weapon(BL_BOOK));
    // weapons.push_back(Weapon(PSYCHO_AXE));
    // weapons.push_back(Weapon(IDOL_SONG));
    // weapons.push_back(Weapon(ELITE_LAVA));

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
        
    if (minuteTimer == 5 && secondTimer == 0)
        spawnPool.insert(DARK_SHRIMP);
    if (minuteTimer == 8 && secondTimer == 30)
        spawnPool.erase(DARK_SHRIMP);

    if (minuteTimer == 5 && secondTimer == 0)
    {
        spawnPool.insert(BLOOM);
        spawnPool.insert(GLOOM);
    }
    if (minuteTimer == 11 && secondTimer == 0)
    {
        spawnPool.erase(BLOOM);
        spawnPool.erase(GLOOM);
    }

    spawnRate = (minuteTimer * 60 + secondTimer) / 20 + 10;
}

void GameState::bossSpawn(int minuteTimer, int secondTimer)
{
    if(minuteTimer == 1 && secondTimer == 0)
    {
        spawn(enemies, player.collider.center, FUBUZILLA, EnemyCount);
        ++EnemyCount;
        weapons.push_back(Weapon(FUBU_BEAM));
        boss = true;
    }
}

void GameState::update(float timeStep)
{
    if (player.health <= 0)
    {
        isOver = true;
        SDL_ResetKeyboard();
    }

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

    if(!boss)
    {
        bossSpawn(playerHUD.HUD_Timer.getTicks(Minute), playerHUD.HUD_Timer.getTicks(Second) - 60 * playerHUD.HUD_Timer.getTicks(Minute));
        
    }

    updateSpawnPool(playerHUD.HUD_Timer.getTicks(Minute), playerHUD.HUD_Timer.getTicks(Second) - 60 * playerHUD.HUD_Timer.getTicks(Minute));

    spawnCooldown -= timeStep;
    if (spawnCooldown <= 0)
    {
        int temp = rand() % (int)spawnPool.size();
        std::unordered_set<ENEMY_TYPE>::iterator it;
        it = spawnPool.begin();
        for (int i = 0; i < temp; ++i)
            ++it;
        for (int i = 0; i < spawnRate; ++i)
        {
            
            spawn(enemies, player.collider.center, *it, EnemyCount);
            ++EnemyCount;
            spawnCooldown = SPAWN_CD;
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
    SDL_RendererFlip temp2;
    player.move();
    moved = player.collider.center - temp;

    // enemy move
    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        // it->timePassed += timeStep;
        it->frameTime -= timeStep;

        if(it->frameTime <= 0)
        {
            ++it->currentFrame;
            if(it->currentFrame > it->frames) it->currentFrame = 0;
            it->frameTime = enemyFrameTime;
        }

        it->move(player.collider.center);
        
        for (auto it2 = enemies.begin(); it2 != enemies.end(); ++it2)
        {
            if (it == it2)
                continue;
            if (checkCircleCollision(it->collider, it2->collider))
            {
                collisionEvent(it->collider, it2->collider);
            }
        }

        if (it->cd > 0)
        {
            it->cd -= timeStep;
        }
        else if (checkCircleCollision(player.collider, it->collider))
        {
            it->cd = EnemyCD;
            player.health -= it->atk;
            dmgNumbers.push_back(DamageNumber{it->atk,player.collider.center, {255,0,0}});
            
        }

        if(it->type == FUBUZILLA)
        {
            temp = it->collider.center;
            temp2 = it->flip;
        }
    }

    // initiate attacks
    for (auto it = weapons.begin(); it != weapons.end(); ++it)
    {
        it->cooldown -= timeStep;

        if(it->cooldown > 0) continue;

        it->cooldown = it->timeBetweenAttacks;

        for(int i = 0; i < it->dmgArea.attackCount; ++i)
        {
            switch ((int)it->ID)
        {
        case AXE:
        {
            it->dmgArea.center = player.collider.center;
            it->dmgArea.angle = player.arrowAngle;
            // it->dmgArea.flip = player.flip;
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
            if(player.flip == SDL_FLIP_HORIZONTAL) it->dmgArea.angle = 180;
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
            it->dmgArea.rotatingCenter = player.collider.center;
            break;
        }
        case IDOL_SONG:
        {
            it->dmgArea.center = it->dmgArea.direction = player.collider.center;
            it->dmgArea.count = i;
            it->dmgArea.angle = player.arrowAngle;
            break;
        }
        case FUBU_BEAM:
        {
            it->dmgArea.center = temp;
            if(temp2 == SDL_FLIP_HORIZONTAL) it->dmgArea.angle = 180;
            else it->dmgArea.angle = 0;
            break;
        }
        case ELITE_LAVA:
        {
            it->dmgArea.center = Vector2f{randomFloat( - SCREEN_WIDTH / 3, SCREEN_WIDTH / 3), randomFloat(- SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3)} + player.collider.center;
            break;
        }
        }
        activeAttack.push_back(it->dmgArea);
        }
    }

    // active attacks
    for (auto it = activeAttack.begin(); it != activeAttack.end(); ++it)
    {
        it->frameTime -= timeStep;
        it->duration -= timeStep;

        if(it->duration <= 0)
        {
            activeAttack.erase(it);
            --it;
            continue;
        }
        
        if(it->frameTime <= 0)
        {
            it->frameTime = spriteFrameTime;
            ++it->currentFrame;
            if(it->currentFrame > it->frames) it->currentFrame = 0;
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
            it->timePassed += timeStep;
            spiralMotion(it->center, it->rotatingCenter, 0.01, it->timePassed);
            break;
        }
        case IDOL_SONG:
        {
            int temp;
            if(it->count == 0) temp = 1;
            else temp = -1;

            it->center.y += temp;
            it->center.x = temp * sin((2.5 - it->duration) * 10) * 100 + it->direction.x;
            
            break;
        }
        case FUBU_BEAM:
        {
            it->center = temp;
            break;
        }
        case ELITE_LAVA:
        {
            break;
        }
        }

        if(it->ofPlayer)
        {
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

            if(hitEnemy(*it, it2->collider, it2->health, it2->isHit, it2->ID, player))
            {

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
        else
        {
            if(hitPlayer(*it, player))
            dmgNumbers.push_back(DamageNumber{15,player.collider.center, {255,0,0}});
        }
    }

    // create drops
    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        if (it->health <= 0)
        {
            dropItems.push_back(ExpDrop(it->expValue, it->collider.center));
            if(it -> type == FUBUZILLA)
            {
                for(auto it2 = weapons.begin(); it2 != weapons.end(); ++it2)
                {
                    if(it2->ID == FUBU_BEAM) {weapons.erase(it2); break;}
                    
                }
            }
            enemies.erase(it);
            --it;
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
        ++weapons[0].level;
        weapons[0].updateStats();
    }
    // expTopBarSRC.w = player.currentExp / reqNextLevel * 648;
    // expTopBar.w = player.currentExp / reqNextLevel *(SCREEN_WIDTH +10);

    playerHUD.update(player, reqNextLevel);
}

void GameState::render(SDL_Renderer *renderer)
{

    camera.x = (player.collider.center.x) - SCREEN_WIDTH / 2;
    camera.y = (player.collider.center.y) - SCREEN_HEIGHT / 2;
    camera.w = SCREEN_WIDTH;
    camera.h = SCREEN_HEIGHT;


    for (auto it = dropItems.begin(); it != dropItems.end(); ++it)
    {
        it->render(renderer, camera.x, camera.y);
    }

    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        it->render(renderer, it->currentFrame, camera.x, camera.y);
    }


    for (auto it = activeAttack.begin(); it != activeAttack.end(); ++it)
    {
        renderWeapon(renderer, *it, player, it->currentFrame, camera.x, camera.y);
    }

    player.render(renderer, player.currentFrame / 2 / player.state, camera.x, camera.y);

    for(auto it = dmgNumbers.begin(); it != dmgNumbers.end(); ++it)
    {
        SDL_Rect temp{it->dmgBox.x - camera.x, it->dmgBox.y - camera.y, it->dmgBox.w, it->dmgBox.h};
        dmgText.loadFromRenderedText(std::to_string(it->dmg), it->color, DMG_font, renderer);
        dmgText.render(renderer, &temp);
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

    if (currentKeyStates[SDL_SCANCODE_ESCAPE] && !pause && !isOver)
    {
        pause = true;
    }
    // else if (currentKeyStates[SDL_SCANCODE_X] && pause)
    // {
    //     pause = false;
    // }
    playerHUD.handleEvents(pause, direct);

    if (currentKeyStates[SDL_SCANCODE_Z] && isOver)
    {
        reset();
        direct = Title;
        return;
    }

    // direct = Room1;

    if (pause)
        return;

    player.handleEvent();
}
