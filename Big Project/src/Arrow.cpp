#include "Arrow.h"

Arrow::Arrow()
{
    x_val = 0; y_val = 0;
    is_moving = false;
    arrow_rect.x = 0; arrow_rect.y = 0;
}

Arrow::~Arrow() {}

void Arrow::HandleArrow(const int& x_border, const int& y_border)
{
    arrow_rect.x += x_val;
    if(arrow_rect.x >= x_border) is_moving = false;
     
}

void Arrow::LoadImage(std::string filename, SDL_Renderer* screen)
{
    SDL_Texture *new_texture = nullptr;

    SDL_Surface *loaded_surface = IMG_Load(filename.c_str());
    if (loaded_surface == nullptr)
    {
        std::cerr << "Failed to load image " << filename << std::endl;
        return;
    }

    new_texture = SDL_CreateTextureFromSurface(screen , loaded_surface);

    if (new_texture == nullptr)
    {
        std::cerr << "Failed to create texture from surface " << std::endl;
        return;
    }

    arrow_rect.w = loaded_surface->w*4;
    arrow_rect.h = loaded_surface->h*4;


    SDL_FreeSurface(loaded_surface);

    arrow_texture = new_texture;
}

void Arrow::Render(SDL_Renderer *screen)
{
    
    SDL_RenderCopy(screen, arrow_texture, nullptr, &arrow_rect);
}