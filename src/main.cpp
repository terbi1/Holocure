
#include <cstdlib>

#include "utils.hpp"
#include "Game.hpp"

int main(int argc, char *args[])
{
    srand(time(NULL));
    
    Game game;
    game.init("Holocure", SCREEN_WIDTH, SCREEN_HEIGHT);
    game.loadmedia();

    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();

    while (game.running())
    {
        float deltaTime = utils::hireTimeInSeconds() - currentTime;
        currentTime += deltaTime;
        accumulator += deltaTime;

        while (accumulator >= timeStep)
        {
            // time stepping
            accumulator -= timeStep;

            game.handleEvents();
            game.update(timeStep);
        }

        game.playMusic();
        //start drawing
        game.render();
    }

    game.clean();

    return 0;
}