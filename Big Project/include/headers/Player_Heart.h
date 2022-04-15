#ifndef PLAYER_HP_H_
#define PLAYER_HP_H_

#include "CommonFunc.h"
#include "BaseObject.h"

class PlayerHp
{
public:
    PlayerHp();
    ~PlayerHp();

    void Render(SDL_Renderer *renderer);

    void Init(SDL_Renderer *renderer);

    void InCreaseHeart();
    void DecreaseHeart();

private:
    SDL_Rect health_rect;
    int current_health;
    SDL_Texture* health_texture;
    SDL_Rect health_pos;
};



#endif