
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
	// free();
	// if(mTexture == NULL) std::cout << 1;
}

void LTexture::importTexture(SDL_Texture* texture)
{
	mTexture = texture;
}

bool LTexture::loadFromFile( std::string path, SDL_Renderer* gRenderer)
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		std::cout <<  "Unable to load image! SDL_image Error: " << path.c_str() << IMG_GetError() <<'\n';
        return false;
	}

	// SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
	if( newTexture == NULL )
	{
		std::cout << "Unable to create texture from! SDL Error: " << path.c_str() << SDL_GetError() <<'\n';
        return false;
	}
	
	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;
	
	SDL_FreeSurface( loadedSurface );
	
    mTexture = newTexture;
	
	return (mTexture!=NULL);
}

// #if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* gFont, SDL_Renderer* gRenderer )
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL ) {
        std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << '\n';
        return false;
    }

    mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );

	if( mTexture == NULL )
	{
		std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << '\n';
        return false;
	}
	
	mWidth = textSurface->w;
	mHeight = textSurface->h;
	
	SDL_FreeSurface( textSurface );
	
	return mTexture != NULL;
}
// #endif

void LTexture::free()
{
	if( mTexture == NULL ) return;
	
	SDL_DestroyTexture( mTexture );
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render(SDL_Renderer* gRenderer, SDL_Rect* renderQuad, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    if(renderQuad == NULL) {
        renderQuad -> x = 0;
        renderQuad -> y = 0;
        renderQuad -> w = mWidth;
        renderQuad -> h = mHeight;
    }

	// if( clip == NULL ) return;
	
	// renderQuad.w = clip->w;
	// renderQuad.h = clip->h;
	
	SDL_RenderCopyEx( gRenderer, mTexture, clip, renderQuad, angle, center, flip );
}

void LTexture::renderF(SDL_Renderer* gRenderer, SDL_FRect* renderQuad, SDL_Rect* clip, double angle, SDL_FPoint* center, SDL_RendererFlip flip )
{
    if(renderQuad == NULL) {
        renderQuad -> x = 0;
        renderQuad -> y = 0;
        renderQuad -> w = mWidth;
        renderQuad -> h = mHeight;
    }

	// if( clip == NULL ) return;
	
	// renderQuad.w = clip->w;
	// renderQuad.h = clip->h;
	
	SDL_RenderCopyExF( gRenderer, mTexture, clip, renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

SDL_Texture* LTexture::getTexture()
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
    if( mStarted && !mPaused )
    {
        mPaused = true;

        mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
    }
}

void LTimer::unpause()
{
    if( mStarted && mPaused )
    {
        mPaused = false;

        mStartTicks = SDL_GetTicks() - mPausedTicks;

        mPausedTicks = 0;
    }
}

Uint32 LTimer::getTicks(TimeUnit unit)
{
	Uint32 time = 0;

	if(!mStarted) return 0;

    
    if( mPaused )
    {
        time = mPausedTicks;
    }
    else
    {
        time = SDL_GetTicks() - mStartTicks;
    }
    
	switch(unit)
	{
		case Milisecond: return time;
		case Second: return (time / 1000);
		case Minute: return (time / 1000 / 60);
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


void DamageNumber::render(SDL_Renderer* renderer, TTF_Font* font, LTexture textureText, int camX, int camY)
{
	dmgBox.x -= camX;
	dmgBox.y -= camY;
	std::string dmgText = std::to_string(dmg);
    textureText.loadFromRenderedText(dmgText,color,font, renderer);
    textureText.render(renderer, &dmgBox);
}

void DamageNumber::update(float timeStep)
{
    dmgBox.y -= 1;
    duration -= timeStep;
}
// FPS_Processor::FPS_Processor()
// {
// 	countedFrames = 0;
// 	gFPSTextTexture = new LTexture;
// 	fpsTimer = new LTimer;
// 	capTimer = new LTimer;
// }
// FPS_Processor::~FPS_Processor()
// {
// 	gFPSTextTexture->free();
// 	delete fpsTimer;
// 	delete capTimer;
// }
// void FPS_Processor::initTimeCounting()
// {
// 	fpsTimer->start();
// }
// void FPS_Processor::cappingFrame()
// {
// 	capTimer->start();
// 	++countedFrames;
// 	int frameTicks = capTimer->getTicks();
// 	if( frameTicks < SCREEN_TICK_PER_FRAME )
// 	{
// 		//Wait remaining time
// 		SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
// 	}
// }
// void FPS_Processor::printFPS(SDL_Renderer* renderer, TTF_Font* gFont){
// 	int avgFPS = countedFrames / ( fpsTimer->getTicks() / 1000.f );
// 	std::stringstream timeText;
// 	timeText.str( "" );
// 	timeText << "FPS: " << avgFPS; 
// 	SDL_Color textColor = { 0, 0, 0, 255 };
// 	if( !gFPSTextTexture->loadFromRenderedText( timeText.str().c_str(), textColor, gFont, renderer ))
// 	{
// 		printf( "Unable to render FPS texture!\n" );
// 	}
// 	gFPSTextTexture->render( renderer,( SCREEN_WIDTH - gFPSTextTexture->getWidth() ), 0 );
// }

// LButton::LButton(){
// 	keyDown = new LTexture;
// 	keyUp = new LTexture;
// 	inside = 0;
// 	pressed = 0;
// 	xPos = 0; yPos = 0; xCen = 0; yCen = 0;
// }
// LButton::LButton(LTexture* _keyUp, LTexture* _keyDown)
// {
// 	motionMouse = 0;
// 	keyUp = _keyUp;
// 	keyDown = _keyDown;
// 	width = keyUp->getWidth();
// 	height = keyUp->getHeight();
// 	xPos = 0; yPos = 0; xCen = 0; yCen = 0;
// }
// LButton::~LButton(){
// 	keyUp->free();
// 	keyDown->free();
// 	delete keyUp;
// 	delete keyDown;
// }
// bool LButton::getPressed()
// {
// 	return pressed;
// }
// bool LButton::getInside()
// {
// 	return inside;
// }
// int LButton::getXCen(){return xCen;}
// int LButton::getYCen(){return yCen;}
// int LButton::getXPos(){return xPos;}
// int LButton::getYPos(){return yPos;}
// int LButton::getWidth(){return width;}
// int LButton::getHeight(){return height;}
// void LButton::setSize(int w, int h){width = w; height = h;}
// void LButton::setPressed(bool _pressed){pressed = _pressed;}
// void LButton::setTexture(LTexture* _keyUp, LTexture* _keyDown)
// {
// 	keyUp = _keyUp;
// 	keyDown = _keyDown;
// 	width = keyUp->getWidth();
// 	height = keyUp->getHeight();
// }
// void LButton::setPosition( int x, int y )
// {
// 	xPos = x; yPos = y;
// }
// void LButton::setCenterPosition( int x, int y )
// {
// 	xCen = x; yCen = y;
// }
// void LButton::handleEvents(SDL_Event* e, bool circleButton)
// {
// 	if (xPos == 0 && yPos == 0)
// 	{
// 		xPos = xCen - width/2, yPos = yCen - height/2;
// 	}
// 	motionMouse = 0;
// 	pressed = 0;
// 	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
// 	{
// 		int x, y;
// 		SDL_GetMouseState( &x, &y );
// 		bool inside = true;
// 		if (!circleButton)
// 		{
// 			inside = isInside(x, y);
// 		}
// 		else
// 		{
// 			if ( (x-xCen)*(x-xCen) + (y-yCen)*(y-yCen) <= width*width/4 )
// 			{
// 				inside = true;
// 			}else
// 			{
// 				inside = false;
// 			}
// 		}
// 		if (inside)
// 		{
// 			switch (e->type)
// 			{
// 				case SDL_MOUSEMOTION:
// 					motionMouse = 1;
// 					break;
// 				case SDL_MOUSEBUTTONDOWN:
// 					playSoundEffects(se_mouseClick);
// 					motionMouse = 1;
// 					pressed = 1;
// 					break;
// 				case SDL_MOUSEBUTTONUP:
// 					pressed = 0;
// 					break;
// 				default:
// 					break;
// 			}
// 		}
// 	}

// }
// void LButton::render(SDL_Renderer* renderer, int x, int y)
// {
// 	if (x==0&&y==0)
// 	{
// 		x=xPos; y = yPos;
// 	}
// 	if (motionMouse)
// 	{
// 		keyDown->render(renderer, x, y);
// 	}
// 	else
// 	{
// 		keyUp->render(renderer, x, y);
// 	}
// }
// bool LButton::isInside(int x, int y){
// 	if (x<xPos)
// 	{
// 		return false;
// 	}
// 	else if (x>xPos+width)
// 	{
// 		return false;
// 	}
// 	else if (y<yPos)
// 	{
// 		return false;
// 	}
// 	else if (y>yPos + height)
// 	{
// 		return false;
// 	}
// 	return true;
// }