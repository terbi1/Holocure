#include <string>
// Third Party
#include <SDL2/SDL.h> // For Mac, use <SDL.h>
#include "sDL2/SDL_image.h"

#include "AnimatedSprites.hpp"

// Constructor
void AnimatedSprite::getResource(SDL_Renderer* renderer, const char* filepath){
    m_texture = IMG_LoadTexture(renderer,filepath);
}

// Destructor
AnimatedSprite::~AnimatedSprite(){
    SDL_DestroyTexture(m_texture);
    m_texture = NULL;
}

void AnimatedSprite::Draw(int x, int y, int w, int h){
    // Create a rectangle
    m_dst.x = x;
    m_dst.y = y;
    m_dst.w = w;
    m_dst.h = h;
}

void AnimatedSprite::PlayFrame(int x,int y, int w, int h, int frame){
    m_src.x = x+w*frame;
    m_src.y = y;
    m_src.w = w;
    m_src.h = h;
}

void AnimatedSprite::Update(){

}

void AnimatedSprite::Render(SDL_Renderer*& renderer, SDL_RendererFlip flip,float angle, SDL_Point* rotatingCenter){
    // SDL_RenderCopy(renderer,m_texture,&m_src,&m_dst);
    if(m_src.x == 0 && m_src.y == 0 && m_src.w == 0 && m_src.w == 0) 
    {
        SDL_RenderCopyEx(renderer, m_texture, NULL, &m_dst, angle, rotatingCenter, flip);
        return;
    }
    SDL_RenderCopyEx(renderer, m_texture, &m_src, &m_dst, angle, rotatingCenter, flip);
}