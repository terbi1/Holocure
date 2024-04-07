#include "weapon.hpp"

DamagingArea::DamagingArea()
{
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
        break;
    }
    case CEO_TEARS:
    {
        dmgArea.duration = 1.5;
        dmgArea.frames = 0;
        timeBetweenAttacks = 0.5;
        dmgArea.hitLimit = 1;
        dmgArea.damage = 100;
        // dmgArea.frameTime = 1.5;
        dmgArea.attackCount = 1;
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
        break;
    }
    case FUBU_BEAM:
    {
        dmgArea.duration = 1.17;
        dmgArea.frames = 38;
        timeBetweenAttacks = 3;
        dmgArea.hitLimit = -1;
        dmgArea.hitCooldown = 1;
        dmgArea.ofPlayer = false;
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
        dmgArea.hitLimit = 10;
        dmgArea.hitCooldown = 2;
        dmgArea.duration = 2;
        dmgArea.frames = 0;
        break;
    }
    }
}

void Weapon::setHitLimit(int newHitLimit)
{
    dmgArea.hitLimit = newHitLimit;
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
}
void Weapon::setDuration(float newDuration)
{
    dmgArea.duration = newDuration;
}

void Weapon::setAttackCount(int newCount)
{
    dmgArea.attackCount = newCount;
}
void Weapon::updateStats()
{
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
    }
}

