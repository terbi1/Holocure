#include "weapon.hpp"

DamagingArea::DamagingArea()
{
}

void DamagingArea::update(float timeStep, Vector2f player_center, SDL_Rect camera, bool &shake, int &shakeTime)
{
    frameTime -= timeStep;
    duration -= timeStep;

    if (duration <= 0)
    {
        isActive = false;
        return;
    }

    if (frameTime <= 0)
    {
        frameTime = spriteFrameTime;
        currentFrame = (currentFrame + 1) % (frames + 1);
    }

    switch ((int)weaponID)
        {
        case FUBU_BEAM:
        case BULLET1:
        case BULLET2:
        case BULLET3:
        case BULLET4:
        {
            return;
        }
        case AXE:
            center = player_center;
            break;
        case NUTS:
            center += direction * projectileSpeed;
            angle += 5;
            if(bounce && circleBounce(Circle{center, size.x / 2}, direction, camera)) 
            {
                bounce = false;
            }
            break;
        case CEO_TEARS:
            center += direction * projectileSpeed;
            break;
        case SPIDER_COOKING:
            center = player_center;
            break;
        case FAN_BEAM:
            center = player_center;
            break;
        case BL_BOOK:
        {
            center += player_center - rotatingCenter;
            rotatingCenter = player_center;
            circularMotion(center, player_center, -0.01 * projectileSpeed);
            break;
        }
        case PSYCHO_AXE:
        {
            timePassed += timeStep;
            spiralMotion(center, rotatingCenter, 0.01, timePassed);
            break;
        }
        case IDOL_SONG:
        {
            int temp = (count == 0 ? 1 : -1);
            center.y += temp * projectileSpeed;
            center.x = temp * sin((2.5 - duration) * 10) * 100 * projectileSpeed + direction.x;
            break;
        }
        case ELITE_LAVA:
        {
            break;
        }
        case FALLING_BLOCKS:
        {
            if (fallTime > 0)
            {
                center.y += 8;
                fallTime -= timeStep;
                if (fallTime <= 0)
                {
                    shake = true;
                    shakeTime = 30;
                }
            }
            break;
        }
        case CUTTING_BOARD:
        {
            if (fallTime > 0)
            {
                center.x += cosf((angle + 180.0f) / 180.0f * M_PI) * projectileSpeed;
                center.y += sinf((angle + 180.0f) / 180.0f * M_PI) * projectileSpeed;
                fallTime -= timeStep;
            }
            break;
        }
        case X_POTATO:
        {
            if (fallTime > 0)
            {
                center += direction * projectileSpeed;
                angle += 20;
                circleBounce(Circle{center, radius}, direction, camera);
                fallTime -= timeStep;
                if (fallTime <= 0)
                {
                    explode();
                }
            }
            break;
        }
        }
}

