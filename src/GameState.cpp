
#include <sstream>

#include "GameState.hpp"

Game_State::Game_State() 
{
}

Game_State::~Game_State() 
{
}

Tabs Game_State::getDirect() {
    return direct;
}

void setUpPlayRoom(SDL_Renderer* renderer) {

}

void Game_State::render(SDL_Renderer* renderer)
{
	// std::stringstream timeText;

    // Center the camera over the dot
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    camera.x = (player.getPos().x + player.hitBox.w / 2) - SCREEN_WIDTH / 2;
    camera.y = (player.getPos().y + player.hitBox.h / 2) - SCREEN_HEIGHT / 2;
    camera.w = SCREEN_WIDTH; camera.h = SCREEN_HEIGHT;

    player.render(renderer, player.currentFrame, camera.x, camera.y);

    // timeText.str("");
    //     // int minute = (SDL_GetTicks() - startTime) / 1000 / 60;
    //     int minute = utils::timeInMinutes(SDL_GetTicks() - startTime);
    //     int second = utils::timeInSeconds(SDL_GetTicks() - startTime) - minute * 60;
    //     if(minute < 10) timeText << 0;
	// 	timeText << minute << ":";
    //     if(second < 10) timeText << 0;
    //     timeText << second; 
        // start drawing
        // window.renderBackground(background, camera);
        // window.tiledRender(background, camera, sui.getPos());
        // // sui.health.dst = {sui.hitBox.x, sui.hitBox.y + sui.hitBox.h, sui.hitBox.w, 6};
        // // inflictDamage(axe, deadbeat, sui, window.getRenderer(), camera.x, camera.y);

        // for(int i = 0; i < (int)dropItems.size(); ++i) {
        //     SDL_Rect dst{dropItems[i].pos.x - camera.x,dropItems[i].pos.y - camera.y, int(12 * 1.5), int(13 * 1.5)};
        //     SDL_RenderCopy(window.getRenderer(), expDrop, NULL, &dst);
        //     SDL_RenderDrawPoint(window.getRenderer(), dropItems[i].pos.x - camera.x, dropItems[i].pos.y - camera.y);
        // }

        // // for(int i = 0; i < (int)enemies.size(); ++i) {
        // for(auto it = enemies.begin(); it != enemies.end(); ++it) {
        //     it -> render(window.getRenderer(), deadFrame / 4 / 3, camera.x, camera.y);
        // }
}

void Game_State::reset()
{
}

void Game_State::handleEvent()
{
}

void Game_State::update() 
{
    // player event

    // spawn enemies
    // if(currentTime - lastSpawn >= 1) {
    // while(enemies.size() < 100) {
    //     for(int i = 0; i < 5; ++i)
    //         spawn(enemies, renderer, player.getPos());
    //     break;
    // }
    //     lastSpawn = currentTime;
    // }
    
    // player event
    player.handleEvent();
    player.move();

    //enemy move
    for(int i = 0; i < (int)enemies.size(); ++i) {
        enemies[i].move(player.getPos());
    }
    for(int i = 0; i < (int)enemies.size(); ++i) {
        for(int j = 0; j < (int)enemies.size(); ++j) {
            if(i == j) continue;
            if(checkCircleCollision(enemies[i].collider, enemies[j].collider)) {
                collisionEvent(enemies[i], enemies[j]);
            }
        }
    }

    // moving animation frame
    // ++frame;
    ++player.currentFrame;
    if ((player.currentFrame / 2 / player.state) > (player.state - 1))
    {
        player.currentFrame = 0;
    }
    //
    // ++deadFrame;
    // if (deadFrame / 4 / 3 > 2)
    // {
    //     deadFrame = 0;
    // }
    // if(axe.isActive)
    // {
    //     if(attackFrame == 4)
    //         for(int i = 0; i < enemies.size(); ++i)
    //             inflictDamage(axe, enemies[i], player,windowgetRenderer(), camera.x, camera.y);
    //     ++attackFrame;
    //     if ((attackFrame / 4) > 5)
    //     {
    //         attackFrame = 0;
    //         axe.isActive = false;
    //         axe.lastAttack = SDL_GetTicks();
    //     }
    // }
    // for (auto itGang = enemies.begin(); itGang != enemies.end()++itGang)
    // {
    //     inflictDamage(spiderCooking, *itGang, player, windowgetRendere(), camera.x, camera.y);
    //     if(itGang -> health <= 0) {
    //         dropItems.push_back(Drop(EXP, itGang -> collidercenter));
    //         enemies.erase(itGang);
    //     }
    // }
    if(dropItems.size() > 0)
    for(auto itDrop = dropItems.begin(); itDrop != dropItems.end(); ++itDrop) {
        if(dropItems.size() <= 0) break;
        Vector2f temp = itDrop -> pos;
        float dis = distance(player.centerPoint, temp);
        std::cout << dis;
        if(dis <= 10.0){
            dropItems.erase(itDrop);
            player.currentExp += 1000;
            --itDrop;
        }
        else itDrop->pickedUp(player.centerPoint);
    }

    // while(player.currentExp >= expForNextLevel) {
    //     player.currentExp -= expForNextLevel;
    //     expForNextLevel += 50;
    //     ++player.LEVEL;
    // }
    // expTopBarSRC.w = player.currentExp / expForNextLevel * 648;
    // expTopBar.w = player.currentExp / expForNextLevel *(SCREEN_WIDTH +10);
}
