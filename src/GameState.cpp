
#include "GameStates.hpp"

bool isOutsideOfView(Circle object, int camX, int camY)
{
    if ((object.center.x + object.radius - camX < 0 || object.center.x - object.radius - camX > SCREEN_WIDTH) && (object.center.y + object.radius - camY < 0 || object.center.y - object.radius - camY > SCREEN_HEIGHT))
        return true;

    return false;
}

void GameStates::weaponUpdate()
{
    if (choice == -1)
        return;
    switch (optionLevel[choice])
    {
    case 0:
    {
        switch ((int)optionKey[choice])
        {
        case ATK_UP:
            player.increaseATK(8);
            break;
        case SPD_UP:
            player.increaseSpeed(12);
            break;
        case HP_UP:
            player.increaseMaxHP(10);
            break;
        case HP_RECOVER:
            player.heal(20);
            break;
        }
        break;
    }
    case 1:
    {
        weapons.push_back(Weapon(optionKey[choice]));
        optionPool[optionKey[choice]] = 2;
        break;
    }
    default:
    {
        for (auto it = weapons.begin(); it != weapons.end(); ++it)
        {
            if (it->ID != optionKey[choice])
                continue;

            it->updateStats();

            if (it->level < 7)
            {
                optionPool[it->ID] = it->level + 1;
            }
            else
            {
                optionPool.erase(it->ID);
            }

            break;
        }
        break;
    }
    }
    choice = -1;
    optionKey.clear();
    optionLevel.clear();
    checkWeaponLimit();
}

GameStates::GameStates()
{
}

GameStates::~GameStates()
{
}

void GameStates::start()
{
    playerHUD.HUD_Timer.start();
    player.setPlayer(ID);
    optionPool = {{PSYCHO_AXE, 1}, {BL_BOOK, 1}, {SPIDER_COOKING, 1}, {ELITE_LAVA, 1}, {FAN_BEAM, 1}, {CEO_TEARS, 1}, {IDOL_SONG, 1}, {CUTTING_BOARD, 1}, {ATK_UP, 0}, {HP_UP, 0}, {HP_RECOVER, 0}, {SPD_UP, 0}};
    switch((int)ID)
    {
        case Suisei:
        weapons.push_back(Weapon(FALLING_BLOCKS));
        weapons.push_back(Weapon(AXE));
        optionPool[AXE] = 2;
        break;
        case Risu:
        weapons.push_back(Weapon(BIG_NUT));
        weapons.push_back(Weapon(NUTS));
        optionPool[NUTS] = 2;
        break;
        case Ayame:
        weapons.push_back(Weapon(SPIRIT));
        weapons.push_back(Weapon(DUAL_KATANA));
        weapons.push_back(Weapon(SPIRIT_FIRE));
        optionPool[DUAL_KATANA] = 2;
        break;
    }
    // weapons.push_back(Weapon(X_POTATO));
    reqNextLevel = 79;
    spawnCooldown = 0;
    specialCD = 0;
    EnemyCount = 0;
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    choice = -1;
    pause = false;
    isOver = false;
    leveledUp = false;
    player.collider.center = {SCREEN_WIDTH / 2 + 16, SCREEN_HEIGHT / 2 + 26};
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

void GameStates::loadMedia(SDL_Renderer *renderer)
{
    DMG_font = TTF_OpenFont(font_8bitPLus.c_str(), 24);
    playerHUD.initHUD(renderer, player.health);
}

Tabs GameStates::getDirect()
{
    Tabs temp = direct;
    direct = Room1;
    return temp;
}

bool GameStates::getPause()
{
    return pause;
}

void GameStates::updateSpawnPool(int minuteTimer, int secondTimer)
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
    if (minuteTimer == 10 && secondTimer == 0)
    {
        spawnPool.erase(BLOOM);
        spawnPool.erase(GLOOM);
    }
    if (minuteTimer == 5 && secondTimer == 55)
    {
        spawnPool.insert(DEAD_BATTER);
    }
    if (minuteTimer == 8 && secondTimer == 30)
    {
        spawnPool.erase(DEAD_BATTER);
    }
    if (minuteTimer == 8 && secondTimer == 30)
    {
        spawnPool.insert(MIKOP);
    }
    if (minuteTimer == 11 && secondTimer == 0)
    {
        spawnPool.erase(MIKOP);
    }

    if (minuteTimer == 11 && secondTimer == 0)
    {
        spawnPool.insert(HOSHIYOMI);
    }
    if (minuteTimer == 12 && secondTimer == 0)
    {
        spawnPool.erase(HOSHIYOMI);
    }

    if (minuteTimer == 12 && secondTimer == 0)
    {
        spawnPool.insert(SORATOMO);
    }

    if(minuteTimer == 15 && secondTimer == 0)
    {
        spawnPool.clear();
        spawnPool.insert(YAGOO);
    }

    spawnRate = (minuteTimer * 60 + secondTimer) / 25 + 10 * (minuteTimer == 11 ? secondTimer / 10:1) + 20 * (minuteTimer / 15) * (minuteTimer - 14);
}

