#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

#include "math.hpp"
#include "Data.hpp"

class RenderWindow 
{    
public:
    RenderWindow();
    ~RenderWindow();

    void init(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filePath);
    void cleanUp();
    void clear();
    void display();
    void renderBackground(int x, int y, SDL_Texture* background, int camX, int camY);
    SDL_Renderer* getRenderer();
    TTF_Font* getFont();
    void tiledRender(SDL_Texture* background, SDL_Rect camera, Vector2f player_pos);
    bool loadFromRenderedText( std::string text, SDL_Color textColor, SDL_Texture* &textureText);
private:
    TTF_Font* font = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;
    int tabs;
};

    

    