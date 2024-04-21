

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

void ResourceManager::Draw(int x, int y, int w, int h){
    // Create a rectangle
    m_dst.x = x;
    m_dst.y = y;
    m_dst.w = w;
    m_dst.h = h;
}

void ResourceManager::PlayFrame(int x,int y, int w, int h, int frame){
    m_src.x = x+w*frame;
    m_src.y = y;
    m_src.w = w;
    m_src.h = h;
}

void ResourceManager::Update(){

}

void ResourceManager::Render(std::string ID, SDL_Renderer*& renderer, SDL_RendererFlip flip,float angle, SDL_Point* rotatingCenter){
    // SDL_RenderCopy(renderer,m_texture,&m_src,&m_dst);

    auto search = m_texture.find(ID);
    
    if(search == m_texture.end())
    {
        SDL_Texture* Texture = IMG_LoadTexture(renderer, ID.c_str());
        m_texture.insert(std::make_pair(ID, Texture));
    }

    if(m_src.x == 0 && m_src.y == 0 && m_src.w == 0 && m_src.w == 0) 
    {
        SDL_RenderCopyEx(renderer, m_texture[ID], NULL, &m_dst, angle, rotatingCenter, flip);
        return;
    }
    SDL_RenderCopyEx(renderer, m_texture[ID], &m_src, &m_dst, angle, rotatingCenter, flip);
}