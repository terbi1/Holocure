#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <unordered_map>

class ResourceManager
{
private:
    ResourceManager();
    ~ResourceManager();
    ResourceManager operator=(ResourceManager const&);

    std::unordered_map<std::string, SDL_Texture*> m_texture;
public:
    static ResourceManager& getInstance();

    SDL_Texture* getTexture(std::string filepath, SDL_Renderer* renderer);

};