
#include <iostream>
#include <algorithm>

#include "Structure.hpp"

#pragma region LTexture

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	free();
	// if(mTexture == NULL) std::cout << 1;
}

void LTexture::importTexture(SDL_Texture *texture)
{
	mTexture = texture;
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer *gRenderer)
{
	free();

	SDL_Texture *newTexture = NULL;

	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image! SDL_image Error: " << path.c_str() << IMG_GetError() << '\n';
		return false;
	}

	// SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if (newTexture == NULL)
	{
		std::cout << "Unable to create texture from! SDL Error: " << path.c_str() << SDL_GetError() << '\n';
		return false;
	}

	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	SDL_FreeSurface(loadedSurface);

	mTexture = newTexture;

	return (mTexture != NULL);
}

// #if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *gFont, SDL_Renderer *gRenderer)
{
	free();

	SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << '\n';
		return false;
	}

	mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

	if (mTexture == NULL)
	{
		std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << '\n';
		return false;
	}

	mWidth = textSurface->w;
	mHeight = textSurface->h;

	SDL_FreeSurface(textSurface);

	return mTexture != NULL;
}
// #endif

void LTexture::free()
{
	if (mTexture == NULL)
		return;

	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(SDL_Renderer *gRenderer, SDL_Rect *renderQuad, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	if (renderQuad == NULL)
	{
		renderQuad->x = 0;
		renderQuad->y = 0;
		renderQuad->w = mWidth;
		renderQuad->h = mHeight;
	}

	// if( clip == NULL ) return;

	// renderQuad.w = clip->w;
	// renderQuad.h = clip->h;

	SDL_RenderCopyEx(gRenderer, mTexture, clip, renderQuad, angle, center, flip);
}

void LTexture::renderText(std::string textureText, SDL_Color textColor, TTF_Font *gFont, SDL_Renderer *gRenderer, int x, int y, int size, int wrappingSize)
{
	free();

	TTF_SetFontSize(gFont, size);
	SDL_Surface *textSurface = TTF_RenderText_Solid_Wrapped(gFont, textureText.c_str(), textColor, wrappingSize);
	// SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << '\n';
		return;
	}

	mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

	if (mTexture == NULL)
	{
		std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << '\n';
		return;
	}

	mWidth = textSurface->w;
	mHeight = textSurface->h;

	SDL_Rect textBox{x, y, 0, 0};
	textBox.w = textSurface->w;
	textBox.h = textSurface->h;
	SDL_FreeSurface(textSurface);

	// TTF_SizeText(gFont, textureText.c_str(), &textBox.w, &textBox.h);
	SDL_RenderCopy(gRenderer, mTexture, NULL, &textBox);
}

void LTexture::renderF(SDL_Renderer *gRenderer, SDL_FRect *renderQuad, SDL_Rect *clip, double angle, SDL_FPoint *center, SDL_RendererFlip flip)
{
	if (renderQuad == NULL)
	{
		renderQuad->x = 0;
		renderQuad->y = 0;
		renderQuad->w = mWidth;
		renderQuad->h = mHeight;
	}

	// if( clip == NULL ) return;

	// renderQuad.w = clip->w;
	// renderQuad.h = clip->h;

	SDL_RenderCopyExF(gRenderer, mTexture, clip, renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

SDL_Texture *LTexture::getTexture()
{
	return mTexture;
}

#pragma endregion

#pragma region LTimer

LTimer::LTimer()
{
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}

void LTimer::start()
{
	mStarted = true;

	mPaused = false;

	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void LTimer::stop()
{
	mStarted = false;

	mPaused = false;

	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause()
{
	if (mStarted && !mPaused)
	{
		mPaused = true;

		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void LTimer::unpause()
{
	if (mStarted && mPaused)
	{
		mPaused = false;

		mStartTicks = SDL_GetTicks() - mPausedTicks;

		mPausedTicks = 0;
	}
}

Uint32 LTimer::getTicks(TimeUnit unit)
{
	Uint32 time = 0;

	if (!mStarted)
		return 0;

	if (mPaused)
	{
		time = mPausedTicks;
	}
	else
	{
		time = SDL_GetTicks() - mStartTicks;
	}

	switch (unit)
	{
	case Milisecond:
		return time;
	case Second:
		return (time / 1000);
	case Minute:
		return (time / 1000 / 60);
	}

	return 0;
}

bool LTimer::isStarted()
{
	return mStarted;
}

bool LTimer::isPaused()
{
	return mPaused && mStarted;
}

#pragma endregion LTimer

#pragma region DamageNumber

void DamageNumber::render(SDL_Renderer *renderer, TTF_Font *font, LTexture textureText, int camX, int camY)
{
	// dmgBox.x -= camX;
	// dmgBox.y -= camY;
	textureText.renderText(std::to_string(dmg), color, font, renderer, dmgBox.x - camX, dmgBox.y - camY, 24 + dmg / 10 * 2);
}

void DamageNumber::update(float timeStep)
{
	dmgBox.y -= 1;
	duration -= timeStep;
}

#pragma endregion

#pragma region LButton

LButton::LButton()
{
}

void LButton::render(SDL_Renderer *renderer, TTF_Font *font)
{
	// if(!isCurrentButton) texture[0].render(renderer, &box);
	// else texture[0].render(renderer, &box);

	SDL_Rect renderBox;

	if (!isCurrentButton)
	{
		if (type == 0)
			texture = Button[0];
		else if (type == 1)
			texture = Upgrade[0];
		else{
			texture = Black_Screen;
		}
		color = {255, 255, 255};
	}
	else
	{
		if (type == 0)
			{texture = Button[1];
			color = {0, 0, 0};}
		else if(type == 1)
			{texture = Upgrade[1];
			color = {255,255,255};}
		
	}

	if (isCurrentButton && type == 0)
	{
		renderBox.x = center.x - size.x * 1.1 / 2;
		renderBox.y = center.y - size.y / 2;
		renderBox.w = size.x * 1.1;
		renderBox.h = size.y;
	}
	else
	{
		renderBox.x = center.x - size.x / 2;
		renderBox.y = center.y - size.y / 2;
		renderBox.w = size.x;
		renderBox.h = size.y;
	}

	if(!(type == 2 && isCurrentButton))
	SDL_RenderCopy(renderer, ResourceManager::getInstance().getTexture(texture, renderer), NULL, &renderBox);
	if (font == NULL)
		return;
	int tempW, tempH;
	TTF_SetFontSize(font, 24);
	TTF_SizeText(font, text.c_str(), &tempW, &tempH);
	if(type == 0) textureText.renderText(text, color, font, renderer, renderBox.x + renderBox.w / 2 - tempW / 2, renderBox.y + renderBox.h / 2 - tempH / 2, 24);
	else textureText.renderText(text, color, font, renderer, 350, renderBox.y + renderBox.h / 2 - tempH / 2 - 10, 22);
}

bool LButton::handleEvent()
{
	const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_Z] || currentKeyStates[SDL_SCANCODE_KP_ENTER])
	{
		return true;
	}

	return false;
}

#pragma endregion LButton