bool DamagingArea::hitEnemy(Circle &enemyCollider, int enemyID)
{
    if (hitID.find(enemyID) != hitID.end()) {
        return false;
    }
    
    switch ((int)weaponID)
    {
    case AXE:
    {
        SDL_Rect hitBox;
        hitBox.w = size.x * 1.5;
        hitBox.h = size.y * 1.5;
        hitBox.x = center.x;
        hitBox.y = center.y - hitBox.h / 2;
        switch ((int)angle)
        {
        case 0:
            hitBox.x -= hitBox.w / 8;
            break;
        case 180:
            hitBox.x -= hitBox.w - hitBox.w / 8;
            break;
        case -90:
            std::swap(hitBox.w, hitBox.h);
            hitBox.x -= hitBox.w / 2;
            hitBox.y -= -hitBox.w / 2 + hitBox.h - hitBox.h / 8;
            break;
        case 90:
            std::swap(hitBox.w, hitBox.h);
            hitBox.x -= hitBox.w / 2;
            hitBox.y -= -hitBox.w / 2 + hitBox.h / 8;
            break;
        }

        if (!checkAABBCircleCollision(hitBox, enemyCollider))
        {
            return false;
        }
        break;
    }
    case NUTS:
    {
        if (!checkCircleCollision(Circle{center, size.x / 2}, enemyCollider))
        {
            return false;
        }
        break;
    }
    case SPIDER_COOKING:
    {
        if (!checkCircleCollision(Circle{center, size.x}, enemyCollider))
        {
            return false;
        }
        break;
    }
    case CEO_TEARS:
    {
        if (!checkCircleCollision(Circle{center, size.y / 2}, enemyCollider))
        {
            return false;
        }
        break;
    }
    case FAN_BEAM:
    {
        SDL_Rect hitBox;
        hitBox.w = 460;
        hitBox.h = size.y;
        hitBox.x = center.x + 50;
        hitBox.y = center.y - hitBox.h / 2;

        if (angle == 180)
            hitBox.x += -hitBox.w - 100;

        if (!checkAABBCircleCollision(hitBox, enemyCollider))
        {
            return false;
        }
        break;
    }
    case BL_BOOK:
    {
        if (!checkCircleCollision(Circle{center, size.x * 1.2f}, enemyCollider))
        {
            return false;
        }
        break;
    }
    case PSYCHO_AXE:
    {
        if (!checkCircleCollision(Circle{center, size.x * 2 / 3}, enemyCollider))
        {
            return false;
        }
        break;
    }
    case IDOL_SONG:
    {
        if (!checkCircleCollision(Circle{center, (size.x + size.y) / 4}, enemyCollider))
        {
            return false;
        }
        break;
    }
    case ELITE_LAVA:
    {
        if (!checkCircleCollision(Circle{center, 110}, enemyCollider))
        {
            return false;
        }
        break;
    }
    case FALLING_BLOCKS:
    {
        SDL_Rect hitBox;
        if(count >= 0 && count <= 3)
        {
            switch(count)
            {
                case 0:
                hitBox = SDL_Rect{(int)center.x - 96, (int)center.y, 96,96};
                break;
                case 1:
                hitBox = SDL_Rect{(int)center.x - 96, (int)center.y - 96, 96,96};
                break;
                case 2:
                hitBox = SDL_Rect{(int)center.x, (int)center.y - 96, 96,96};
                break;
                case 3:
                hitBox = SDL_Rect{(int)center.x, (int)center.y, 96,96};
                break;
            }
            if (!checkAABBCircleCollision(hitBox, enemyCollider))
            {
                // inflictDamage(weapon, player, enemyHealth, isHit, enemyID);
                return false;
            }
        }
        else if(count >= 4 && count <= 7)
        {
            switch(count)
            {
                case 4:
                hitBox = SDL_Rect{(int)center.x - 96, (int)center.y, 192,96};
                break;
                case 5:
                hitBox = SDL_Rect{(int)center.x - 96, (int)center.y - 96, 96,192};
                break;
                case 6:
                hitBox = SDL_Rect{(int)center.x - 96, (int)center.y - 96, 192,96};
                break;
                case 7:
                hitBox = SDL_Rect{(int)center.x, (int)center.y-96, 96,192};
                break;
            }
            if (!checkAABBCircleCollision(hitBox, enemyCollider))
            {
                // inflictDamage(weapon, player, enemyHealth, isHit, enemyID);
                return false;
            }
        }
        else
        {
            hitBox = SDL_Rect{(int)center.x - 96, (int)center.y - 96, 192, 192};
            if(!checkAABBCircleCollision(hitBox, enemyCollider)) return false;
            SDL_Rect safeZone;
            switch(count)
            {
                case 8:
                safeZone = SDL_Rect{(int)center.x - 96, (int)center.y-96, 96,96};
                if(enemyCollider.center.x + enemyCollider.radius <= safeZone.x + safeZone.w 
                && enemyCollider.center.y + enemyCollider.radius <= safeZone.y + safeZone.h)
                return false;
                break;
                case 9:
                safeZone = SDL_Rect{(int)center.x, (int)center.y - 96, 96,96};
                if(enemyCollider.center.x - enemyCollider.radius >= safeZone.x
                && enemyCollider.center.y + enemyCollider.radius <= safeZone.y + safeZone.h)
                return false;
                break;
                case 10:
                safeZone = SDL_Rect{(int)center.x, (int)center.y, 96,96};
                if(enemyCollider.center.x - enemyCollider.radius >= safeZone.x
                && enemyCollider.center.y - enemyCollider.radius >= safeZone.y)
                return false;
                break;
                case 11:
                safeZone = SDL_Rect{(int)center.x - 96, (int)center.y, 96,96};
                if(enemyCollider.center.x + enemyCollider.radius <= safeZone.x + safeZone.w 
                && enemyCollider.center.y - enemyCollider.radius >= safeZone.y)
                return false;
                break;
            }
            // inflictDamage(weapon, player, enemyHealth, isHit, enemyID);
            // return true;
        }
        break;
    }
    case CUTTING_BOARD:
    {
        SDL_Rect hitBox;
        hitBox.w = size.x * areaMultiplier[0];
        hitBox.h = size.y * areaMultiplier[0];
        if((int)angle % 180 != 0) std::swap(hitBox.w, hitBox.h);
        hitBox.x = center.x - hitBox.w / 2;
        hitBox.y = center.y - hitBox.h / 2;
        if(!checkAABBCircleCollision(hitBox, enemyCollider))
        {
            return false;
        }
        break;
    }
    case X_POTATO:
    {
        if(!checkCircleCollision(Circle{center, radius}, enemyCollider))
        {
            return false;
        }
        break;
    }
    }
    --hitLimit;
    hitID[enemyID] = hitCooldown;
    return true;
}
void DamagingArea::explode()
{
    switch((int)weaponID)
    {
        case X_POTATO:
        damage *= 2;
        hitLimit = -1;
        frames = 4;
        radius *= 15;
        textureID = "res/gfx/spr_PotatoExplosion/spr_PotatoExplosion.png";
        return;
    }
}

