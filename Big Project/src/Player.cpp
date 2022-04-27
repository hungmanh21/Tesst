#include "Player.h"
#include<iostream>
using namespace std;

Player :: Player(){
    framePresent.x = 0, framePresent.y = 0;
    frameTime = 0;
    playerPosition.w = playerPosition.h = 0;
    playerPosition.x = playerPosition.y = 256; // de 64 de tranh ket vao tuong
    playerTexture = NULL;
    x_val_ = 0;
    y_val_ = 0;
    map_x_ = 0;
    map_y_ = 0;

    is_attack = false;
    angle = 0;
}

Player :: ~ Player(){
    Free();
}

bool Player ::LoadImg(std ::string filename, SDL_Renderer *screen)
{
    SDL_Texture *new_texture = nullptr;

    SDL_Surface *loaded_surface = IMG_Load(filename.c_str());
    if (loaded_surface == nullptr)
    {
        std::cerr << "Failed to load image " << filename << std::endl;
        return false;
    }

    SDL_Surface* surface = IMG_Load("Assets\\Player\\slash.png");

    new_texture = SDL_CreateTextureFromSurface(screen , loaded_surface);

    slashTexture = SDL_CreateTextureFromSurface(screen, surface);

    if (new_texture == nullptr)
    {
        std::cerr << "Failed to create texture from surface " << std::endl;
        return false;
    }

    framePresent.w = loaded_surface->w / PLAYER_FRAME_NUM_W;
    framePresent.h = loaded_surface->h / PLAYER_FRAME_NUM_H;

    playerPosition.w = framePresent.w * ZOOM_SIZE_PLAYER;
    playerPosition.h = framePresent.h * ZOOM_SIZE_PLAYER;

    slash_Rect.w = surface->w;
    slash_Rect.h = surface->h;

    SDL_FreeSurface(surface);
    SDL_FreeSurface(loaded_surface);

    playerTexture = new_texture;

    player_hp.Init(screen);

    return true;
}

void Player :: Render(SDL_Renderer *renderer)
{
    // tinh lai vi tri nhan vat khi map di chuyen
    playerPosition.x -= map_x_;
    playerPosition.y -= map_y_;

    SDL_RenderCopy(renderer, playerTexture, &framePresent, &playerPosition);

    if(is_attack)
    {
        if(framePresent.y == framePresent.h * 3)
        {
            slash_Rect.x = playerPosition.x;
            slash_Rect.y = playerPosition.y - 45;
            angle = 270;
        }
        else if(framePresent.y == framePresent.h * 2)
        {
            slash_Rect.x = playerPosition.x + 45;
            slash_Rect.y = playerPosition.y;
            angle = 0;
        }
        else if (framePresent.y == framePresent.h)
        {
            slash_Rect.x = playerPosition.x - 45;
            slash_Rect.y = playerPosition.y;
            angle = 180;
        }
        else
        {
            slash_Rect.x = playerPosition.x;
            slash_Rect.y = playerPosition.y + 45;
            angle = 90;
        }
        SDL_RenderCopyEx(renderer, slashTexture, nullptr, &slash_Rect, angle, nullptr, SDL_FLIP_NONE);
        is_attack = false;
    }
    else
    {
        slash_Rect.x = slash_Rect.y = 0;
    }
    playerPosition.x += map_x_;
    playerPosition.y += map_y_;

    player_hp.Render(renderer);
}

void Player :: ChangeSprite(const int Direction, bool running) // sau này sửa thành SDL Rect setclip
{
    if (running)
    {
        framePresent.y = framePresent.h * Direction; 

        frameTime++;
        if (frameTime == 4)
        {
            frameTime = 0;
            framePresent.x += framePresent.w;
            if (framePresent.x >= framePresent.w * PLAYER_FRAME_NUM_W)
                framePresent.x = 0;
        }
    }
    else
        framePresent.x = framePresent.w * 1;
}

void Player :: HandleInputAction(SDL_Event events, SDL_Renderer *screen)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_UP:
            ChangeSprite(SPRITE_UP, 1);
            y_val_ = -STEP;
            break;
        case SDLK_DOWN:
            ChangeSprite( SPRITE_DOWN , 1);
            y_val_ = +STEP;
            break;
        case SDLK_LEFT:
            ChangeSprite( SPRITE_LEFT , 1);
            x_val_ = -STEP;
            break;
        case SDLK_RIGHT:
            ChangeSprite( SPRITE_RIGHT , 1);
            x_val_ = +STEP;
            break;
        case SDLK_SPACE:
            is_attack = true;
            break;
            
        default:
            x_val_ = 0;
            y_val_ = 0;
            break;
        }
    }
    else ChangeSprite(0, false);
}

void Player::Free(){
    if (playerTexture != nullptr)
    {
        SDL_DestroyTexture(playerTexture);
        playerPosition.x = playerPosition.y = playerPosition.w = playerPosition.h = 0;
    }


    if (playerTexture != nullptr)
    {
        SDL_DestroyTexture(playerTexture);
        playerPosition.x = playerPosition.y = playerPosition.w = playerPosition.h = 0;
    }
}

