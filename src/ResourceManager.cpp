

#include "ResourceManager.hpp"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

ResourceManager ResourceManager::operator=(ResourceManager const& rhs)
{
    return *this;
}

// Is instantiate, exactly 1 instance of our class
ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager* s_instance = new ResourceManager;

    return *s_instance;
}

SDL_Texture* ResourceManager::getTexture(std::string filepath, SDL_Renderer* renderer) 
{
    auto search = m_texture.find(filepath);
    
    if(search == m_texture.end())
    {
        SDL_Texture* Texture = IMG_LoadTexture(renderer, filepath.c_str());
        m_texture.insert(std::make_pair(filepath, Texture));
    }

    return m_texture[filepath];
}