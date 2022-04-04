#include "Player_Heart.h"

PlayerHp::PlayerHp()
{
    Total_hearts = 0;
}

PlayerHp::~PlayerHp()
{

}

void PlayerHp::AddPos(const int& xPos)
{
    Pos_List.push_back(xPos);
}

void PlayerHp::Init(std::string filename, SDL_Renderer* renderer)
{
    SDL_Texture *new_texture = nullptr;

    SDL_Surface* loaded_surface = IMG_Load(filename.c_str());
    if(loaded_surface == nullptr)
    {
        std::cerr << "Failed to load image " << filename << std::endl;
        return;
    }

    new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);

    if(new_texture == nullptr)
    {
        std::cerr << "Failed to create texture from surface " << std::endl;
        return;
    }

    heart_rect.w =loaded_surface->w*3;
    heart_rect.h =loaded_surface->h*3;

    SDL_FreeSurface(loaded_surface);

    heart_texture = new_texture;

    Total_hearts = 3;

    AddPos(20);
    AddPos(60);
    AddPos(100);
}

void PlayerHp::Render(SDL_Renderer* renderer)
{
    for (int i = 0; i < Pos_List.size(); i++)
    {
        heart_rect.x = Pos_List[i];
        heart_rect.y = 18;
        SDL_RenderCopy(renderer, heart_texture, nullptr, &heart_rect);
    }
}

void PlayerHp::DecreaseHeart()
{
    Total_hearts--;
    Pos_List.pop_back();
}

void PlayerHp::InCreaseHeart()
{
    Total_hearts++;
    int last_pos = Pos_List.back();
    Pos_List.push_back(last_pos + 40);
}