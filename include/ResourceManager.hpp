#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <unordered_map>

class ResourceManager
{
private:
    SDL_Rect m_src{0, 0, 0, 0};         // Where we're selecting from
    SDL_Rect m_dst{0, 0, 0, 0};   // Where we are rendering
    ResourceManager();
    ~ResourceManager();
    ResourceManager operator=(ResourceManager const&);

    std::unordered_map<std::string, SDL_Texture*> m_texture;
public:
    static ResourceManager& getInstance();

    SDL_Texture* getTexture(std::string filepath, SDL_Renderer* renderer);
    
    void Draw(int x, int y, int w, int h);

        // Select and play a specific frame
        void PlayFrame(int x, int y,int w, int h, int frame);

        // Update every frame
        void Update();
        // Render
        void Render(std::string ID, SDL_Renderer*& renderer, SDL_RendererFlip flip, float angle, SDL_Point* rotatingCenter = NULL);
};