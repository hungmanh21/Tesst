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
    coin_count = 0;
}

Player :: ~ Player(){
    Free();
}

bool Player::LoadImg(std ::string filename, SDL_Renderer *screen)
{
    SDL_Texture *new_texture = nullptr;

    SDL_Surface *loaded_surface = IMG_Load(filename.c_str());
    if (loaded_surface == nullptr)
    {
        std::cerr << "Failed to load image " << filename << std::endl;
        return false;
    }

    new_texture = SDL_CreateTextureFromSurface(screen , loaded_surface);

    if (new_texture == nullptr)
    {
        std::cerr << "Failed to create texture from surface " << std::endl;
        return false;
    }

    framePresent.w = loaded_surface->w / 3;
    framePresent.h = loaded_surface->h / 4;

    playerPosition.w = framePresent.w*2;
    playerPosition.h = framePresent.h*2;

    SDL_FreeSurface(loaded_surface);

    playerTexture = new_texture;

    return true;
}

void Player :: Render(SDL_Renderer *renderer)
{
    // tinh lai vi tri nhan vat khi map di chuyen
    playerPosition.x -= map_x_;
    playerPosition.y -= map_y_;

    SDL_RenderCopy(renderer, playerTexture, &framePresent, &playerPosition);

    playerPosition.x += map_x_;
    playerPosition.y += map_y_;
}

void Player :: ChangeSprite(const int Direction, bool running)
{
    if (running)
    {
        framePresent.y = framePresent.h * Direction; // chuyen huong
        
        frameTime ++;
        if (frameTime == 5){
            frameTime = 0;
            framePresent.x += framePresent.w;
        }
        if (framePresent.x >= framePresent.w * 3) // có 3 ảnh cho 1 hướng đi
            framePresent.x = 0;
        
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
        default:
            x_val_ = 0;
            y_val_ = 0;
            break;
        }
    }
    else ChangeSprite(0, false);

    if(events.type == SDL_MOUSEBUTTONDOWN)
    {
        if(events.button.button == SDL_BUTTON_LEFT)
        {
            Arrow* arrow = new Arrow();
            arrow->LoadImage("Assets\\Player\\Arrow.png", screen);
            arrow->SetRect(playerPosition.x + playerPosition.w - 20, playerPosition.y + playerPosition.h - 10);
            arrow->Set_X_Val(15);
            arrow->Set_is_move(true);

            arrow_list.push_back(arrow);
        }
    }
}

void Player::HandleArrows(SDL_Renderer *screen)
{
    for (int i = 0; i < arrow_list.size(); i++)
    {
        Arrow* ar = arrow_list[i];
        if(ar != nullptr)
        {
            if(ar->Get_is_move() == true)
            {
                ar->HandleArrow(SCREEN_WIDTH, SCREEN_HEIGHT);
                ar->Render(screen);
            }
            else
            {
                arrow_list.erase(arrow_list.begin() + i);
                if(ar != nullptr)
                {
                    delete ar;
                    ar = nullptr;
                }
            }
        }
    }
    
}

void Player::Free(){
    if (playerTexture != nullptr)
    {
        SDL_DestroyTexture(playerTexture);
        playerPosition.x = playerPosition.y = playerPosition.w = playerPosition.h = 0;
    }
}

// // Xu ly va cham
void Player::CheckToMap(Map& map_data)
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
    int height_min = framePresent.h*2 < TILE_SIZE ? framePresent.h*2 : TILE_SIZE;
    
    x1 = (playerPosition.x + x_val_) / TILE_SIZE;
    x2 = (playerPosition.x + x_val_ + framePresent.w*2 - 1) / TILE_SIZE;

    y1 = (playerPosition.y) / TILE_SIZE;
    y2 = (playerPosition.y + height_min - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val_ > 0) // di sang phai
        {
            if(map_data.tile[y1][x2] == MONEY_TILE || map_data.tile[y2][x2] == MONEY_TILE)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseCoin();
            }
            else if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                playerPosition.x = x2 * TILE_SIZE;
                playerPosition.x -= framePresent.w*2 + 1;
                x_val_ = 0;
            }
        } else if (x_val_ < 0)
        {
            if (map_data.tile[y1][x1] == MONEY_TILE || map_data.tile[y2][x1] == MONEY_TILE)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y2][x1] = 0;
                IncreaseCoin();
            }

            else if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
            {
                playerPosition.x = (x1 + 1) * TILE_SIZE;
                x_val_ = 0;
            }
            
        }
        
    }


    // check va cham chieu doc
    int width_min = framePresent.w*2 < TILE_SIZE ? framePresent.w*2 : TILE_SIZE;
    x1 = (playerPosition.x) / TILE_SIZE;
    x2 = (playerPosition.x + width_min) / TILE_SIZE;
    y1 = (playerPosition.y + y_val_) / TILE_SIZE;
    y2 = (playerPosition.y + y_val_ + framePresent.h*2 - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 <MAX_MAP_Y)
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
                playerPosition.y = (y2) * TILE_SIZE;
                playerPosition.y -= framePresent.h*2 + 1;
                y_val_ = 0;
            }
        } else if (y_val_ < 0)
        {
            if (map_data.tile[y1][x1] == MONEY_TILE || map_data.tile[y1][x2] == MONEY_TILE)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
                IncreaseCoin();
            }
            else if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
            {
                playerPosition.y = (y1 + 1) *TILE_SIZE;
                y_val_ = 0;
            }
            
        }
        
    }
    playerPosition.x += x_val_;
    playerPosition.y += y_val_;

    // // bo 2 dong toi neu muon nhan vat di chuyen lien tuc
    x_val_ = 0;
    y_val_ = 0;

    // tranh vuot qua 2 ben cua map
    if (playerPosition.x < 0 )
    {
        playerPosition.x = 0;
    }
    else if (playerPosition.x + framePresent.w >  map_data.max_x_) 
    {
        playerPosition.x = map_data.max_x_ - framePresent.w*2 + 1;
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