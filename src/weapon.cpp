#include "weapon.hpp"

Weapon::Weapon(WEAPON_ID type, SDL_Renderer* renderer) 
    :ID(type)
{
    switch(ID) {
        case AXE:
        aoe.damage = 10;
        cd = 1000;
        lastAttack = SDL_GetTicks();
        aoe.sprites.getResource(renderer, "res/gfx/spr_SuiseiAxeSwing/spr_SuiseiAxeSwing2.png");
        break;
        case SPIDER_COOKING:
        aoe.damage = 1;
        cd = 1000;
        lastAttack = SDL_GetTicks();
        aoe.sprites.getResource(renderer, "res/gfx/spr_spidercooking.png");
        break;
    }
}

void renderWeapon(SDL_Renderer *renderer, Weapon& weapon, Player player, int frame, int camX, int camY)
{
    switch((int)weapon.ID) 
    {
        case AXE:
        {
        
        if(!weapon.isActive) return; 

        SDL_Rect src;
        src.x = 0; src.y = 0;
        src.w = 107; src.h = 144;

        SDL_Rect dst;
        dst.w = 107 * 2; dst.h = 144 * 2;
        dst.x = player.centerPoint.x - camX; dst.y = player.centerPoint.y - dst.h / 2 -  camY;

        switch (player.arrowAngle)
        {
        case 0:
            break;
        case 180:
            dst.x += -dst.w; 
            break;
        case -90:
            dst.x += -dst.w / 2; dst.y += -dst.w / 2;
            break;
        case 90:
            dst.x += -dst.w / 2 ; dst.y += dst.w / 2;
            break;
        }

        weapon.aoe.sprites.Draw(dst.x, dst.y, dst.w, dst.h);
        weapon.aoe.sprites.PlayFrame(src.x, src.y, src.w, src.h, frame);
        weapon.aoe.sprites.Render(renderer, player.flip, player.arrowAngle);
        return;
        }
        case SPIDER_COOKING:
        {
            weapon.aoe.sprites.Draw(player.centerPoint.x - 107/2 - camX, player.centerPoint.y - 107/2 - camY, 107, 107);
            weapon.aoe.sprites.PlayFrame(0, 0, 107, 107, 0);
            weapon.aoe.sprites.Render(renderer, player.flip, player.arrowAngle);
        }
    }
}

void inflictDamage(Weapon& weapon, Enemy& enemy, Player player, SDL_Renderer* renderer, int camX, int camY) {
    if(!weapon.isActive) return;

    switch((int)weapon.ID) {
        case AXE:
        {
            SDL_Rect hitBox;
            hitBox.w = 107 * 2; hitBox.h = 144 * 2;
            hitBox.x = player.centerPoint.x; hitBox.y = player.centerPoint.y - hitBox.h / 2;

            switch (player.arrowAngle)
            {
            case 0:
                break;
            case 180:
                hitBox.x -= hitBox.w;
                break;
            case -90:
                std::swap(hitBox.w, hitBox.h);
                hitBox.x -= hitBox.w / 2; hitBox.y -= - hitBox.w / 2 + hitBox.h;
                break;
            case 90:
                std::swap(hitBox.w, hitBox.h);
                hitBox.x -= hitBox.w / 2; hitBox.y -= - hitBox.w / 2;
                break;
            }

            if(checkAABBCircleCollision(hitBox, enemy.collider)) {
                enemy.isHit = true;
                enemy.health -= weapon.aoe.damage;
            }

            hitBox.x -= camX; hitBox.y -= camY;
            SDL_SetRenderDrawColor(renderer, 255,0,0,0);
            SDL_RenderDrawRect(renderer, &hitBox);
            
            return;
        }
        case SPIDER_COOKING:
        {

            SDL_Rect hitBox;
            hitBox.x = player.centerPoint.x; hitBox.y = player.centerPoint.y;

            if(checkCircleCollision(Circle{player.centerPoint, 100/2}, enemy.collider)) {
                enemy.isHit = true;
                enemy.health -= weapon.aoe.damage;
            }

            // weapon.aoe.sprites.Draw(player.centerPoint.x - 107/2 - camX, player.centerPoint.y - 107/2 - camY, 107, 107);
            // weapon.aoe.sprites.PlayFrame(0, 0, 107, 107, 0);
            // weapon.aoe.sprites.Render(renderer, player.flip, player.arrowAngle);
        }
    }
}
