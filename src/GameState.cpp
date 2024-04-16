
#include "GameStates.hpp"

bool isOutsideOfView(Circle object, int camX, int camY)
{
    if ((object.center.x + object.radius - camX < 0 || object.center.x - object.radius - camX > SCREEN_WIDTH) && (object.center.y + object.radius - camY < 0 || object.center.y - object.radius - camY > SCREEN_HEIGHT))
        return true;

    return false;
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
    optionPool = {{PSYCHO_AXE, 1}, {BL_BOOK, 1}, {SPIDER_COOKING, 1}, {ELITE_LAVA, 1}, {FAN_BEAM, 1}, {CEO_TEARS, 1}, {AXE, 2}, {IDOL_SONG,1}, {CUTTING_BOARD, 1}, {ATK_UP, 0}, {HP_UP, 0}, {HP_RECOVER, 0}, {SPD_UP, 0}};
    weapons.push_back(Weapon(AXE));
    // player.health = player.maxHP;
    // player.currentExp = 0;
    // player.LEVEL = 1;
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
    return direct;
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
    if (minuteTimer == 11 && secondTimer == 0)
    {
        spawnPool.erase(BLOOM);
        spawnPool.erase(GLOOM);
    }

    spawnRate = (minuteTimer * 60 + secondTimer) / 20 + 10;
}

void GameStates::bossSpawn(int minuteTimer, int secondTimer)
{
    if (minuteTimer == 1 && secondTimer == 0)
    {
        spawn(enemies, player.collider.center, FUBUZILLA, EnemyCount);
        ++EnemyCount;
        weapons.push_back(Weapon(FUBU_BEAM));
        boss = true;
    }
}

void GameStates::checkWeaponLimit()
{
    int weaponCount = (int)weapons.size();
    for(auto it = weapons.begin(); it != weapons.end(); ++it)
    {
        if(it->ID == FUBU_BEAM || it->ID == FALLING_BLOCKS) --weaponCount;
    }
    if(weaponCount < MAX_WEAPON) return;
    for(auto it = optionPool.begin(); it != optionPool.end();)
    {
        if(it->second == 1) 
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
    else if (isOver)
    {
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

    if (choice != -1)
    {
        if(optionLevel[choice] == 0)
        {
            switch((int)optionKey[choice])
            {
                case ATK_UP: player.increaseATK(8); break;
                case SPD_UP: player.increaseSpeed(12); break;
                case HP_UP: player.increaseMaxHP(10); break;
                case HP_RECOVER: player.heal(20); break;
            }
        }
        else if (optionLevel[choice] == 1)
        {
            weapons.push_back(Weapon(optionKey[choice]));
            optionPool[optionKey[choice]] = 2;
        }
        else
        {
            for (auto it = weapons.begin(); it != weapons.end(); ++it)
            {
                if (it->ID == optionKey[choice])
                {
                    it->updateStats();
                    // choice = -1;
                    if (it->level < 7)
                    {
                        // optionPool.insert({it->ID, it->level});
                        optionPool[it->ID] = it->level + 1;
                    }
                    else
                        optionPool.erase(it->ID);
                    break;
                }
            }
        }
        choice = -1;
        optionKey.clear();
        optionLevel.clear();
        checkWeaponLimit();

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

        it->move(player.collider.center, timeStep);

        if (it->type == FUBUZILLA)
        {
            temp = it->collider.center;
            temp2 = it->flip;
        }
    }

    sort(enemies.begin(), enemies.end(), compareByX);

    std::vector<std::vector<int>> possibleCollision;
    std::vector<int> active;
    float right = -1e9;
    for (int i = 0; i < (int)enemies.size(); ++i)
    {
        if (enemies[i].type == FUBUZILLA)
            continue;
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
                    // collisionEvent(enemies[*it2].collider, enemies[*it3].collider);
                }
            }
        }
    }

    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        if (it->cd > 0)
        {
            it->cd -= timeStep;
        }
        else if (checkCircleCollision(player.collider, it->collider))
        {
            it->cd = EnemyCD;
            player.health -= it->atk;
            dmgNumbers.push_back(DamageNumber{it->atk, player.collider.center, {255, 0, 0}});
        }
    }

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
                it->dmgArea.center = Vector2f{(float)(randomInt(-5, 5) * 98), -SCREEN_HEIGHT / 2} + player.collider.center;
                it->dmgArea.fallTime = (rand() % 6 + 1) * 0.12;
                it->dmgArea.count = rand() % 12;
                break;
            }
            case CUTTING_BOARD:
            {
                it->dmgArea.center = player.collider.center;
                switch(i)
                {
                    case 0: it->dmgArea.angle = player.arrowAngle; break;
                    case 1: it->dmgArea.angle = player.arrowAngle + 90; break;
                    case 2: it->dmgArea.angle = player.arrowAngle - 90; break;
                }
                break;
            }
            case X_POTATO:
            {
                it->dmgArea.center = player.collider.center;
                Vector2f temp = {randomFloat(-1,1), randomFloat(-1,1)};
                while(temp.x == 0 && temp.y == 0)
                {
                    temp = {randomFloat(-1,1), randomFloat(-1,1)};
                }
                it->dmgArea.direction = vectorNormalize(temp);
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

            it->center.y += temp * it->projectileSpeed;
            it->center.x = temp * sin((2.5 - it->duration) * 10) * 100 * it->projectileSpeed + it->direction.x;

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
            break;
        }
        case CUTTING_BOARD:
        {
            if(it->fallTime > 0)
            {
                it->center.x += cosf((it->angle + 180.0f) / 180.0f * M_PI) * it->projectileSpeed;
                it->center.y += sinf((it->angle + 180.0f) / 180.0f * M_PI) * it->projectileSpeed;
                it->fallTime -= timeStep;
            }
            break;
        }
        case X_POTATO:
        {
            if(it->fallTime > 0)
            {
                it->center += it->direction * it->projectileSpeed;
                it->angle += 20;
                circleBounce(Circle{it->center, it->radius}, it->direction, camera);
                it->fallTime -= timeStep;
                if(it->fallTime <= 0)
                {
                    it->explode();
                }
            }
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
                    it2->getKnockedBack(vectorNormalize(it2->collider.center - player.collider.center), it->knockbackTime, it->knockbackSpeed);
                    it2->takeDamage(damageCal(*it, player));
                    dmgNumbers.push_back(DamageNumber{damageCal(*it, player), it2->collider.center, {255, 255, 255}});
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
            if (hitPlayer(*it, player))
                dmgNumbers.push_back(DamageNumber{15, player.collider.center, {255, 0, 0}});
        }
    }

    // create drops

    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        if (it->health > 0) continue;
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
        it = enemies.erase(it);
        --it;
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
            for (int j = 0; j < temp; ++j) ++it;
            optionKey.push_back(it->first);
            optionLevel.push_back(it->second);
            playerHUD.tabs_levelup.getResource(it->first,it->second,i);
        }
        trace.clear();
        leveledUp = true;
        SDL_ResetKeyboard();
    }

    playerHUD.update(player, reqNextLevel, specialCD);
}

