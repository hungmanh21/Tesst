#ifndef PLAYER_H_
#define PLAYER_H_
#include "CommonFunc.h"
#include "BaseObject.h"
#include "Game_Map.h"
#include "Player_Health.h"

const int PLAYER_FRAME_NUM_H = 4;
const int PLAYER_FRAME_NUM_W = 3;
const int SPRITE_DOWN = 0;
const int SPRITE_LEFT = 1;
const int SPRITE_RIGHT = 2;
const int SPRITE_UP = 3;
const int STEP = 6;
const int ZOOM_SIZE_PLAYER = 2;
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

    void IncreaseCoin() {coin_count++;}

    SDL_Rect get_slash_Rect() const {return slash_Rect;}

private:
    

    SDL_Texture *playerTexture;
    SDL_Rect playerPosition; // Rect nay present playerTexture
    int frameTime;
    SDL_Rect framePresent;

    double x_val_, y_val_;
    
    // map
    int map_x_;
    int map_y_;
    
    // slash 
    SDL_Rect slash_Rect;
    SDL_Texture* slashTexture;
    bool is_attack;
    double angle;

    // coin
    int coin_count;

    // health
    PlayerHp player_hp;
};
#endif