void GameStates::bossSpawn(int minuteTimer, int secondTimer)
{
    if (minuteTimer == 8 && secondTimer == 0)
    {
        spawn(enemies, player.collider.center, FUBUZILLA, EnemyCount);
        ++EnemyCount;
        weapons.push_back(Weapon(FUBU_BEAM));
        boss = true;
    }
    if (minuteTimer >= 12 && secondTimer == 0)
    {
        enemies.clear();
        spawn(enemies, player.collider.center, A_CHAN, EnemyCount);
        ++EnemyCount;
        weapons.push_back(Weapon(BULLET1));
        weapons.push_back(Weapon(BULLET2));
        weapons.push_back(Weapon(BULLET3));
        weapons.push_back(Weapon(BULLET4));
        boss = true;
        finalBoss = true;
    }
}

void GameStates::checkWeaponLimit()
{
    int weaponCount = (int)weapons.size();
    for (auto it = weapons.begin(); it != weapons.end(); ++it)
    {
        if(Exception.find(it->ID) != Exception.end())
            --weaponCount;
    }
    if (weaponCount < MAX_WEAPON)
        return;
    for (auto it = optionPool.begin(); it != optionPool.end();)
    {
        if (it->second == 1)
            it = optionPool.erase(it);
        else
            ++it;
    }
}

