#pragma once

#include <string>
// Third Party
#include <SDL2/SDL.h> // For Mac, use <SDL.h>

class AnimatedSprite{
    public:
        // Constructor
        void getResource(SDL_Renderer* renderer, const char* filepath);
        void setTexture(SDL_Texture* texture)
        {
            m_texture = texture;
        }
        // AnimatedSprite(SDL_Renderer*& renderer, const char* filepath);
        // Destructor
        ~AnimatedSprite();
        // 
        void Draw(int x, int y, int w, int h);

        // Select and play a specific frame
        void PlayFrame(int x, int y,int w, int h, int frame);

        // Update every frame
        void Update();
        // Render
        void Render(SDL_Renderer*& renderer, SDL_RendererFlip flip, float angle, SDL_Point* rotatingCenter = NULL);

        void clean();
        SDL_Texture* getTexture() {
            return m_texture;
        };

    private:
        SDL_Texture* m_texture = NULL;
        SDL_Rect m_src{0, 0, 0, 0};         // Where we're selecting from
        SDL_Rect m_dst{0, 0, 0, 0};   // Where we are rendering
};