void DamagingArea::render(SDL_Renderer* renderer, Player player, int camX, int camY)
{
    switch ((int)weaponID)
    {
    case AXE:
    {
        SDL_Rect dst;
        dst.w = size.x * 1.5;
        dst.h = size.y * 1.5;
        dst.x = center.x - camX;
        dst.y = center.y - dst.h / 2 - camY;

        switch ((int)angle)
        {
        case 0:
            dst.x -= dst.w / 8;
            break;
        case 180:
            dst.x += -dst.w + dst.w / 8;
            break;
        case -90:
            dst.x += -dst.w / 2;
            dst.y += -dst.w / 2 + dst.h / 8;
            break;
        case 90:
            dst.x += -dst.w / 2;
            dst.y += dst.w / 2 - dst.h / 8;
            break;
        }
        ResourceManager::getInstance().Draw(dst.x, dst.y, dst.w, dst.h);
        ResourceManager::getInstance().PlayFrame(0, 0, 107, 144, currentFrame);
        ResourceManager::getInstance().Render(textureID, renderer, SDL_FLIP_NONE, angle);
        return;
    }
    case NUTS:
    {
        ResourceManager::getInstance().Draw((int)(center.x - size.x / 2 - camX), (int)(center.y - size.y / 2 - camY), (int)size.x, (int)size.y);
        ResourceManager::getInstance().PlayFrame(0, 0, 0, 0, 0);
        ResourceManager::getInstance().Render(textureID, renderer, SDL_FLIP_NONE, angle);
        return;
    }
    case SPIDER_COOKING:
    {
        ResourceManager::getInstance().Draw(center.x - size.x * 2 / 2 - camX, center.y - size.x * 2 / 2 - camY, size.x * 2, size.y * 2);
        SDL_SetTextureAlphaMod(ResourceManager::getInstance().getTexture(textureID, renderer), 50);
        ResourceManager::getInstance().PlayFrame(0, 0, 0, 0, 0);
        ResourceManager::getInstance().Render(textureID, renderer, SDL_FLIP_NONE, 0);
        return;
    }
    case CEO_TEARS:
    {
        ResourceManager::getInstance().Draw((int)(center.x - size.x / 2 - camX), (int)(center.y - size.y / 2 - camY), (int)size.x, (int)size.y);
        ResourceManager::getInstance().PlayFrame(0, 0, 0, 0, 0);
        ResourceManager::getInstance().Render(textureID, renderer, SDL_FLIP_NONE, 0);
        return;
    }
    case FAN_BEAM:
    {
        textureID = FanBeam_Animation[currentFrame];
        SDL_Rect dst;
        SDL_QueryTexture(ResourceManager::getInstance().getTexture(textureID, renderer), NULL, NULL, &dst.w, &dst.h);
        dst.h *= areaMultiplier[0];
        dst.x = center.x - camX + 50;
        dst.y = center.y - dst.h / 2 - camY;
        if (angle == 180) dst.x += -dst.w - 100;
        ResourceManager::getInstance().Draw(dst.x, dst.y, dst.w, dst.h);
        ResourceManager::getInstance().PlayFrame(0, 0, 0, 0, 0);
        ResourceManager::getInstance().Render(textureID,renderer, SDL_FLIP_NONE, 0);
        return;
    }
    case BL_BOOK:
    {
        ResourceManager::getInstance().Draw(center.x - size.x / 2 - camX, center.y - size.y / 2 - camY, size.x, size.y);
        ResourceManager::getInstance().PlayFrame(0, 0, 0, 0, 0);
        ResourceManager::getInstance().Render(textureID,renderer, SDL_FLIP_NONE, 0);
        return;
    }
    case PSYCHO_AXE:
    {
        ResourceManager::getInstance().Draw(center.x - size.x - camX, center.y - size.y - camY, size.x * 2, size.y * 2);
        ResourceManager::getInstance().PlayFrame(0, 0, 46, 46, currentFrame);
        ResourceManager::getInstance().Render(textureID,renderer, SDL_FLIP_NONE, 0);
        return;
    }
    case IDOL_SONG:
    {
        ResourceManager::getInstance().Draw(center.x - size.x / 2 - camX, center.y - size.y / 2 - camY, size.x, size.y);
        ResourceManager::getInstance().PlayFrame(0, 0, 0, 0, 0);
        ResourceManager::getInstance().Render(IdolSong_Animation,renderer, SDL_FLIP_NONE, 0);
        return;
    }
    case FUBU_BEAM:
    {
        if (currentFrame < 30)
        {
            SDL_Rect dst;
            dst.w = SCREEN_WIDTH;
            dst.h = 234;
            dst.x = center.x - camX + 120;
            dst.y = center.y - dst.h / 2 - camY;
            if (angle == 180)
                dst.x += -dst.w - 230;
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 50 * (currentFrame / 3 % 2 + 1));
            SDL_RenderFillRect(renderer, &dst);
            return;
        }

        SDL_Rect dst;
        SDL_QueryTexture(ResourceManager::getInstance().getInstance().getTexture(FubuBeam_Animation[currentFrame - 30], renderer), NULL, NULL, NULL, &dst.h);
        dst.w = SCREEN_WIDTH;
        dst.h *= 18;
        dst.x = center.x - camX + 120;
        dst.y = center.y - dst.h / 2 - camY;

        if (angle == 180)
            dst.x += -dst.w - 230;

        ResourceManager::getInstance().Draw(dst.x, dst.y, dst.w, dst.h);
        ResourceManager::getInstance().PlayFrame(0, 0, dst.w, dst.h, 0);
        ResourceManager::getInstance().Render(FubuBeam_Animation[currentFrame - 30], renderer, SDL_FLIP_NONE, angle);
        return;
    }
    case ELITE_LAVA:
    {
        if (currentFrame < 9)
        {
            textureID = LavaPoolStart_Animation[currentFrame];
        }
        else if (currentFrame > frames - 6)
        {
            textureID = LavaPoolEnd_Animation[currentFrame - (frames - 5)];
        }
        else
        {
            textureID = LavaPool;
        }

        SDL_Rect dst;
        SDL_QueryTexture(ResourceManager::getInstance().getTexture(textureID, renderer), NULL, NULL, &dst.w, &dst.h);
        dst.w *= 2;
        dst.h *= 2;
        dst.x = center.x - dst.w / 2 - camX;
        dst.y = center.y - dst.h / 2 - camY;

        ResourceManager::getInstance().Draw(dst.x, dst.y, dst.w, dst.h);
        ResourceManager::getInstance().PlayFrame(0, 0, dst.w, dst.h, 0);
        ResourceManager::getInstance().Render(textureID, renderer, SDL_FLIP_NONE, angle);
        return;
    }
    case FALLING_BLOCKS:
    {
        ResourceManager::getInstance().Draw(center.x - 96 - camX, center.y - 96 - camY, 192, 192);
        ResourceManager::getInstance().PlayFrame(0, 0, 43, 43, count);
        ResourceManager::getInstance().Render(textureID, renderer, SDL_FLIP_NONE, 0);
        return;
    }
    case CUTTING_BOARD:
    {
        SDL_Rect dst;
        dst.w = size.x * areaMultiplier[0];
        dst.h = size.y * areaMultiplier[0];
        dst.x = center.x - dst.w / 2 - camX;
        dst.y = center.y - dst.h / 2 - camY;
        ResourceManager::getInstance().Draw(dst.x, dst.y, dst.w, dst.h);
        ResourceManager::getInstance().PlayFrame(0,0,10,63,0);
        ResourceManager::getInstance().Render(textureID, renderer, SDL_FLIP_NONE, angle);
        return;
    }
    case X_POTATO:
    {
        SDL_Rect dst;
        if(fallTime > 0)
        {
            dst.w = 15 * areaMultiplier[0];
            dst.h = 21 * areaMultiplier[0];
        }
        else
        {
            dst.w = 256 * areaMultiplier[1];
            dst.h = 256 * areaMultiplier[1];
        }
        dst.x = center.x - dst.w / 2 - camX;
        dst.y = center.y - dst.h / 2 - camY;
        ResourceManager::getInstance().Draw(dst.x, dst.y, dst.w, dst.h);
        ResourceManager::getInstance().PlayFrame(0,0,256,256,currentFrame);
        ResourceManager::getInstance().Render(textureID, renderer, SDL_FLIP_NONE, angle);
        return;
    }
    case BULLET1:
    case BULLET4:
    {
        ResourceManager::getInstance().Draw(center.x - 26/2 - camX, center.y - 26/2 - camY, 26, 26);
        ResourceManager::getInstance().PlayFrame(0, 0, 0, 0, 0);
        ResourceManager::getInstance().Render(BulletBlue_Animation[currentFrame],renderer, SDL_FLIP_NONE, 0);
        return;
    }
    case BULLET2:
    {
        ResourceManager::getInstance().Draw(center.x - 26/2 - camX, center.y - 26/2 - camY, 26, 26);
        ResourceManager::getInstance().PlayFrame(0, 0, 0, 0, 0);
        ResourceManager::getInstance().Render(BulletRed_Animation[currentFrame],renderer, SDL_FLIP_NONE, 0);
        return;
    }
    case BULLET3:
    {
        ResourceManager::getInstance().Draw(center.x - 26/2 - camX, center.y - 26/2 - camY, 26, 26);
        ResourceManager::getInstance().PlayFrame(0, 0, 0, 0, 0);
        if(count < 5)
        ResourceManager::getInstance().Render(BulletYellow_Animation[currentFrame],renderer, SDL_FLIP_NONE, 0);
        else 
        ResourceManager::getInstance().Render(BulletRed_Animation[currentFrame],renderer, SDL_FLIP_NONE, 0);
        return;
    }
    }
}

