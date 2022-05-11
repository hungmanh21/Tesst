#include "Player_Health.h"

PlayerHp::PlayerHp()
{
    current_health = 5;

    health_pos.x = health_pos.y = 20;
    health_pos.w = health_pos.h = 0;

    health_rect.x = health_rect.y = 0;
    health_rect.w = health_rect.h = 0;

    health_texture = nullptr;
}

PlayerHp::~PlayerHp()
{

}
void PlayerHp::Init(SDL_Renderer* renderer)
{
    SDL_Texture *new_texture = nullptr;

    SDL_Surface* loaded_surface = IMG_Load("Assets/Player/health_bar.png");
    if(loaded_surface == nullptr)
    {
        std::cerr << "Failed to load health bar" << std::endl;
        return;
    }

    new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);

    if(new_texture == nullptr)
    {
        std::cerr << "Failed to create texture from surface " << std::endl;
        return;
    }

    health_rect.w = loaded_surface->w;
    health_rect.h = loaded_surface->h/6;

    health_pos.w = health_rect.w/3;
    health_pos.h = health_rect.h/3;

    SDL_FreeSurface(loaded_surface);

    health_texture = new_texture;
}

void PlayerHp::Render(SDL_Renderer* renderer)
{
    health_rect.y = current_health*health_rect.h;
    SDL_RenderCopy(renderer, health_texture, &health_rect, &health_pos);
}

void PlayerHp::DecreaseHeart()
{
    if(current_health > 0) current_health--;
}

void PlayerHp::IncreaseHeart()
{
    if(current_health < 5) current_health++;
}