void renderWeapon(SDL_Renderer *renderer, DamagingArea &weapon, Player player, int frame, int camX, int camY)
{
    AnimatedSprite sprite;

    switch ((int)weapon.weaponID)
    {
    case AXE:
    {
        sprite.getResource(renderer, "res/gfx/spr_SuiseiAxeSwing/spr_SuiseiAxeSwing2.png");

        SDL_Rect src{0, 0, 107, 144};

        SDL_Rect dst;
        dst.w = weapon.size.x * 1.5;
        dst.h = weapon.size.y * 1.5;
        dst.x = weapon.center.x - camX;
        dst.y = weapon.center.y - dst.h / 2 - camY;

        SDL_Rect hitBox;
        hitBox.w = weapon.size.x * 1.5;
        hitBox.h = weapon.size.y * 1.5;
        hitBox.x = weapon.center.x;
        hitBox.y = weapon.center.y - hitBox.h / 2;

        switch (weapon.angle)
        {
        case 0:
            hitBox.x -= hitBox.w / 8;
            dst.x -= dst.w / 8;
            break;
        case 180:
            hitBox.x -= hitBox.w - hitBox.w / 8;
            dst.x += -dst.w + dst.w / 8;
            break;
        case -90:
            std::swap(hitBox.w, hitBox.h);
            hitBox.x -= hitBox.w / 2;
            hitBox.y -= -hitBox.w / 2 + hitBox.h - hitBox.h / 8;
            dst.x += -dst.w / 2;
            dst.y += -dst.w / 2 + dst.h / 8;
            break;
        case 90:
            std::swap(hitBox.w, hitBox.h);
            hitBox.x -= hitBox.w / 2;
            hitBox.y -= -hitBox.w / 2 + hitBox.h / 8;
            dst.x += -dst.w / 2;
            dst.y += dst.w / 2 - dst.h / 8;
            break;
        }
        hitBox.x -= camX;
        hitBox.y -= camY;
        sprite.Draw(dst.x, dst.y, dst.w, dst.h);
        sprite.PlayFrame(src.x, src.y, src.w, src.h, frame);
        sprite.Render(renderer, SDL_FLIP_NONE, weapon.angle);
        SDL_SetRenderDrawColor(renderer, 255,0,0,255);
        SDL_RenderDrawRect(renderer, &hitBox);
        return;
    }
    case SPIDER_COOKING:

    {
        sprite.getResource(renderer, "res/gfx/spr_spidercooking.png");

        sprite.Draw(weapon.center.x - 107 * 2 / 2 - camX, weapon.center.y - 107 * 2 / 2 - camY, 107 * 2, 107 * 2);
        SDL_SetTextureAlphaMod(sprite.getTexture(), 50);
        sprite.PlayFrame(0, 0, 107, 107, 0);
        sprite.Render(renderer, SDL_FLIP_NONE, 0);
        return;
    }
    case CEO_TEARS:
    {
        sprite.getResource(renderer, "res/gfx/spr_CEOTears.png");

        sprite.Draw(weapon.center.x - 10 - camX, weapon.center.y - 8 - camY, 20, 16);
        sprite.PlayFrame(0, 0, 10, 8, 0);
        sprite.Render(renderer, SDL_FLIP_NONE, 0);
        return;
    }
    case FAN_BEAM:
    {

        sprite.getResource(renderer, FanBeam_Animation[weapon.currentFrame].c_str());

        SDL_Rect dst;
        SDL_QueryTexture(sprite.getTexture(), NULL, NULL, &dst.w, &dst.h);
        dst.x = weapon.center.x - camX + 50;
        dst.y = weapon.center.y - dst.h / 2 - camY;

        if (weapon.angle == 180)
            dst.x += -dst.w - 100;

        sprite.Draw(dst.x, dst.y, dst.w, dst.h);
        sprite.PlayFrame(0, 0, dst.w, dst.h, 0);
        sprite.Render(renderer, SDL_FLIP_NONE, weapon.angle);
        return;
    }
    case BL_BOOK:
    {
        sprite.getResource(renderer, BLBook_Animation.c_str());

        sprite.Draw(weapon.center.x - 18 - camX, weapon.center.y - 23 - camY, 36, 46);
        sprite.PlayFrame(0, 0, 18, 23, 0);
        sprite.Render(renderer, SDL_FLIP_NONE, 0);
        return;
    }
    case PSYCHO_AXE:
    {
        sprite.getResource(renderer, PsychoAxe_Animation[weapon.currentFrame].c_str());

        sprite.Draw(weapon.center.x - weapon.size.x - camX, weapon.center.y - weapon.size.y - camY, weapon.size.x * 2, weapon.size.y * 2);
        sprite.PlayFrame(0, 0, 46, 46, 0);
        sprite.Render(renderer, SDL_FLIP_NONE, 0);
        return;
    }
    case IDOL_SONG:
    {
        sprite.getResource(renderer, IdolSong_Animation.c_str());

        sprite.Draw(weapon.center.x - 29 - camX, weapon.center.y - 27 - camY, 58, 54);
        sprite.PlayFrame(0, 0, 29, 27, 0);
        sprite.Render(renderer, SDL_FLIP_NONE, 0);
        return;
    }
    case FUBU_BEAM:
    {
        if (weapon.currentFrame < 30)
        {
            SDL_Rect dst;
            dst.w = SCREEN_WIDTH;
            dst.h = 234;
            dst.x = weapon.center.x - camX + 120;
            dst.y = weapon.center.y - dst.h / 2 - camY;
            if (weapon.angle == 180)
                dst.x += -dst.w - 230;
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 50 * (weapon.currentFrame / 3 % 2 + 1));
            SDL_RenderFillRect(renderer, &dst);
            return;
        }
        sprite.getResource(renderer, FubuBeam_Animation[weapon.currentFrame - 30].c_str());

        SDL_Rect dst;
        SDL_QueryTexture(sprite.getTexture(), NULL, NULL, NULL, &dst.h);
        dst.w = SCREEN_WIDTH;
        dst.h *= 18;
        dst.x = weapon.center.x - camX + 120;
        dst.y = weapon.center.y - dst.h / 2 - camY;

        if (weapon.angle == 180)
            dst.x += -dst.w - 230;

        sprite.Draw(dst.x, dst.y, dst.w, dst.h);
        sprite.PlayFrame(0, 0, dst.w, dst.h, 0);
        sprite.Render(renderer, SDL_FLIP_NONE, weapon.angle);
        return;
    }
    case ELITE_LAVA:
    {
        if (weapon.currentFrame < 9)
        {
            sprite.getResource(renderer, LavaPoolStart_Animation[weapon.currentFrame].c_str());
        }
        else if (weapon.currentFrame > weapon.frames - 6)
        {
            sprite.getResource(renderer, LavaPoolEnd_Animation[weapon.currentFrame - (weapon.frames - 5)].c_str());
        }
        else
        {
            sprite.getResource(renderer, LavaPool.c_str());
        }

        SDL_Rect dst;
        SDL_QueryTexture(sprite.getTexture(), NULL, NULL, &dst.w, &dst.h);
        dst.w *= 2;
        dst.h *= 2;
        dst.x = weapon.center.x - dst.w / 2 - camX;
        dst.y = weapon.center.y - dst.h / 2 - camY;

        sprite.Draw(dst.x, dst.y, dst.w, dst.h);
        sprite.PlayFrame(0, 0, dst.w, dst.h, 0);
        sprite.Render(renderer, SDL_FLIP_NONE, weapon.angle);
        return;
    }
    case FALLING_BLOCKS:
    {
        sprite.getResource(renderer, SuiseiFallingBlocks[weapon.count].c_str());
        sprite.Draw(weapon.center.x - 96 - camX, weapon.center.y - 96 - camY, 192, 192);
        SDL_Rect hitBox{(int)weapon.center.x - 96 - camX, (int)weapon.center.y - 96 - camY, 192, 192};
        sprite.PlayFrame(0, 0, 43, 43, 0);
        sprite.Render(renderer, SDL_FLIP_NONE, 0);
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
        SDL_RenderDrawRect(renderer, &hitBox);
        return;
    }
    }
}