Weapon::Weapon(WEAPON_ID type)
    : ID(type)
{
    dmgArea.weaponID = ID;
    switch ((int)ID)
    {
    case AXE:
    {
        dmgArea.duration = 0.18;
        timeBetweenAttacks = 1.38;
        dmgArea.hitLimit = -1;
        dmgArea.damage = 120;
        dmgArea.hitCooldown = 0.5;
        dmgArea.frames = 5;
        dmgArea.size = {107, 144};
        dmgArea.textureID = "res/gfx/spr_SuiseiAxeSwing/spr_SuiseiAxeSwing2.png";
        break;
    }
    case NUTS:
    {
        dmgArea.duration = 1;
        timeBetweenAttacks = 1.33;
        dmgArea.hitLimit = 8;
        dmgArea.damage = 100;
        dmgArea.attackCount = 3;
        dmgArea.projectileSpeed = 5;
        dmgArea.hitCooldown = 0.5;
        dmgArea.frames = 0;
        dmgArea.size = {12, 18};
        dmgArea.textureID = "res/gfx/spr_RisuCashew.png";
        break;
    }
    case SPIDER_COOKING:
    {
        dmgArea.duration = 10;
        dmgArea.frames = 0;
        timeBetweenAttacks = 10.02;
        dmgArea.hitLimit = -1;
        dmgArea.damage = 90;
        dmgArea.hitCooldown = 0.75;
        dmgArea.size = {107, 107};
        dmgArea.textureID = "res/gfx/spr_spidercooking.png";
        break;
    }
    case CEO_TEARS:
    {
        dmgArea.duration = 1.5;
        dmgArea.frames = 0;
        timeBetweenAttacks = 0.5;
        dmgArea.hitLimit = 1;
        dmgArea.damage = 100;
        dmgArea.attackCount = 1;
        dmgArea.projectileSpeed = 4;
        dmgArea.size = {20,16};
        dmgArea.textureID = "res/gfx/spr_CEOTears.png";
        break;
    }
    case FAN_BEAM:
    {
        dmgArea.duration = 0.3;
        dmgArea.frames = 9;
        timeBetweenAttacks = 3;
        dmgArea.hitLimit = -1;
        dmgArea.damage = 300;
        dmgArea.hitCooldown = 1;
        dmgArea.size = {460, 13};
        dmgArea.areaMultiplier[0] = 1;
        dmgArea.knockbackSpeed = 15;
        dmgArea.knockbackTime = 0.1;
        break;
    }
    case BL_BOOK:
    {
        dmgArea.duration = 2;
        dmgArea.frames = 0;
        timeBetweenAttacks = 6;
        dmgArea.hitLimit = 7;
        dmgArea.damage = 140;
        dmgArea.hitCooldown = 0.33;
        dmgArea.radius = 100;
        dmgArea.attackCount = 3;
        dmgArea.size = {36,46};
        dmgArea.projectileSpeed = 3;
        dmgArea.knockbackSpeed = 2;
        dmgArea.knockbackTime = 0.08;
        dmgArea.textureID = BLBook_Animation;
        break;
    }
    case PSYCHO_AXE:
    {
        dmgArea.damage = 120;
        timeBetweenAttacks = 4;
        dmgArea.attackCount = 1;
        dmgArea.hitLimit = 10;
        dmgArea.hitCooldown = 0.83;
        dmgArea.duration = 3;
        dmgArea.frames = 7;
        dmgArea.radius = 100;
        dmgArea.size = {46, 46};
        dmgArea.textureID = "res/gfx/spr_PsychoAxe/spr_PsychoAxe.png";
        break;
    }
    case IDOL_SONG:
    {
        dmgArea.damage = 130;
        timeBetweenAttacks = 3.33;
        dmgArea.attackCount = 2;
        dmgArea.hitLimit = -1;
        dmgArea.hitCooldown = 0.33;
        dmgArea.duration = 2.5;
        dmgArea.frames = 4;
        dmgArea.size = {58,54};
        dmgArea.projectileSpeed = 1;
        dmgArea.textureID = IdolSong_Animation;
        break;
    }
    case ELITE_LAVA:
    {
        dmgArea.damage = 80;
        timeBetweenAttacks = 5;
        dmgArea.attackCount = 1;
        dmgArea.hitLimit = -1;
        dmgArea.hitCooldown = 0.75;
        dmgArea.duration = 3;
        dmgArea.frames = 99;
        break;
    }
    case FALLING_BLOCKS:
    {
        dmgArea.damage = 300;
        timeBetweenAttacks = 0.25;
        dmgArea.attackCount = 1;
        dmgArea.hitLimit = -1;
        dmgArea.hitCooldown = 2;
        dmgArea.duration = 2;
        dmgArea.frames = 0;
        dmgArea.textureID = "res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks.png";
        break;
    }
    case CUTTING_BOARD:
    {
        dmgArea.damage = 130;
        timeBetweenAttacks = 3;
        dmgArea.attackCount = 1;
        dmgArea.hitLimit = -1;
        dmgArea.hitCooldown = 0.33;
        dmgArea.duration = 2;
        dmgArea.frames = 0;
        dmgArea.fallTime = 0.25;
        dmgArea.projectileSpeed = 7;
        dmgArea.knockbackSpeed = 7;
        dmgArea.knockbackTime = 0.20;
        dmgArea.size = {20,126};
        dmgArea.areaMultiplier[0] = 1.3;
        dmgArea.textureID = CuttingBoard_Animation;
        break;
    }
    case X_POTATO:
    {
        dmgArea.textureID = XPotato_Animation;
        dmgArea.damage = 90;
        timeBetweenAttacks = 3.5;
        dmgArea.attackCount = 1;
        dmgArea.hitLimit = 10;
        dmgArea.hitCooldown = 0.33;
        dmgArea.duration = 2;
        dmgArea.frames = 0;
        dmgArea.radius = 8;
        dmgArea.fallTime = 1.85;
        dmgArea.projectileSpeed = 5;
        dmgArea.size = {30,42};
        dmgArea.areaMultiplier[0] = 1;
        dmgArea.areaMultiplier[1] = 0.8;
        break;
    }
    case FUBU_BEAM:
    {
        dmgArea.damage = 15;
        dmgArea.duration = 1.17;
        dmgArea.frames = 38;
        timeBetweenAttacks = 3;
        dmgArea.hitLimit = -1;
        dmgArea.hitCooldown = 1;
        dmgArea.ofPlayer = false;
        break;
    }
    case BULLET1:
    case BULLET2:
    case BULLET3:
    case BULLET4:
    {
        dmgArea.damage = 1;
        // if(ID != BULLET1 && ID != BULLET4) 
        // {
        //     dmgArea.attackCount = 10;
        //     timeBetweenAttacks = 0.5;
        // }
        if(ID == BULLET2) 
        {
            dmgArea.attackCount = 10;
            timeBetweenAttacks = 4;
        }
        else if(ID == BULLET1){
            dmgArea.attackCount = 6;
            timeBetweenAttacks = 4;
            dmgArea.attackDelay = 0.25;
        }
        else if(ID == BULLET4){
            dmgArea.attackCount = 120;
            timeBetweenAttacks = 14;
            dmgArea.attackDelay = 0.05;
        }
        else if(ID == BULLET3)
        {
            dmgArea.attackCount = 24;
            timeBetweenAttacks = 14;
            dmgArea.attackDelay = 0.25;
        }
        dmgArea.duration = 7;
        dmgArea.frames = 1;
        
        dmgArea.hitLimit = 1;
        dmgArea.hitCooldown = 1;
        dmgArea.projectileSpeed = 1.6;
        dmgArea.ofPlayer = false;
        break;
    }
    }
    count = dmgArea.attackCount;
    // cooldown = timeBetweenAttacks;
}