void GameStates::update(float timeStep, bool &shake)
{
    if (pause || leveledUp)
    {
        Mix_VolumeMusic(20);
        playerHUD.HUD_Timer.pause();
        return;
    }
    else if (isOver || isWon)
    {
        Mix_HaltMusic();
        direct = End;
        return;
    }
    else
    {
        playerHUD.HUD_Timer.unpause();
        Mix_VolumeMusic(64);
    }

    if (shakeTime == 0)
        shake = false;
    if (shakeTime > 0)
        --shakeTime;
    if (player.health <= 0)
    {
        isOver = true;
        SDL_ResetKeyboard();
    }

    weaponUpdate();

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
        for (int i = 0; i < temp; ++i)
            ++it;
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
    player.update(timeStep);
    moved = player.collider.center - temp;
    if (specialCD > 0)
        specialCD -= timeStep;

    // create drops
    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        if(isOutsideOfView(it->collider, camera.x, camera.y)) it->maximumLifeTime -= timeStep;

        if(it->maximumLifeTime <= 0 && (it->ID != A_CHAN && it->ID != FUBUZILLA))
        {
            it = enemies.erase(it);
            --it;
            continue;
        }

        if (it->health > 0)
            continue;

        if(it->atk == -1)
        {
            weapons[2].initiateDmgArea(player.collider.center, player.arrowAngle, player.flip, 0, it->collider.center);
            activeAttack.push_back(weapons[2].dmgArea);
        }
        dropItems.push_back(ExpDrop(it->expValue, it->collider.center));
        if (it->type == FUBUZILLA)
        {
            boss = false;
            for (auto it2 = weapons.begin(); it2 != weapons.end(); ++it2)
            {
                if (it2->ID == FUBU_BEAM)
                {
                    weapons.erase(it2);
                    break;
                }
            }
        }
        else if (it->type == A_CHAN)
        {
            if(!endless) isWon = true;
            for (auto it = weapons.begin(); it != weapons.end(); ++it)
            {
                if (it->ID == BULLET1 || it->ID == BULLET2 || it->ID == BULLET4 || it->ID == BULLET3)
                {
                    weapons.erase(it);
                    --it;
                }
            }
        }
        it = enemies.erase(it);
        --it;
    }

    // enemy move

    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        it->update(player.collider.center, timeStep);
        if (it->type == FUBUZILLA)
        {
            temp = it->collider.center;
            temp2 = it->flip;
        }
        else if (it->type == A_CHAN)
        {
            temp = it->collider.center;
        }
    }

    // sweep and prune algorithm to optimize collision cheking
    sort(enemies.begin(), enemies.end(), compareByX);

    std::vector<std::vector<int>> possibleCollision;
    std::vector<int> active;
    float right = -1e9;
    for (int i = 0; i < (int)enemies.size(); ++i)
    {
        if (enemies[i].type == FUBUZILLA || enemies[i].type == A_CHAN)
        {
            bossIndex = i;
            continue;
        }
        if (enemies[i].collider.center.x - enemies[i].collider.radius > right)
        {
            if ((int)active.size() >= 2)
                possibleCollision.push_back(active);
            active.clear();
            right = enemies[i].collider.center.x + enemies[i].collider.radius;
        }
        active.push_back(i);
    }

    for (auto it = possibleCollision.begin(); it != possibleCollision.end(); ++it)
    {
        for (auto it2 = it->begin(); it2 != it->end(); ++it2)
        {
            for (auto it3 = it->begin(); it3 != it->end(); ++it3)
            {
                if (it2 == it3)
                    continue;
                if (checkCircleCollision(enemies[*it2].collider, enemies[*it3].collider))
                {
                    float dis = distance(enemies[*it2].collider.center, enemies[*it3].collider.center);
                    enemies[*it2].direction += (enemies[*it2].collider.center - enemies[*it3].collider.center) * (1.0f / (1.0f + dis * dis));
                }
            }
        }
    }

    // enemies attack
    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        if (it->cd > 0)
            continue;

        if (checkCircleCollision(player.collider, it->collider))
        {
            it->cd = EnemyCD;
            player.health -= it->atk;
            dmgNumbers.push_back(DamageNumber{it->atk, player.collider.center, {255, 0, 0}});
        }
    }

    // initiate attacks
    for (auto it = weapons.begin(); it != weapons.end(); ++it)
    {
        
        if(it->ID == BULLET3 || it->ID == BULLET4)
        {
            if(it->ID != enemies[bossIndex].attack)
            {
                continue;
            }
        }

        it->cooldown -= timeStep;
        it->timePassed += timeStep;

        while(it->count < it->dmgArea.attackCount && it->timePassed >= it->dmgArea.attackDelay)
        {
            if(it->ID == SPIRIT) weapons[1].setAttackInterval(1.67 / 5);

            Vector2f temp1{0, 0};
            if (it->ID == CEO_TEARS)
            {
                int index = rand() % (int)enemies.size();
                temp1 = vectorNormalize(enemies[index].collider.center - player.collider.center);
            }

            it->initiateDmgArea(player.collider.center, player.arrowAngle, player.flip, it->count, temp1);

            if (it->ID != FUBU_BEAM && it->ID != BULLET1 && it->ID != BULLET2 && it->ID != BULLET3 && it->ID != BULLET4)
            {
                activeAttack.push_back(it->dmgArea);
            }
            else if (it->ID == FUBU_BEAM)
            {
                it->dmgArea.center = temp;
                if (temp2 == SDL_FLIP_HORIZONTAL)
                    it->dmgArea.angle = 180;
                else
                    it->dmgArea.angle = 0;
                bossAttack.push_back(it->dmgArea);
            }
            else if (it->ID == BULLET1)
            {
                it->dmgArea.center = temp;
                it->dmgArea.direction = vectorNormalize(player.collider.center - it->dmgArea.center);
                bossAttack.push_back(it->dmgArea);
            }
            else if (it->ID == BULLET4)
            {
                it->dmgArea.center = temp;
                it->dmgArea.angle = it->count * 8;
                bossAttack.push_back(it->dmgArea);
                enemies[bossIndex].notMoving = true;
            }
            else if (it->ID == BULLET2)
            {
                // it->dmgArea.center = player.collider.center;
                it->dmgArea.center = temp;
                it->dmgArea.angle = it->count * 36;
                bossAttack.push_back(it->dmgArea);
            }
            else if (it->ID == BULLET3)
            {
                for(int i = 0; i < 10; ++i)
                {it->dmgArea.center = it->dmgArea.rotatingCenter = temp;
                it->dmgArea.angle = i * 72;
                it->dmgArea.count = i;
                bossAttack.push_back(it->dmgArea);
                }
                enemies[bossIndex].notMoving = true;
            }
            ++it->count;
            it->timePassed = 0;
        }

        if((it->ID == BULLET4 || it->ID == BULLET3) && it->count >= it->dmgArea.attackCount)
        {
            enemies[bossIndex].notMoving = false;
            // it->cooldown = it->timeBetweenAttacks; 
            // it->count = 0;
        }
        // if (it->cooldown > 0)
        //     continue;
        
        if(it->cooldown <= 0) 
        {
            if(it->ID == BULLET4 || it->ID == BULLET3)
            enemies[bossIndex].attack = (enemies[bossIndex].attack == BULLET3 ? BULLET4:BULLET3);
            it->cooldown = it->timeBetweenAttacks; 
            it->count = 0;
        }
    }

    // active attacks
    for (auto it = activeAttack.begin(); it != activeAttack.end(); ++it)
    {

        it->update(timeStep, player.collider.center, camera, shake, shakeTime);

        if (!it->isActive)
        {
            if(it->weaponID == SPIRIT) weapons[1].setAttackInterval(1.67);
            activeAttack.erase(it);
            --it;
            continue;
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

            if (it->hitEnemy(it2->collider, it2->ID))
            {
                it2->getKnockedBack(vectorNormalize(it2->collider.center - player.collider.center), it->knockbackTime, it->knockbackSpeed);
                it2->takeDamage(damageCal(*it, player));
                dmgNumbers.push_back(DamageNumber{damageCal(*it, player), it2->collider.center, {255, 255, 255}});
                if(it2->health <= 0 && it->weaponID == DUAL_KATANA && weapons[1].level == 7)
                {
                    if(rand() % 10 < 4) it2->atk = -1;
                }
            }
            if (it->hitLimit == 0)
            {
                activeAttack.erase(it);
                --it;
                break;
            }

        }
    }

    // boss active attacks
    for (auto it = bossAttack.begin(); it != bossAttack.end(); ++it)
    {

        it->update(timeStep, player.collider.center, camera, shake, shakeTime);

        if (!it->isActive)
        {
            bossAttack.erase(it);
            --it;
            continue;
        }
        switch ((int)it->weaponID)
        {
        case FUBU_BEAM:
        {
            it->center = temp;
            break;
        }
        case BULLET1:
        {
            it->center += it->direction * it->projectileSpeed;
            break;
        }
        case BULLET2:
        case BULLET4:
        {
            it->center.x += cosf((it->angle + 180.0f) / 180.0f * M_PI) * it->projectileSpeed;
            it->center.y += sinf((it->angle + 180.0f) / 180.0f * M_PI) * it->projectileSpeed;
            break;
        }
        case BULLET3:
        {
            int temp = (it->count < 5 ? -1 : 1);
            it->center.x -= temp * cosf((it->angle + 180.0f) / 180.0f * M_PI) * it->projectileSpeed;
            it->center.y -= temp * sinf((it->angle + 180.0f) / 180.0f * M_PI) * it->projectileSpeed;

            circularMotion(it->center, it->rotatingCenter, temp * it->projectileSpeed * 0.2f / 180.0f * M_PI);
            it->angle += temp * it->projectileSpeed * 0.2f;
            break;
        }
        }

        if (hitPlayer(*it, player))
            dmgNumbers.push_back(DamageNumber{(int)it->damage, player.collider.center, {255, 0, 0}});
        if (it->hitLimit == 0)
        {
            bossAttack.erase(it);
            --it;
            break;
        }
    }

    // drop pickup
    for (auto itDrop = dropItems.begin(); itDrop != dropItems.end(); ++itDrop)
    {
        if (isOutsideOfView(Circle{itDrop->pos, 13 * 1.5}, camera.x, camera.y))
        {
            itDrop->maximumLifeTime -= timeStep;
            if(itDrop->maximumLifeTime <= 0)
            {
                dropItems.erase(itDrop);
                --itDrop;
            }
            continue;
        }

        if (itDrop->pickedUp(player.collider.center))
        {
            switch(itDrop->ID)
            {
                case EXP:
                player.currentExp += itDrop->expValue;
                break;
                case FOOD:
                dmgNumbers.push_back(DamageNumber{(int)(player.maxHP * 0.2), player.collider.center, {0, 255, 0}});
                player.health = std::min(player.health + player.maxHP * 0.2, (double)player.maxHP);
                break;
            }
            itDrop = dropItems.erase(itDrop);
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
        }
        trace.clear();
        leveledUp = true;
        direct = Level_Up;
        Mix_VolumeMusic(20);
        playerHUD.HUD_Timer.pause();
        SDL_ResetKeyboard();
    }
    playerHUD.update(player, reqNextLevel, specialCD);
}

