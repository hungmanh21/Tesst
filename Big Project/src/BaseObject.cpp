#include "BaseObject.h"

BaseObject::BaseObject()
{
    p_object_ = nullptr;
    rect_.x = rect_.y = 0;
    rect_.w = rect_.h = 0;
}

BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::LoadImage(std::string filename, SDL_Renderer * screen)
{
    SDL_Texture *new_texture = nullptr;

    SDL_Surface* loaded_surface = IMG_Load(filename.c_str());
    if(loaded_surface == nullptr)
    {
        std::cerr << "Failed to load image " << filename << std::endl;
        return false;
    }

    new_texture = SDL_CreateTextureFromSurface(screen, loaded_surface);

    if(new_texture == nullptr)
    {
        std::cerr << "Failed to create texture from surface " << std::endl;
        return false;
    }

    rect_.w =loaded_surface->w;
    rect_.h =loaded_surface->h;

    SDL_FreeSurface(loaded_surface);

    p_object_ = new_texture;
    
    return true;
}

void BaseObject::Render(SDL_Renderer * des, const SDL_Rect* clip)
{
    SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};

    SDL_RenderCopy(des, p_object_, &renderQuad, nullptr);
}

void BaseObject::Free()
{
    if(p_object_ != nullptr)
    {
        SDL_DestroyTexture(p_object_);
        rect_.x = rect_.y =rect_.w = rect_.h = 0;
    }

}