void Weapon::setHitLimit(int newHitLimit)
{
    dmgArea.hitLimit = newHitLimit;
}

void Weapon::setHitCooldown(float newHitCooldown)
{
    dmgArea.hitCooldown = newHitCooldown;
}

void Weapon::setDamage(float newDamage)
{
    dmgArea.damage = newDamage;
}
void Weapon::setAttackInterval(float newInterval)
{
    timeBetweenAttacks = newInterval;
}
void Weapon::setArea(float areaIncrease)
{
    dmgArea.size *= (100.0 + areaIncrease) / 100.0;
    dmgArea.areaMultiplier[0] *= (100.0 + areaIncrease) / 100;
}
void Weapon::setDuration(float newDuration)
{
    dmgArea.duration = newDuration;
}

void Weapon::setAttackCount(int newCount)
{
    dmgArea.attackCount = newCount;
}

void Weapon::setKnockback(float time, float speed)
{
    dmgArea.knockbackTime = time;
    dmgArea.knockbackSpeed = speed;
}

void Weapon::initiateDmgArea(Vector2f playerCenter,float playerArrowAngle, SDL_RendererFlip playerFlip, int count,Vector2f direction)
{
            switch ((int)ID)
            {
            case AXE:
            {
                dmgArea.center = playerCenter;
                dmgArea.angle = playerArrowAngle;
                // dmgArea.flip = player.flip;
                break;
            }
            case NUTS:
            {
                dmgArea.center = playerCenter;
                dmgArea.direction = {cosf((10 * (count) + playerArrowAngle - 5 * (dmgArea.attackCount - 1)) / 180 * M_PI), sinf((10 * (count) + playerArrowAngle - 5 * (dmgArea.attackCount - 1)) / 180 * M_PI)}; 
                // dmgArea.direction.print();
            }
            case SPIDER_COOKING:
            {
                dmgArea.center = playerCenter;
                break;
            }
            case CEO_TEARS:
            {
                dmgArea.center = playerCenter;
                dmgArea.direction = direction;
                break;
            }
            case FAN_BEAM:
            {
                dmgArea.center = playerCenter;
                // if (player.flip == SDL_FLIP_HORIZONTAL)
                //     dmgArea.angle = 180 + 180 * i;
                // else
                //     dmgArea.angle = 0 + 180 * i;
                dmgArea.angle = (playerFlip == SDL_FLIP_HORIZONTAL ? 180 + 180 * count: 180 * count);
                break;
            }
            case BL_BOOK:
            {
                dmgArea.rotatingCenter = playerCenter;
                Vector2f temp{playerCenter.x, playerCenter.y - dmgArea.radius};
                circularMotion(temp, playerCenter, 2 * PI / dmgArea.attackCount * count);
                dmgArea.center = temp;
                break;
            }
            case PSYCHO_AXE:
            {
                dmgArea.rotatingCenter = playerCenter;
                break;
            }
            case IDOL_SONG:
            {
                dmgArea.center = dmgArea.direction = playerCenter;
                dmgArea.count = count;
                break;
            }
            case FUBU_BEAM:
            case BULLET1:
            case BULLET2:
            case BULLET3:
            {
                break;
            }
            case ELITE_LAVA:
            {
                dmgArea.center = Vector2f{randomFloat(-SCREEN_WIDTH / 3, SCREEN_WIDTH / 3), randomFloat(-SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3)} + playerCenter;
                break;
            }
            case FALLING_BLOCKS:
            {
                specialDuration[1] -= timeBetweenAttacks;
                dmgArea.center = Vector2f{(float)(randomInt(-5, 5) * 98), -SCREEN_HEIGHT / 2} + playerCenter;
                dmgArea.fallTime = (rand() % 6 + 1) * 0.12;
                dmgArea.count = rand() % 12;
                break;
            }
            case CUTTING_BOARD:
            {
                dmgArea.center = playerCenter;
                switch(count)
                {
                    case 0: dmgArea.angle = playerArrowAngle; break;
                    case 1: dmgArea.angle = playerArrowAngle + 90; break;
                    case 2: dmgArea.angle = playerArrowAngle - 90; break;
                }
                break;
            }
            case X_POTATO:
            {
                dmgArea.center = playerCenter;
                Vector2f temp = {randomFloat(-1,1), randomFloat(-1,1)};
                while(temp.x == 0 && temp.y == 0)
                {
                    temp = {randomFloat(-1,1), randomFloat(-1,1)};
                }
                dmgArea.direction = vectorNormalize(temp);
                break;
            }
            }
}

