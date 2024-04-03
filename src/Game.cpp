
#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Game.hpp"
#include "utils.hpp"
#include "Data.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *p_title, int p_w, int p_h)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL_Init failed. SDL ERROR: " << SDL_GetError();
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "IMG_Init failed. Error: " << IMG_GetError();
	}

	if (TTF_Init() == -1)
	{
		std::cout << "Could not initailize SDL2_ttf, error: " << TTF_GetError() << std::endl;
	}

	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	font = TTF_OpenFont("res/gfx/font/8bitOperatorPlus8-Regular.ttf", 12);
	// Confirm that it was loaded

	if (font == NULL)
	{
		std::cout << "Could not load font" << TTF_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void Game::loadmedia()
{
	tabs_title.setUpMenu(renderer);
	tabs_room1.roomInit(renderer);
	gameState.loadMedia(renderer);
	// playerHUD.initHUD(renderer);
	// playerHUD.HUD_Timer.start();
}

void Game::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
			return;
		}
	}

	switch ((int)currentTab)
	{
	case Title:
		tabs_title.handleEvents();
		currentTab = tabs_title.getDirect();
		break;
	case Room1:
		// tabs_room1.handleEvents();
		currentTab = gameState.getDirect();
		gameState.handleEvent();
		break;
	}
}
// void Game::playMusic()
// {
// 	switch (tabs)
// 	{
// 	case InGame_SoloMode:
// 		if( Mix_PlayingMusic() == 0 && !gameState->isInCountDown() && gameState->getPlaying())
// 		{
// 			Mix_PlayMusic( me_playing, -1 );
// 		}
// 		if (gameState->getPause() && gameState->getPlaying())
// 		{
// 			Mix_HaltMusic();
// 		}
// 		break;
// 	case InGame_BattleMode:
// 		if( Mix_PlayingMusic() == 0 && !battleProcessor->getGameState1()->isInCountDown() && battleProcessor->getGameState1()->getPlaying())
// 		{
// 			Mix_PlayMusic( me_playing, -1 );
// 		}
// 		if (battleProcessor->getGameState1()->getPause() && battleProcessor->getGameState1()->getPlaying())
// 		{
// 			Mix_HaltMusic();
// 		}
// 		break;
// 	default:
// 		if( Mix_PlayingMusic() == 0 ){
// 			Mix_PlayMusic( me_theme, -1 );
// 		}
// 		break;
// 	}
// }

void Game::update(float deltaTime, float currentTime)
{
	switch ((int)currentTab)
	{
	case Title:
		// gameState.reset();
		// playerHUD.HUD_Timer.pause();
		break;
	case Room1:
		// playerHUD.HUD_Timer.unpause();
		// playerHUD.update(gameState.getPlayer(), gameState.reqNextLevel);
		gameState.update(deltaTime, currentTime);
		break;
	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	// static LTexture backGround {backGroundPicture, renderer};
	// backGround.render(renderer, 0, 0);

	switch ((int)currentTab)
	{
	case Title:
		tabs_title.render(renderer);
		break;
	case Room1:
		tabs_room1.render(renderer, gameState.getPlayer().collider.center);
		gameState.render(renderer);
		// playerHUD.render(renderer, gameState.getPause());
		break;
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	font = NULL;
	window = NULL;
	renderer = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}