int damageCal(DamagingArea weapon, Player player)
{
    float weaponDamage = weapon.damage / 100;

    float totalWeaponDamage = weaponDamage;

    float attackDamage = 10 * totalWeaponDamage * player.atk / 100;

    if (attackDamage > 2)
    {
        attackDamage += randomFloat(-std::max(attackDamage * 0.1f, 2.0f), std::max(attackDamage * 0.1f, 2.0f));
    }

    return (int)attackDamage;
}

void inflictDamage(DamagingArea &weapon, Player player, int &enemyHealth, bool &isHit, int enemyID)
{
    --weapon.hitLimit;
    isHit = true;
    enemyHealth -= damageCal(weapon, player);
    weapon.hitID[enemyID] = weapon.hitCooldown;
}

bool hitEnemy(DamagingArea &weapon, Circle enemyCollider, int &enemyHealth, bool &isHit, int enemyID, Player player)
{
    if (weapon.hitID.find(enemyID) != weapon.hitID.end())
        return false;

    switch ((int)weapon.weaponID)
    {
    case AXE:
    {
        SDL_Rect hitBox;
        hitBox.w = weapon.size.x * 1.5;
        hitBox.h = weapon.size.y * 1.5;
        hitBox.x = weapon.center.x;
        hitBox.y = weapon.center.y - hitBox.h / 2;
        switch (weapon.angle)
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

        if (checkAABBCircleCollision(hitBox, enemyCollider))
        {
            inflictDamage(weapon, player, enemyHealth, isHit, enemyID);
            return true;
        }
        return false;
    }
    case SPIDER_COOKING:
    {
        if (checkCircleCollision(Circle{weapon.center, 107 * 2 / 2}, enemyCollider))
        {
            inflictDamage(weapon, player, enemyHealth, isHit, enemyID);
            return true;
        }
        return false;
    }
    case CEO_TEARS:
    {
        if (checkCircleCollision(Circle{weapon.center, 8}, enemyCollider))
        {
            inflictDamage(weapon, player, enemyHealth, isHit, enemyID);
            return true;
        }
        return false;
    }
    case FAN_BEAM:
    {
        SDL_Rect hitBox;
        hitBox.w = 460;
        hitBox.h = 13;
        hitBox.x = weapon.center.x + 50;
        hitBox.y = weapon.center.y - hitBox.h / 2;

        if (weapon.angle == 180)
            hitBox.x += -hitBox.w - 100;

        if (checkAABBCircleCollision(hitBox, enemyCollider))
        {
            inflictDamage(weapon, player, enemyHealth, isHit, enemyID);
            return true;
        }
        return false;
    }
    case BL_BOOK:
    {
        if (checkCircleCollision(Circle{weapon.center, 20}, enemyCollider))
        {
            inflictDamage(weapon, player, enemyHealth, isHit, enemyID);
            return true;
        }
        return false;
    }
    case PSYCHO_AXE:
    {
        if (checkCircleCollision(Circle{weapon.center, weapon.size.x * 2 / 3}, enemyCollider))
        {
            inflictDamage(weapon, player, enemyHealth, isHit, enemyID);
            return true;
        }
        return false;
    }
    case IDOL_SONG:
    {
        if (checkCircleCollision(Circle{weapon.center, 28}, enemyCollider))
        {
            inflictDamage(weapon, player, enemyHealth, isHit, enemyID);
            return true;
        }
        return false;
    }
    case ELITE_LAVA:
    {
        if (checkCircleCollision(Circle{weapon.center, 110}, enemyCollider))
        {
            inflictDamage(weapon, player, enemyHealth, isHit, enemyID);
            return true;
        }
        return false;
    }
    case FALLING_BLOCKS:
    {
        SDL_Rect hitBox;
        if(weapon.count >= 0 && weapon.count <= 3)
        {
            switch(weapon.count)
            {
                case 0:
                hitBox = SDL_Rect{(int)weapon.center.x - 96, (int)weapon.center.y, 96,96};
                break;
                case 1:
                hitBox = SDL_Rect{(int)weapon.center.x - 96, (int)weapon.center.y - 96, 96,96};
                break;
                case 2:
                hitBox = SDL_Rect{(int)weapon.center.x, (int)weapon.center.y - 96, 96,96};
                break;
                case 3:
                hitBox = SDL_Rect{(int)weapon.center.x, (int)weapon.center.y, 96,96};
                break;
            }
            if (checkAABBCircleCollision(hitBox, enemyCollider))
            {
                inflictDamage(weapon, player, enemyHealth, isHit, enemyID);
                return true;
            }
        }
        else if(weapon.count >= 4 && weapon.count <= 7)
        {
            switch(weapon.count)
            {
                case 4:
                hitBox = SDL_Rect{(int)weapon.center.x - 96, (int)weapon.center.y, 192,96};
                break;
                case 5:
                hitBox = SDL_Rect{(int)weapon.center.x - 96, (int)weapon.center.y - 96, 96,192};
                break;
                case 6:
                hitBox = SDL_Rect{(int)weapon.center.x - 96, (int)weapon.center.y - 96, 192,96};
                break;
                case 7:
                hitBox = SDL_Rect{(int)weapon.center.x, (int)weapon.center.y-96, 96,192};
                break;
            }
            if (checkAABBCircleCollision(hitBox, enemyCollider))
            {
                inflictDamage(weapon, player, enemyHealth, isHit, enemyID);
                return true;
            }
        }
        else
        {
            hitBox = SDL_Rect{(int)weapon.center.x - 96, (int)weapon.center.y - 96, 192, 192};
            if(!checkAABBCircleCollision(hitBox, enemyCollider)) return false;
            SDL_Rect safeZone;
            switch(weapon.count)
            {
                case 8:
                safeZone = SDL_Rect{(int)weapon.center.x - 96, (int)weapon.center.y-96, 96,96};
                if(enemyCollider.center.x + enemyCollider.radius <= safeZone.x + safeZone.w 
                && enemyCollider.center.y + enemyCollider.radius <= safeZone.y + safeZone.h)
                return false;
                break;
                case 9:
                safeZone = SDL_Rect{(int)weapon.center.x, (int)weapon.center.y - 96, 96,96};
                if(enemyCollider.center.x - enemyCollider.radius >= safeZone.x
                && enemyCollider.center.y + enemyCollider.radius <= safeZone.y + safeZone.h)
                return false;
                break;
                case 10:
                safeZone = SDL_Rect{(int)weapon.center.x, (int)weapon.center.y, 96,96};
                if(enemyCollider.center.x - enemyCollider.radius >= safeZone.x
                && enemyCollider.center.y - enemyCollider.radius >= safeZone.y)
                return false;
                break;
                case 11:
                safeZone = SDL_Rect{(int)weapon.center.x - 96, (int)weapon.center.y, 96,96};
                if(enemyCollider.center.x + enemyCollider.radius <= safeZone.x + safeZone.w 
                && enemyCollider.center.y - enemyCollider.radius >= safeZone.y)
                return false;
                break;
            }
            inflictDamage(weapon, player, enemyHealth, isHit, enemyID);
            return true;
        } 

        return false;
    }
    }

    return false;
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
    }

    return false;
}