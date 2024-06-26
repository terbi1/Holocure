#pragma once

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <algorithm>   

#include "Data.hpp"
#include "Structure.hpp"
#include "math.hpp"
#include "ResourceManager.hpp"

enum TimeUnit
{
	Milisecond,
	Second,
	Minute
};

class LTexture
{
public:
	LTexture();
	~LTexture();
	bool loadFromFile( std::string path, SDL_Renderer* gRenderer );
	void importTexture(SDL_Texture* texture);
	void getResource(SDL_Renderer* renderer, const char* filepath);
	bool loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* gFont1, SDL_Renderer* gRenderer );
	void free();
	void setColor( Uint8 red, Uint8 green, Uint8 blue );
	void setBlendMode( SDL_BlendMode blending );
	void setAlpha( Uint8 alpha );
	void render(SDL_Renderer* gRenderer, SDL_Rect* renderQuad = NULL, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
	void renderText(std::string textureText, SDL_Color textColor, TTF_Font* gFont, SDL_Renderer* gRenderer, int x, int y, int size, int wrappingSize = 600);
	void renderF(SDL_Renderer* gRenderer, SDL_FRect* renderQuad = NULL, SDL_Rect* clip = NULL, double angle = 0.0, SDL_FPoint* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
	int getWidth();
	int getHeight();
	SDL_Texture* getTexture();
	SDL_Texture* mTexture;
private:
	int mWidth;
	int mHeight;
};

class LTimer
{
public:
	LTimer();
	void start();
	void stop();
	void pause();
	void unpause();
	Uint32 getTicks(TimeUnit unit);
	Uint32 timeInSeconds();
	Uint32 timeInMinutes();
	bool isStarted();
	bool isPaused();
private:
	Uint32 mStartTicks;
	Uint32 mPausedTicks;
	bool mPaused;
	bool mStarted;
};

struct DamageNumber
{
    int dmg{};
    Vector2f pos;
    SDL_Color color;
    SDL_Rect dmgBox{(int)pos.x, (int)pos.y, 18, 18};
    float duration{0.3};
    void render(SDL_Renderer* renderer, TTF_Font* font, LTexture textureText, int camX, int camY);
    void update(float timeStep);
};

class LButton
{
public:
LButton();
LButton(std::string m_text, Vector2f m_center, Vector2f m_size, int m_type)
	:text(m_text), center(m_center), size(m_size), type(m_type)
{}
void render(SDL_Renderer* renderer, TTF_Font* font = NULL);
void setCurrentButton()
{
	isCurrentButton = true;
}
void notCurrentButton()
{
	isCurrentButton = false;
}
bool getState()
{
	return isCurrentButton;
}
bool handleEvent();
void setText(std::string m_text)
{
	text = m_text;
}
Vector2f getCenter()
{
	return center;
}
private:
std::string text{};
Vector2f center;
Vector2f size;
int type;
SDL_Rect box;
SDL_Color color;
LTexture textureText;
std::string texture;
bool isCurrentButton{false};
};