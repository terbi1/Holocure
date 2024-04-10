
#include "GameState.hpp"


bool isOutsideOfView(Circle object, int camX, int camY)
{
    if((object.center.x + object.radius - camX < 0 || object.center.x - object.radius - camX > SCREEN_WIDTH) && (object.center.y + object.radius - camY < 0 || object.center.y - object.radius - camY > SCREEN_HEIGHT)) return true;

    return false;
}

GameState::GameState()
{
}

GameState::~GameState()
{
}

void GameState::loadMedia(SDL_Renderer *renderer)
{
    DMG_font = TTF_OpenFont(font_8bitPLus.c_str(), 24);

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
    if (minuteTimer == 10 && secondTimer == 0)
    {
        spawn(enemies, player.collider.center, FUBUZILLA, EnemyCount);
        ++EnemyCount;
        weapons.push_back(Weapon(FUBU_BEAM));
        boss = true;
    }
}

void GameState::update(float timeStep, bool &shake)
{
    if (shakeTime == 0)
        shake = false;
    if (shakeTime > 0)
        --shakeTime;
    if (player.health <= 0)
    {
        isOver = true;
        SDL_ResetKeyboard();
    }

    if (pause || leveledUp)
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

    if (choice != -1)
    {
        for (auto it = weapons.begin(); it != weapons.end(); ++it)
        {
            if (it->ID == optionKey[choice])
            {
                it->updateStats();
                choice = -1;
                if (it->level < 7)
                {
                    // optionPool.insert({it->ID, it->level});
                    optionPool[it->ID] = it->level;
                }
                else
                    optionPool.erase(it->ID);
                break;
            }
        }
        if (choice != -1)
        {
            weapons.push_back(Weapon(optionKey[choice]));
            optionPool.insert({optionKey[choice], 1});
            choice = -1;
        }
        // ++optionPool[optionKey[choice]];
        optionKey.clear();
        optionLevel.clear();
    }
    // spawn enemies

    if (!boss)
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
        for (int i = 0; i < temp; ++i) ++it;
        for (int i = 0; i < spawnRate; ++i)
        {
            spawn(enemies, player.collider.center, *it, EnemyCount);
            ++EnemyCount;
            spawnCooldown = SPAWN_CD;
        }
    }

    // dmg numbers
    for (auto it = dmgNumbers.begin(); it != dmgNumbers.end(); ++it)
    {
        if (it->duration <= 0)
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
    if (specialCD > 0)
        specialCD -= timeStep;

    // enemy move

    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        it->timePassed += timeStep;
        it->frameTime -= timeStep;

        if (it->frameTime <= 0)
        {
            ++it->currentFrame;
            if (it->currentFrame > it->frames)
                it->currentFrame = 0;
            it->frameTime = enemyFrameTime;
        }

        it->move(player.collider.center);
        
        // for (auto it2 = enemies.begin(); it2 != enemies.end(); ++it2)
        // {
        //     if (it == it2) continue;
        //     if (checkCircleCollision(it->collider, it2->collider))
        //     {
        //         collisionEvent(it->collider, it2->collider);
        //     }
        // }

        // if (it->cd > 0)
        // {
        //     it->cd -= timeStep;
        // }
        // else if (checkCircleCollision(player.collider, it->collider))
        // {
        //     it->cd = EnemyCD;
        //     // player.health -= it->atk;
        //     dmgNumbers.push_back(DamageNumber{it->atk, player.collider.center, {255, 0, 0}});
        // }

        // if (it->type == FUBUZILLA)
        // {
        //     temp = it->collider.center;
        //     temp2 = it->flip;
        // }
    }

    sort(enemies.begin(), enemies.end(), compareByX);

    std::vector<std::vector<int>> possibleCollision;
    std::vector<int> active;
    float right = -1e9;
    for(int i = 0; i < (int)enemies.size(); ++i)
    {
        if(enemies[i].collider.center.x - enemies[i].collider.radius > right)
        {
            if((int)active.size() >= 2) possibleCollision.push_back(active);
            active.clear();
            right = enemies[i].collider.center.x + enemies[i].collider.radius;
        }
        active.push_back(i);
    }
    for(auto it = possibleCollision.begin(); it != possibleCollision.end(); ++it)
    {
        for(auto it2 = it->begin(); it2 != it->end(); ++it2)
        {
            for (auto it3 = it->begin(); it3 != it->end(); ++it3)
            {
                if (it2 == it3) continue;
                if (checkCircleCollision(enemies[*it2].collider, enemies[*it3].collider))
                {
                    float dis = distance(enemies[*it2].collider.center, enemies[*it3].collider.center);
                    // enemies[*it2].direction.x -= 1.0f / ( 1.0f + dis * dis * dis);
                    // enemies[*it2].direction.y -= 1.0f / ( 1.0f + dis * dis * dis);
                    enemies[*it2].direction += (enemies[*it2].collider.center - enemies[*it3].collider.center) * (1.0f / ( 1.0f + dis * dis));
                    // collisionEvent(enemies[*it2].collider, enemies[*it3].collider);
                }
            }
        }
    }
    // for(int i = 0; i < (int)enemies.size(); ++i)
    // {
    //     // it->timePassed += timeStep;
    //     enemies[i].frameTime -= timeStep;

    //     if (enemies[i].frameTime <= 0)
    //     {
    //         ++enemies[i].currentFrame;
    //         if (enemies[i].currentFrame > enemies[i].frames)
    //             enemies[i].currentFrame = 0;
    //         enemies[i].frameTime = enemyFrameTime;
    //     }

    //     enemies[i].move(player.collider.center);
    // }

    // sort(enemies.begin(), enemies.end(), compareByX);

    // for(int i = 0; i < (int)enemies.size(); ++i)
    // {
    //     if(i == (int)enemies.size() - 1) break;
    //     if(checkCircleCollision(enemies[i].collider, enemies[i+1].collider))
    //     {
    //         collisionEvent(enemies[i].collider, enemies[i+1].collider);
    //     }
    // }
    // for(int i = 0; i < 64; ++i)
    // {
    //     for(int j = 0; j < 36; ++j)
    //     {
    //         for(auto it = WORLD_CHUNKS[i][j].begin(); it != WORLD_CHUNKS[i][j].end(); ++it)
    //         {
    //             for(auto it2 = it; it2 != WORLD_CHUNKS[i][j].end(); ++it2)
    //             {
    //                 if(checkCircleCollision(enemies[*it].collider, enemies[*it2].collider))
    //             {
    //                 collisionEvent(enemies[*it].collider, enemies[*it2].collider);
    //             }
    //             }
    //         }
    //     }
    // }

    // for(int i = 0; i < 64; ++i)
    // {
    //     for(int j = 0; j < 36; ++j)
    //     {
    //         WORLD_CHUNKS[i][j].clear();
    //     }
    // }
    // initiate attacks
    for (auto it = weapons.begin(); it != weapons.end(); ++it)
    {
        it->cooldown -= timeStep;

        if (it->cooldown > 0)
            continue;

        it->cooldown = it->timeBetweenAttacks;

        for (int i = 0; i < it->dmgArea.attackCount; ++i)
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
                if (player.flip == SDL_FLIP_HORIZONTAL)
                    it->dmgArea.angle = 180 + 180 * i;
                else
                    it->dmgArea.angle = 0 + 180 * i;
                break;
            }
            case BL_BOOK:
            {
                Vector2f temp{player.collider.center.x, player.collider.center.y - it->dmgArea.radius};
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
                if (temp2 == SDL_FLIP_HORIZONTAL)
                    it->dmgArea.angle = 180;
                else
                    it->dmgArea.angle = 0;
                break;
            }
            case ELITE_LAVA:
            {
                it->dmgArea.center = Vector2f{randomFloat(-SCREEN_WIDTH / 3, SCREEN_WIDTH / 3), randomFloat(-SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3)} + player.collider.center;
                break;
            }
            case FALLING_BLOCKS:
            {
                it->specialDuration[1] -= it->timeBetweenAttacks;
                if (it->specialDuration[1] <= 0)
                {
                    it->specialDuration[1] = it->specialDuration[0];
                    weapons.erase(it);
                    --it;
                    continue;
                }
                it->dmgArea.center = Vector2f{randomInt(-5, 5) * 98, -SCREEN_HEIGHT / 2} + player.collider.center;
                it->dmgArea.fallTime = (rand() % 6 + 1) * 0.12;
                it->dmgArea.count = rand() % 12;
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

        if (it->duration <= 0)
        {
            activeAttack.erase(it);
            --it;
            continue;
        }

        if (it->frameTime <= 0)
        {
            it->frameTime = spriteFrameTime;
            ++it->currentFrame;
            if (it->currentFrame > it->frames)
                it->currentFrame = 0;
        }

        switch ((int)it->weaponID)
        {
        case AXE:
            it->center = player.collider.center;
            break;
        case CEO_TEARS:
            it->center += it->direction * it->projectileSpeed;
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
            circularMotion(it->center, player.collider.center, -0.01 * it->projectileSpeed);
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
            if (it->count == 0)
                temp = 1;
            else
                temp = -1;

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
        case FALLING_BLOCKS:
        {
            // std::cout << it->fallTime << '\n';
            if (it->fallTime > 0)
            {
                it->center.y += 8;
                it->fallTime -= timeStep;
                if (it->fallTime <= 0)
                {
                    shake = true;
                    shakeTime = 30;
                }
            }
            // else if(it->fallTime <= 0 && it->fallTime > -0.01)
            // {
            //     shake = true;
            // }
            break;
        }
        }

        if (it->ofPlayer)
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

                if (hitEnemy(*it, it2->collider, it2->health, it2->isHit, it2->ID, player))
                {
                    dmgNumbers.push_back(DamageNumber{damageCal(*it, player), it2->collider.center, {255, 255, 255}});
                }

                if (it->hitLimit == 0)
                {
                    // std::cout << 1;
                    activeAttack.erase(it);
                    --it;
                    break;
                }
            }
        }
        else
        {
            if (hitPlayer(*it, player))
                dmgNumbers.push_back(DamageNumber{15, player.collider.center, {255, 0, 0}});
        }
    }

    // create drops
    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        if (it->health <= 0)
        {
            dropItems.push_back(ExpDrop(it->expValue, it->collider.center));
            if (it->type == FUBUZILLA)
            {
                for (auto it2 = weapons.begin(); it2 != weapons.end(); ++it2)
                {
                    if (it2->ID == FUBU_BEAM)
                    {
                        weapons.erase(it2);
                        break;
                    }
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

    // level up
    if (player.currentExp >= reqNextLevel)
    {
        player.currentExp -= reqNextLevel;
        ++player.LEVEL;
        reqNextLevel = pow(4.0 * (player.LEVEL + 1.0), 2.1) - pow(4.0 * player.LEVEL, 2.1);
        for (int i = 0; i < 4; ++i)
        {
            int temp = rand() % (int)optionPool.size();
            if (trace.find(temp) != trace.end())
            {
                --i;
                continue;
            }
            trace.insert(temp);
            std::unordered_map<WEAPON_ID, int>::iterator it;
            it = optionPool.begin();
            for (int j = 0; j < temp; ++j)
                ++it;
            optionKey.push_back(it->first);
            optionLevel.push_back(it->second);
            switch (it->first)
            {
            case PSYCHO_AXE:
                playerHUD.tabs_levelup.iconTexture[i] = PsychoAxe_Icon;
                break;
            case SPIDER_COOKING:
                playerHUD.tabs_levelup.iconTexture[i] = SpiderCooking_Icon;
                break;
            case BL_BOOK:
                playerHUD.tabs_levelup.iconTexture[i] = BLBook_Icon;
                break;
            case ELITE_LAVA:
                playerHUD.tabs_levelup.iconTexture[i] = LavaPool_Icon;
                break;
            case FAN_BEAM:
                playerHUD.tabs_levelup.iconTexture[i] = FanBeam_Icon;
                break;
            case CEO_TEARS:
                playerHUD.tabs_levelup.iconTexture[i] = CEOTears_Icon;
                break;
            }
        }
        trace.clear();
        leveledUp = true;
        SDL_ResetKeyboard();
    }
    // expTopBarSRC.w = player.currentExp / reqNextLevel * 648;
    // expTopBar.w = player.currentExp / reqNextLevel *(SCREEN_WIDTH +10);

    playerHUD.update(player, reqNextLevel, specialCD);
}

void GameState::render(SDL_Renderer *renderer, bool shake)
{
    int shakeX{0}, shakeY{0};
    if (shake)
    {
        shakeX = rand() % 10;
        shakeY = rand() % 10;
    }
    camera.x = (player.collider.center.x) - SCREEN_WIDTH / 2 + shakeX;
    camera.y = (player.collider.center.y) - SCREEN_HEIGHT / 2 + shakeY;
    camera.w = SCREEN_WIDTH;
    camera.h = SCREEN_HEIGHT;

    for (auto it = dropItems.begin(); it != dropItems.end(); ++it)
    {
        if(isOutsideOfView(Circle{it->pos, 13 * 1.5}, camera.x, camera.y)) continue;
        it->render(renderer, camera.x, camera.y);
    }

    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        if(isOutsideOfView(it->collider, camera.x, camera.y)) continue;
        it->render(renderer, it->currentFrame, camera.x, camera.y);
    }

    for (auto it = activeAttack.begin(); it != activeAttack.end(); ++it)
    {
        renderWeapon(renderer, *it, player, it->currentFrame, camera.x, camera.y);
    }

    player.render(renderer, player.currentFrame / 2 / player.state, camera.x, camera.y);

    for (auto it = dmgNumbers.begin(); it != dmgNumbers.end(); ++it)
    {
        SDL_Rect temp{it->dmgBox.x - camera.x, it->dmgBox.y - camera.y, it->dmgBox.w, it->dmgBox.h};
        dmgText.loadFromRenderedText(std::to_string(it->dmg), it->color, DMG_font, renderer);
        dmgText.render(renderer, &temp);
    }

    playerHUD.render(renderer, pause, leveledUp, isOver);
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
    else if (currentKeyStates[SDL_SCANCODE_X] && specialCD <= 0)
    {
        weapons.push_back(Weapon(FALLING_BLOCKS));
        specialCD = player.specialCD;
    }
    // else if (currentKeyStates[SDL_SCANCODE_X] && pause)
    // {
    //     pause = false;
    // }
    playerHUD.handleEvents(pause, leveledUp, direct, choice);

    if (currentKeyStates[SDL_SCANCODE_Z] && isOver)
    {
        reset();
        direct = Title;
        return;
    }

    if (pause)
        return;

    player.handleEvent();
}
