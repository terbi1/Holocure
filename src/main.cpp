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
#include "GameState.hpp"
#include "Tabs_Title.hpp"

int main(int argc, char *args[])
{
    srand(time(NULL));

    // RenderWindow window;
    // window.init("Holocure", SCREEN_WIDTH, SCREEN_HEIGHT);
    // Tabs_Title titlePage;
    // Tabs currentTab = Title;
    // titlePage.setUpMenu(window.getRenderer());
    // Tabs_Room1 room;
    // room.roomInit(window.getRenderer());
    // HUD hud;
    // hud.initHUD(window.getRenderer());
    // hud.HUD_Timer.start();
    
    Game game;
    game.init("Holocure", SCREEN_WIDTH, SCREEN_HEIGHT);
    game.loadmedia();

    // GameState test;
    // test.loadMedia(window.getRenderer());

    // Player sui;
    // sui.health.value = 50;
    // sui.health.hp = window.loadTexture("res/gfx/hud_HUD_HP_green_0.png");
    // sui.health.base = window.loadTexture("res/gfx/hud_HUD_HP_green_1.png");
    // sui.health.src = {0, 0, 129, 6};
    // sui.arrow = window.loadTexture("res/gfx/spr_Arrow/spr_Arrow_0.png");

    SDL_Event event;

    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();
    
    // float lastSpawn = currentTime;

    bool gameRunning = true;

    // SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    // int frame = 0;
    // int invincibleFrame = 0;
    // int attackFrame = 0;
    // int deadFrame = 0;
    // int expForNextLevel = 100;
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

            // if (currentTab == Room1)
            // {
            //     hud.HUD_Timer.unpause();
            //     test.update(currentTime);
            //     hud.update(test.getPlayer(), test.reqNextLevel);
            //     room.handleEvents();
            //     currentTab = room.getDirect();
            // }
            // else
            // {
            //     hud.HUD_Timer.pause();
            //     titlePage.handleEvents();
            //     currentTab = titlePage.getDirect();
            // }

            game.handleEvents();
            game.update(currentTime);
        }

        // clear window
        // window.clear();

        //start drawing
        // switch ((int)currentTab)
        // {
        // case Room1:
        // {
        //     room.render(window.getRenderer(), test.getPlayer().getPos());
        //     // sui.health.dst = {sui.hitBox.x, sui.hitBox.y + sui.hitBox.h, sui.hitBox.w, 6};
        //     // inflictDamage(axe, deadbeat, sui, window.getRenderer(), camera.x, camera.y);

        //     // renderWeapon(window.getRenderer(), axe, sui, attackFrame / 4, camera.x, camera.y);

        //     test.render(window.getRenderer());

        //     hud.render(window.getRenderer());

        //     break;
        // }

        // case Title:
        // {
        //     titlePage.render(window.getRenderer());
        //     break;
        // }
        // }

        // window.display();
        game.render();
    }

    // window.cleanUp();
    game.clean();

    return 0;
}