void Weapon::updateStats()
{
    ++level;
    switch ((int)ID)
    {
    case PSYCHO_AXE:
    {
        switch (level)
        {
        case 2:
            setArea(20);
            setDamage(156);
            return;
        case 3:
            setAttackInterval(3.2);
            return;
        case 4:
            setArea(20);
            setDamage(207);
        case 5:
            setHitLimit(-1);
            setDuration(4);
            return;
        case 6:
            setArea(50);
            return;
        case 7:
            setDamage(311);
            return;
        }
    }
    case NUTS:
    {
        switch (level)
        {
        case 2:
            setDamage(120);
            return;
        case 3:
            setAttackCount(4);
            return;
        case 4:
            setAttackInterval(1.13);
            return;
        case 5:
            setAttackCount(5);
            return;
        case 6:
            setDamage(144);
            dmgArea.projectileSpeed = 7.5;
            return;
        case 7:
            setArea(30);
            setDuration(2.5);
            dmgArea.bounce = true;
            return;
        }
    }
    case SPIDER_COOKING:
    {
        switch (level)
        {
        case 2:
            setArea(15);
            return;
        case 3:
            setDamage(117);
            return;
        case 4:
            setArea(25);
            return;
        case 5:
            setHitCooldown(0.6);
            return;
        case 6:
            setDamage(140.4);
            return;
        case 7:
            setKnockback(0.13, 3.0);
            return;
        }
    }
    case ELITE_LAVA:
    {
        switch (level)
        {
        case 2:
            setArea(20);
            return;
        case 3:
            setAttackCount(2);
            return;
        case 4:
            setDamage(120);
            setDuration(4.5);
            dmgArea.frames = 149;
        case 5:
            setDamage(156);
            return;
        case 6:
            setAttackCount(3);
            return;
        case 7:
            setArea(20);
            setAttackCount(4);
            return;
        }
    }
    case FAN_BEAM:
    {
        switch(level)
        {
            case 2: 
            setArea(30);
            return;
            case 3:
            setAttackInterval(2.5);
            return;
            case 4:
            setDamage(400);
            return;
            case 5:
            setAttackInterval(2);
            return;
            case 6:
            setArea(50);
            return;
            case 7:
            setAttackCount(2);
            return;
        }
    }
    case BL_BOOK:
    {
        switch(level)
        {
        case 2:
        setAttackCount(4);
        return;
        case 3:
        setDamage(182);
        setDuration(5);
        return;
        case 4:
        setAttackCount(5);
        return;
        case 5:
        dmgArea.radius = 150;
        dmgArea.projectileSpeed = 6;
        return;
        case 6:
        setAttackCount(6);
        return;
        case 7:
        setDamage(254.8);
        return;
        }
    }
    case CEO_TEARS:
    {
        switch (level)
        {
        case 2:
        setDamage(120);
        return;
        case 3:
        setAttackCount(2);
        return;
        case 4:
        setAttackInterval(0.33);
        return;
        case 5:
        dmgArea.projectileSpeed = 5;
        setDamage(144);
        return;
        case 6:
        setAttackInterval(0.17);
        return;
        case 7:
        setAttackCount(4);
        return;
        }
    }
    case IDOL_SONG:
    {
        switch(level)
        {
            case 2: setDamage(162.5); return;
            case 3: dmgArea.projectileSpeed = 1.2; return;
            case 4: setArea(25); return;
            case 5: setAttackInterval(2.67); return;
            case 6: setArea(25); return;
            case 7: setDamage(243); return;
        }
    }
    case AXE:
    {
        switch(level)
        {
            case 2: setDamage(156); return; 
            case 3: setArea(20); return; 
            case 4: setAttackInterval(1.33); return;
            case 5: setDamage(200); return;
            case 6: setArea(20); return;
            case 7: 
            dmgArea.textureID = "res/gfx/spr_SuiseiAxeSwing/spr_SuiseiAxeSwing3.png";
            setDamage(600); 
            return;
        }
    }
    case CUTTING_BOARD:
    {
        switch(level)
        {
            case 2: setArea(30); return;
            case 3: setDamage(162.5); return;
            case 4: dmgArea.projectileSpeed = 10; return;
            case 5: setDamage(253.5); return;
            case 6: setAttackInterval(2.5); return;
            case 7: setAttackCount(3); return;
        }
    }
    }
}

