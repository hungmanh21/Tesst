#ifndef PLAYER_H_
#define PLAYER_H_
#include "CommonFunc.h"
#include "BaseObject.h"
#include "Game_Map.h"
#include "Arrow.h"

const int SPRITE_DOWN = 0;
const int SPRITE_LEFT = 1;
const int SPRITE_RIGHT = 2;
const int SPRITE_UP = 3;
const int STEP = 10; 

class Player 
{
public:
    Player();
    ~Player();

    void Render(SDL_Renderer *renderer); // render 

    void Free();

    bool LoadImg(std ::string filename, SDL_Renderer *screen);

    void ChangeSprite(const int Direction, bool running);

    void HandleInputAction(SDL_Event events, SDL_Renderer *screen);

    // Xu ly va cham
    void CheckToMap(Map& map_data);

    // dich map
    void SetMapXY(const int map_x, const int map_y);
    void CenterEntityOnMap(Map& map_data, int& top_x, int& top_y);

    void HandleArrows(SDL_Renderer *screen);

    void IncreaseCoin() {coin_count++;}
private:
    int coin_count;

    SDL_Texture *playerTexture;
    SDL_Rect playerPosition; // Rect nay present playerTexture
    int frameTime;
    SDL_Rect framePresent;

    // Xu ly va cham
    double x_val_, y_val_;

    // vi tri map
    int map_x_;
    int map_y_;

    std::vector<Arrow*> arrow_list;
};
#endif