void GameStates::render(SDL_Renderer *renderer, bool shake)
{
    int shakeX{0}, shakeY{0};
    if (shake && !pause && !leveledUp)
    {
        shakeX = rand() % 10;
        shakeY = rand() % 10;
    }
    camera.x = (player.collider.center.x) - SCREEN_WIDTH / 2 + shakeX;
    camera.y = (player.collider.center.y) - SCREEN_HEIGHT / 2 + shakeY;

    for (auto it = activeAttack.begin(); it != activeAttack.end(); ++it)
    {
        if (it->weaponID != ELITE_LAVA)
            continue;
        it->render(renderer, player, camera.x, camera.y);
    }
    
    for (auto it = dropItems.begin(); it != dropItems.end(); ++it)
    {
        if (isOutsideOfView(Circle{it->pos, 13 * 1.5}, camera.x, camera.y))
            continue;
        it->render(renderer, camera.x, camera.y);
    }

    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        if (isOutsideOfView(it->collider, camera.x, camera.y))
            continue;
        it->render(renderer, it->currentFrame, camera.x, camera.y);
    }

    for (auto it = activeAttack.begin(); it != activeAttack.end(); ++it)
    {
        if (it->weaponID == ELITE_LAVA)
            continue;
        it->render(renderer, player, camera.x, camera.y);
    }

    player.render(renderer, player.currentFrame, camera.x, camera.y);

    for (auto it = bossAttack.begin(); it != bossAttack.end(); ++it)
    {
        it->render(renderer, player, camera.x, camera.y);
    }

    for (auto it = dmgNumbers.begin(); it != dmgNumbers.end(); ++it)
    {
        it->render(renderer, DMG_font, dmgText, camera.x, camera.y);
    }

    playerHUD.render(renderer, (int)player.playerID, pause, leveledUp, isOver, weapons);
}

void GameStates::reset()
{
    playerHUD.HUD_Timer.stop();
    optionKey.clear();
    optionLevel.clear();
    optionPool.clear();
    trace.clear();
    weapons.clear();
    dropItems.clear();
    activeAttack.clear();
    bossAttack.clear();
    spawnPool.clear();
    dmgNumbers.clear();
    enemies.clear();
    player.resetStats();
    boss = false;
}

void GameStates::handleEvent()
{
    if(!leveledUp && !(isOver || isWon)) direct = Room1;
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_ESCAPE] && !pause && !isOver)
    {
        pause = true;
    }
    else if (currentKeyStates[SDL_SCANCODE_X] && specialCD <= 0)
    {
        specialCD = player.specialCD;
        weapons.front().count = 0;
    }

    playerHUD.handleEvents(pause, leveledUp, direct, choice);

    if (pause)
        return;

    player.handleEvent();
}

bool GameStates::getOver()
{
    return isOver;
}