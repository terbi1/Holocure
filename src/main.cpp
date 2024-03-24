#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "utils.hpp"
#include "weapon.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "physics.hpp"
#include "drop.hpp"
#include "Game.hpp"
#include "Room1.hpp"
#include "Hud.hpp"

int main(int argc, char *args[])
{
    srand(time(NULL));

    RenderWindow window;
    window.init("Holocure", SCREEN_WIDTH, SCREEN_HEIGHT);
    Tabs_Title titlePage;
    Tabs currentTab = Room1;
    titlePage.setUpMenu(window.getRenderer());
    Tabs_Room1 room;
    room.roomInit(window.getRenderer());
    HUD hud;
    hud.initHUD(window.getRenderer());
    hud.HUD_Timer.start();


    // SDL_Texture *background = window.loadTexture("res/gfx/BG_newgrass.png");
    // SDL_Texture *expBarBase = window.loadTexture("res/gfx/hud_expbar_bg.png");
    // SDL_Texture *expBarTop = window.loadTexture("res/gfx/hud_expbar_anim_89.png");

    SDL_Texture *expDrop = window.loadTexture("res/gfx/spr_EXP/spr_EXP_0.png");

    // Setup the texture
    SDL_Texture *textureText = NULL;

    // Free the surface
    // We are done with it after we have uploaded to the texture

    // SDL_FreeSurface(surfaceText);

    SDL_Rect timeRect;
    timeRect.w = 100;
    timeRect.h = 25;
    timeRect.x = SCREEN_WIDTH / 2 - timeRect.w / 2;
    timeRect.y = 50;

    // SDL_FRect expBaseBar{0, 0, SCREEN_WIDTH, 34};
    // SDL_Rect expTopBarSRC{0, 0, 0, 26};
    // SDL_FRect expTopBar{0, -3, 0, 34};
    // SDL_Rect levelRect{940, 5, 75, 25};

    Player sui(SUISEI, window);
    sui.health.value = 50;
    sui.health.hp = window.loadTexture("res/gfx/hud_HUD_HP_green_0.png");
    sui.health.base = window.loadTexture("res/gfx/hud_HUD_HP_green_1.png");
    sui.health.src = {0, 0, 129, 6};
    sui.arrow = window.loadTexture("res/gfx/spr_Arrow/spr_Arrow_0.png");

    Weapon axe(AXE, window.getRenderer());
    Weapon spiderCooking(SPIDER_COOKING, window.getRenderer());

    std::vector<Enemy> deadgang;
    std::vector<Enemy>::iterator itGang;

    std::vector<Drop> dropItems;
    std::vector<Drop>::iterator itDrop;

    SDL_Event event;

    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();
    float lastSpawn = currentTime;

    bool gameRunning = true;

    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    int frame = 0;
    // int invincibleFrame = 0;
    // int attackFrame = 0;
    int deadFrame = 0;
    int expForNextLevel = 100;

    // In memory text stream
    std::stringstream timeText;
    std::stringstream levelText{"LV: "};
    // float attackTime = 0;

    while (gameRunning)
    {
        // time stepping
        float newTime = utils::hireTimeInSeconds();
        float deltaTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += deltaTime;

        while (accumulator >= timeStep)
        {
            while (SDL_PollEvent(&event) != 0)
            {
                if (event.type == SDL_QUIT)
                {
                    gameRunning = false;
                }
            }

            // time stepping
            accumulator -= timeStep;

            if (currentTab == Room1)
            {
                hud.HUD_Timer.unpause();
                // player event
                sui.handleEvent();
                // spawn enemies
                if (currentTime - lastSpawn >= 1)
                {
                    while (deadgang.size() < 100)
                    {
                        for (int i = 0; i < 5; ++i)
                            spawn(deadgang, window, sui.getPos(), SHRIMP);
                        break;
                    }
                    lastSpawn = currentTime;
                }

                // player move
                sui.move();

                // enemy move
                for (int i = 0; i < (int)deadgang.size(); ++i)
                {
                    deadgang[i].move(sui.getPos());
                }

                for (int i = 0; i < (int)deadgang.size(); ++i)
                {
                    for (int j = 0; j < (int)deadgang.size(); ++j)
                    {
                        if (i == j)
                            continue;
                        if (checkCircleCollision(deadgang[i].collider, deadgang[j].collider))
                        {
                            collisionEvent(deadgang[i], deadgang[j]);
                        }
                    }
                }

                // Center the camera over the dot

                camera.x = (sui.getPos().x + sui.hitBox.w / 2) - SCREEN_WIDTH / 2;
                camera.y = (sui.getPos().y + sui.hitBox.h / 2) - SCREEN_HEIGHT / 2;

                // moving animation frame
                ++frame;
                ++deadFrame;
                if ((frame / 2 / sui.state) > (sui.state - 1))
                {
                    frame = 0;
                }
                if (deadFrame / 4 / 3 > 2)
                {
                    deadFrame = 0;
                }
                // if (axe.isActive)
                // {
                //     if (attackFrame == 4)
                //         for (int i = 0; i < deadgang.size(); ++i)
                //             inflictDamage(axe, deadgang[i], sui, window.getRenderer(), camera.x, camera.y);

                //     ++attackFrame;
                //     if ((attackFrame / 4) > 5)
                //     {
                //         attackFrame = 0;
                //         axe.isActive = false;
                //         axe.lastAttack = SDL_GetTicks();
                //     }
                // }
                // for (auto itGang = deadgang.begin(); itGang != deadgang.end(); ++itGang)
                // {
                //     inflictDamage(spiderCooking, *itGang, sui, window.getRenderer(), camera.x, camera.y);
                //     if (itGang->health <= 0)
                //     {
                //         dropItems.push_back(Drop(EXP, itGang->collider.center));
                //         deadgang.erase(itGang);
                //     }
                // }
                if (dropItems.size() > 0)
                    for (auto itDrop = dropItems.begin(); itDrop != dropItems.end(); ++itDrop)
                    {
                        if (dropItems.size() <= 0)
                            break;
                        Vector2f temp = itDrop->pos;
                        float dis = distance(sui.centerPoint, temp);
                        if (dis <= 10.0)
                        {
                            dropItems.erase(itDrop);
                            sui.currentExp += 1000;
                            --itDrop;
                        }
                        else
                            itDrop->pickedUp(sui.centerPoint);
                    }
                while (sui.currentExp >= expForNextLevel)
                {
                    sui.currentExp -= expForNextLevel;
                    expForNextLevel += 50;
                    ++sui.LEVEL;
                }
                // expTopBarSRC.w = sui.currentExp / expForNextLevel * 648;
                // expTopBar.w = sui.currentExp / expForNextLevel * (SCREEN_WIDTH + 10);
                // levelText.str("");
                // levelText << "LV: "<< sui.LEVEL;
                hud.update(sui, expForNextLevel);
                room.handleEvents();
                currentTab = room.getDirect();
            }
            else
            {
                hud.HUD_Timer.pause();
                titlePage.handleEvents();
                currentTab = titlePage.getDirect();
            }
        }

        // clear window
        window.clear();
        switch ((int)currentTab)
        {
        case Room1:
        {
            // timeText.str("");
            // Uint32 minute = timer.getTicks(Minute);
            // Uint32 second = timer.getTicks(Second) - minute * 60;
            // int minute = utils::timeInMinutes(SDL_GetTicks() - startTime);
            // int second = utils::timeInSeconds(SDL_GetTicks() - startTime) - minute * 60;
            // if (minute < 10) timeText << 0;
            // timeText << minute << ":";
            // if (second < 10) timeText << 0;
            // timeText << second;
            // start drawing
            // window.renderBackground(background, camera);
            // window.tiledRender(background, camera, sui.getPos());
            room.render(window.getRenderer(), sui.getPos());
            // sui.health.dst = {sui.hitBox.x, sui.hitBox.y + sui.hitBox.h, sui.hitBox.w, 6};
            // inflictDamage(axe, deadbeat, sui, window.getRenderer(), camera.x, camera.y);

            for (int i = 0; i < (int)dropItems.size(); ++i)
            {
                SDL_Rect dst{dropItems[i].pos.x - camera.x, dropItems[i].pos.y - camera.y, int(12 * 1.5), int(13 * 1.5)};
                SDL_RenderCopy(window.getRenderer(), expDrop, NULL, &dst);
                SDL_RenderDrawPoint(window.getRenderer(), dropItems[i].pos.x - camera.x, dropItems[i].pos.y - camera.y);
            }

            for (int i = 0; i < (int)deadgang.size(); ++i)
            {
                deadgang[i].render(window.getRenderer(), deadFrame / 4 / 3, camera.x, camera.y);
            }

            // renderWeapon(window.getRenderer(), axe, sui, attackFrame / 4, camera.x, camera.y);

            // if (!axe.isActive)
            // {

            //     axe.timePassed = SDL_GetTicks() - axe.lastAttack;

            //     if (axe.timePassed >= axe.cd)
            //     {
            //         axe.isActive = true;
            //         axe.timePassed = 0;
            //     }
            // }

            // renderWeapon(window.getRenderer(), spiderCooking, sui, 0, camera.x, camera.y);

            sui.render(window.getRenderer(), frame / 2 / sui.state, camera.x, camera.y);

            // SDL_RenderCopyF(window.getRenderer(), expBarBase, NULL, &expBaseBar);
            // SDL_RenderCopyF(window.getRenderer(), expBarTop, &expTopBarSRC, &expTopBar);
            // window.loadFromRenderedText(levelText.str().c_str(), {255,255,255}, textureText);
            // SDL_RenderCopy(window.getRenderer(),textureText,NULL,&levelRect);

            hud.render(window.getRenderer());

            // window.loadFromRenderedText(timeText.str().c_str(), {255, 255, 255}, textureText);
            // SDL_RenderCopy(window.getRenderer(), textureText, NULL, &timeRect);
            break;
        }

        case Title:
        {
            titlePage.render(window.getRenderer());
            break;
        }
        }

        window.display();
    }

    // free texture
    for (int i = 0; i < 4; ++i)
    {
        SDL_DestroyTexture(sui.idleAnimation[i]);
        sui.idleAnimation[i] = NULL;
    }
    for (int i = 0; i < 5; ++i)
    {
        SDL_DestroyTexture(sui.runAnimation[i]);
        sui.runAnimation[i] = NULL;
    }

    SDL_DestroyTexture(axe.aoe.sprites.getTexture());

    SDL_DestroyTexture(textureText);

    window.cleanUp();

    return 0;
}