void GameStates::render(SDL_Renderer *renderer, bool shake)
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
        if (isOutsideOfView(Circle{it->pos, 13 * 1.5}, camera.x, camera.y))
            continue;
        it->render(renderer, camera.x, camera.y);
    }

    for (auto it = activeAttack.begin(); it != activeAttack.end(); ++it)
    {
        if(it->weaponID != ELITE_LAVA) continue;
        it->render(renderer, player, camera.x, camera.y);
        // renderWeapon(renderer, *it, player, it->currentFrame, camera.x, camera.y);
    }

    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        if (isOutsideOfView(it->collider, camera.x, camera.y))
            continue;
        it->render(renderer, it->currentFrame, camera.x, camera.y);
    }

    for (auto it = activeAttack.begin(); it != activeAttack.end(); ++it)
    {
        if(it->weaponID == ELITE_LAVA) continue;
        it->render(renderer, player, camera.x, camera.y);
    }

    player.render(renderer, player.currentFrame / 2 / player.state, camera.x, camera.y);

    for (auto it = dmgNumbers.begin(); it != dmgNumbers.end(); ++it)
    {
        SDL_Rect temp{it->dmgBox.x - camera.x, it->dmgBox.y - camera.y, it->dmgBox.w, it->dmgBox.h};
        dmgText.loadFromRenderedText(std::to_string(it->dmg), it->color, DMG_font, renderer);
        dmgText.render(renderer, &temp);
    }

    playerHUD.render(renderer, pause, leveledUp, isOver, weapons);
}

void GameStates::reset()
{
    playerHUD.HUD_Timer.stop();
    isOver = false;
    optionKey.clear();
    optionLevel.clear();
    optionPool.clear();
    trace.clear();
    weapons.clear();
    dropItems.clear();
    activeAttack.clear();
    spawnPool.clear();
    dmgNumbers.clear();
    enemies.clear();
    player.resetStats();
}

void GameStates::handleEvent()
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

    if (currentKeyStates[SDL_SCANCODE_ESCAPE] && isOver)
    {
        reset();
        direct = Title;
        SDL_ResetKeyboard();
        return;
    }

    if (pause)
        return;

    player.handleEvent();
}