int damageCal(DamagingArea weapon, Player player)
{
    float weaponDamage = weapon.damage / 100;

    float totalWeaponDamage = weaponDamage;

    float attackDamage = 10 * totalWeaponDamage * player.getATK() / 100;

    if (attackDamage > 2)
    {
        attackDamage += randomFloat(-std::max(attackDamage * 0.1f, 2.0f), std::max(attackDamage * 0.1f, 2.0f));
    }

    return (int)attackDamage;
}

bool hitPlayer(DamagingArea &weapon, Player &player)
{
    if (weapon.hitID.find(1) != weapon.hitID.end())
        return false;

    switch ((int)weapon.weaponID)
    {
    case FUBU_BEAM:
    {
        if (weapon.currentFrame < 30)
            return false;
        SDL_Rect hitBox;
        hitBox.w = SCREEN_WIDTH;
        hitBox.h = 180;
        hitBox.x = weapon.center.x + 120;
        hitBox.y = weapon.center.y - hitBox.h / 2;

        if (weapon.angle == 180)
            hitBox.x += -hitBox.w - 230;

        if (checkAABBCircleCollision(hitBox, player.collider))
        {
            player.health -= 15;
            weapon.hitID[1] = weapon.hitCooldown;
            return true;
        }
        return false;
    }
    case BULLET1:
    case BULLET2:
    case BULLET3:
    case BULLET4:
    {
        if (checkCircleCollision(Circle{weapon.center, 10}, player.collider))
        {
            player.health -= 0;
            weapon.hitID[1] = weapon.hitCooldown;
            --weapon.hitLimit;
            return true;
        }   
    }
    }

    return false;
}