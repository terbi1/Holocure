
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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }
    Mix_VolumeMusic(64);    

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void Game::loadmedia()
{
	tabs_title.setUpMenu(renderer);
	tabs_characterSelect.setUp(renderer);
	tabs_modeselect.setUp(renderer);
	tabs_room1.roomInit(renderer);
	tabs_levelup.setUp(renderer);
	tabs_end.setUp(renderer);
	gameState.loadMedia(renderer);
    titleMusic = Mix_LoadMUS("res/gfx/bgm/bgm_SSS.ogg");
    roomMusic = Mix_LoadMUS("res/gfx/bgm/bgm_suspect.ogg");
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
		tabs_title.handleEvents(isRunning);
		currentTab = tabs_title.getDirect();
		break;
	case Character_Select:
		tabs_characterSelect.handleEvents(gameState.ID);
		currentTab = tabs_characterSelect.getDirect();
		break;
	case Mode_Select:
		tabs_modeselect.handleEvents(gameState.endless);
		currentTab = tabs_modeselect.getDirect();
		if(currentTab == Room1) gameState.start();
		break;
	case Room1:
		gameState.handleEvent();
		currentTab = gameState.getDirect();
		if(currentTab == Title || currentTab == End) gameState.reset();
		break;
	case Level_Up:
		tabs_levelup.handleEvents(gameState.leveledUp, gameState.choice);
		currentTab = tabs_levelup.getDirect();
		break;
	case End:
		tabs_end.handleEvents();
		currentTab = tabs_end.getDirect();
		if(currentTab == Room1) gameState.start();
		break;
	}
}
void Game::playMusic()
{
	switch ((int)currentTab)
	{
		case Title:
		if( Mix_PlayingMusic() == 0 )
		{
			Mix_VolumeMusic(64);
			Mix_PlayMusic(titleMusic, -1);
		}
		return;
		case Room1:
		if( Mix_PlayingMusic() == 0 )
		{
			Mix_PlayMusic(roomMusic, -1);
		}
		return;
		case Level_Up:
		case Character_Select:
		case Mode_Select:
		return;
		case End:
		Mix_HaltMusic();
		return;
	}
}

void Game::update(float timeStep)
{
	switch ((int)currentTab)
	{
	case Title:
		break;
	case Character_Select:
		tabs_characterSelect.update(timeStep);
		break;
	case Mode_Select:
		tabs_modeselect.update(timeStep);
		break;
	case Room1:
		gameState.update(timeStep, shake);
		break;
	case Level_Up:
		tabs_levelup.getResource(gameState.optionKey, gameState.optionLevel);
		break;
	case End:
		tabs_end.update(gameState.getOver());
		break;
	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	switch ((int)currentTab)
	{
	case Title:
		tabs_title.render(renderer);
		break;
	case Character_Select:
		tabs_characterSelect.render(renderer, font);
		break;
	case Mode_Select:
		tabs_modeselect.render(renderer, font);
		break;
	case Room1:
		tabs_room1.render(renderer, gameState.getPlayer().collider.center, shake);
		gameState.render(renderer, shake);
		break;
	case Level_Up:
		tabs_room1.render(renderer, gameState.getPlayer().collider.center, shake);
		gameState.render(renderer, shake);
		tabs_levelup.render(renderer, font);
		break;
	case End:
		tabs_room1.render(renderer, gameState.getPlayer().collider.center, shake);
		gameState.render(renderer, shake);
		tabs_end.render(renderer, font);
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

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}