// // Xu ly va cham
void Player::CheckToMap(Map &map_data)
{
    // gioi han kiem tra theo truc x va y
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    // so do
    // x1, y1 __________ x2, y1
    //   |                 |
    //   |                 |
    //   |                 |
    // x1, y2 __________ x2, y2

    // check va cham theo chieu ngang
    int height_min = framePresent.h * ZOOM_SIZE_PLAYER < TILE_SIZE ? framePresent.h * ZOOM_SIZE_PLAYER : TILE_SIZE;

    x1 = (playerPosition.x + x_val_) / TILE_SIZE;
    x2 = (playerPosition.x + x_val_ + framePresent.w * ZOOM_SIZE_PLAYER - 1) / TILE_SIZE;

    y1 = (playerPosition.y) / TILE_SIZE;
    y2 = (playerPosition.y + height_min - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val_ > 0) // di sang phai
        {
            if (map_data.tile[y1][x2] == MONEY_TILE || map_data.tile[y2][x2] == MONEY_TILE)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseCoin();
            }
            else if (map_data.tile[y1][x2] == HEART_TILE || map_data.tile[y2][x2] == HEART_TILE)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                player_hp.InCreaseHeart();
            }
            else if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                playerPosition.x = x2 * TILE_SIZE;
                playerPosition.x -= framePresent.w * ZOOM_SIZE_PLAYER + 1;
                x_val_ = 0;
            }
        }
        else if (x_val_ < 0)
        {
            if (map_data.tile[y1][x1] == MONEY_TILE || map_data.tile[y2][x1] == MONEY_TILE)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y2][x1] = 0;
                IncreaseCoin();
            }
            else if (map_data.tile[y1][x1] == MONEY_TILE || map_data.tile[y2][x1] == MONEY_TILE)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y2][x1] = 0;
                player_hp.InCreaseHeart();
            }
            else if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
            {
                playerPosition.x = (x1 + 1) * TILE_SIZE;
                x_val_ = 0;
            }
        }
    }

    // check va cham chieu doc
    int width_min = framePresent.w * ZOOM_SIZE_PLAYER < TILE_SIZE ? framePresent.w * ZOOM_SIZE_PLAYER : TILE_SIZE;
    x1 = (playerPosition.x) / TILE_SIZE;
    x2 = (playerPosition.x + width_min) / TILE_SIZE;
    y1 = (playerPosition.y + y_val_) / TILE_SIZE;
    y2 = (playerPosition.y + y_val_ + framePresent.h * ZOOM_SIZE_PLAYER - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0)
        {
            if (map_data.tile[y2][x1] == MONEY_TILE || map_data.tile[y2][x2] == MONEY_TILE)
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseCoin();
            }
            else if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                playerPosition.y = (y2)*TILE_SIZE;
                playerPosition.y -= framePresent.h * ZOOM_SIZE_PLAYER + 1;
                y_val_ = 0;
            }
        }
        else if (y_val_ < 0)
        {
            if (map_data.tile[y1][x1] == MONEY_TILE || map_data.tile[y1][x2] == MONEY_TILE)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
                IncreaseCoin();
            }
            else if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
            {
                playerPosition.y = (y1 + 1) * TILE_SIZE;
                y_val_ = 0;
            }
        }
    }

    // thay doi vi tri
    playerPosition.x += x_val_;
    playerPosition.y += y_val_;

    // set lai do thay doi vi tri sau moi vong lap
    x_val_ = 0;
    y_val_ = 0;

    // tranh vuot qua 2 bien map
    if (playerPosition.x < 0)
    {
        playerPosition.x = 0;
    }
    else if (playerPosition.x + framePresent.w > map_data.max_x_)
    {
        playerPosition.x = map_data.max_x_ - framePresent.w * ZOOM_SIZE_PLAYER + 1;
    }
}

void Player::SetMapXY(const int map_x, const int map_y)
{
    map_x_ = map_x;
    map_y_ = map_y;
}

void Player::CenterEntityOnMap(Map& map_data, int& top_x, int& top_y)
{
    // Ban do di chuyen khi nhan vat toi giua ban do
    if (playerPosition.x - (SCREEN_WIDTH / 2) > top_x)
    {
        top_x = playerPosition.x - (SCREEN_WIDTH / 2);
    }
    else if (top_x > playerPosition.x - (SCREEN_WIDTH / 10))
    {
        top_x = playerPosition.x - (SCREEN_WIDTH / 10);
    }
    

    map_data.start_x = top_x;
    if (map_data.start_x < 0)
    {
        map_data.start_x = 0;
    }
    else if (map_data.start_x + SCREEN_WIDTH >= map_data.max_x_) // tan cung ben phai map
    {
        map_data.start_x = map_data.max_x_ - SCREEN_WIDTH;
    }

    if (playerPosition.y - (SCREEN_HEIGHT / 2) > top_y)
    {
        top_y = playerPosition.y - (SCREEN_HEIGHT / 2);
    } 

    map_data.start_y = top_y;
    if (map_data.start_y < 0)
    {
        map_data.start_y = 0;
    }
    else if (map_data.start_y + SCREEN_HEIGHT >= map_data.max_y_) // tan cung ben duoi map
    {
        map_data.start_y = map_data.max_y_ - SCREEN_HEIGHT;
    }
}