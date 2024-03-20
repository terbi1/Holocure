#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "RenderWindow.hpp"

void init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL_Init failed. SDL ERROR: " << SDL_GetError();
    }

    if (!IMG_Init(IMG_INIT_PNG))
    {
        std::cout << "IMG_Init failed. Error: " << IMG_GetError();
    }

    if(TTF_Init() == -1){
        std::cout << "Could not initailize SDL2_ttf, error: " << TTF_GetError() << std::endl; 
    }

}

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if(window == NULL) {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    }

    font = TTF_OpenFont("res/gfx/font/8bitOperatorPlus8-Regular.ttf",12);
    // Confirm that it was loaded

    if(font == NULL){
        std::cout << "Could not load font" << TTF_GetError() <<std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath) {
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if(texture == NULL) {
        std::cout << "Failed to load texture. Error: " << IMG_GetError() << std::endl;
    }

    return texture;
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp() {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

}

void RenderWindow::renderBackground(int x, int y, SDL_Texture* background, int camX, int camY) { 
    SDL_Rect dst;
    dst.x = x; dst.y = y;
    dst.w = BACKGROUND_WIDTH * 2; dst.h = BACKGROUND_HEIGHT * 2;

    SDL_RenderCopy(renderer, background, NULL, &dst);
}

SDL_Renderer* RenderWindow::getRenderer() {
    return renderer;
}

TTF_Font* RenderWindow::getFont() {
    return font;
}

void RenderWindow::tiledRender(SDL_Texture* background, SDL_Rect camera, Vector2f player_pos)
{
    int addX = ceil(player_pos.x / 2560);
    int addY = ceil(player_pos.y / 2560);
    
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			int posX = player_pos.x + x * 2560 - addX * 2560;
			int posY = player_pos.y + y * 2560 - addY * 2560;

            renderBackground(-posX, -posY, background, camera.x, camera.y);
		}
	}
    // SDL_RenderDrawRect(renderer, &camera);
    // std::cout << camera.x << ',' << camera.y << std::endl;
}

bool RenderWindow::loadFromRenderedText(std::string text, SDL_Color textColor, SDL_Texture* &textureText)
{

	//Render text surface
	SDL_Surface* surfaceText = TTF_RenderText_Solid(font, text.c_str(), textColor );
	if( surfaceText != NULL )
	{
		textureText = SDL_CreateTextureFromSurface(renderer,surfaceText);

		//Get rid of old surface
		SDL_FreeSurface( surfaceText );
	}
	else
	{
		std::cout << "Unable to render text surface! SDL_ttf Error\n" << TTF_GetError();
	}

	//Return success
	return surfaceText != NULL;
}