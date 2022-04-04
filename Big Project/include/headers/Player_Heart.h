#ifndef PLAYER_HP_H_
#define PLAYER_HP_H_

#include "CommonFunc.h"
#include "BaseObject.h"

class PlayerHp
{
public:
    PlayerHp();
    ~PlayerHp();

    void SetHeart(const int& total_heart_) {Total_hearts = total_heart_;}

    void AddPos(const int& xPos);
    void Render(SDL_Renderer *renderer);

    void Init(std::string filename, SDL_Renderer *renderer);

    void InCreaseHeart();
    void DecreaseHeart();

private:
    int Total_hearts;
    SDL_Rect heart_rect;
    SDL_Texture* heart_texture;
    std::vector<int> Pos_List; // Vi tri cua trai tim
};



#endif