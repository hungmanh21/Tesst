#include "Enemy.h"
#include <iostream>
using namespace std;

Enemy :: Enemy(){
    width_frame = height_frame = 0;
    x_val = y_val = x_pos = y_pos = 0;

    frameTime = 0;
    frame_W = frame_H = 0;
    // hiệu ứng di chuyển p2
    animation_a = animation_b = 0;
    input_type.left_ = false;
    type_move = STATIC_ENEMY;
    
}

Enemy :: ~Enemy()
{
    Free();
}

bool Enemy :: LoadImg(std :: string path, SDL_Renderer* screen){
    bool ret = BaseObject:: LoadImage(path, screen);
    if(ret){
        width_frame = rect_.w / ENEMY_FRAME_NUM_W;
        height_frame = rect_.h / ENEMY_FRAME_NUM_H;
        set_clips();
    }
    return ret;
}

SDL_Rect Enemy::get_enemy_Rect()
{
    SDL_Rect e_Rect;
    e_Rect.w = width_frame*ZOOM_SIZE_ENEMY;
    e_Rect.h = height_frame*ZOOM_SIZE_ENEMY;
    e_Rect.x = x_pos;
    e_Rect.y = y_pos;
    return e_Rect; 
}
void Enemy :: set_clips(){
    if(width_frame > 0 && height_frame > 0){
        for (int i = 0; i < ENEMY_FRAME_NUM_H; i++) // 2
        {
            for (int j = 0; j < ENEMY_FRAME_NUM_W; j++) // 4
            {
                frame_clip[i][j].x = j * width_frame; // 4 * w
                frame_clip[i][j].y = i * height_frame; // 2 * h
                frame_clip[i][j].w = width_frame;
                frame_clip[i][j].h = height_frame;
            }
        }
    }
}

void Enemy :: Show(SDL_Renderer *des){ 
    
    // change animation
    if (frameTime == 4)
    { // time to change spritesheet
        frameTime = 0;
        frame_W++;
        if (frame_W >= ENEMY_FRAME_NUM_W)
            frame_W = 0;
        
    }
    if (input_type.left_ == 1){
        frame_H = 0;
    }
    else{
        frame_H = 1;
    }
    frameTime++;

    rect_.x = x_pos - map_x;
    rect_.y = y_pos - map_y;

    SDL_Rect *currentClip = &frame_clip[frame_H][frame_W];
    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame * ZOOM_SIZE_ENEMY, height_frame * ZOOM_SIZE_ENEMY};
    SDL_RenderCopy(des, p_object_, currentClip, &renderQuad);
    
}

void Enemy :: DoPlayer(Map& gMap){
    x_val = y_val = 0;
    if(type_move == STATIC_ENEMY)
    {
        ;
    }
    else 
    {
        if(input_type.left_ == 1){
            x_val = - ENEMY_STEP;
        }
        else if (input_type.right_ == 1)
        {
            x_val = ENEMY_STEP;
        }
        CheckToMap(gMap);
    }
    
}

void Enemy ::CheckToMap(Map &map_data)
{
    // gioi han kiem tra theo truc x va y
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    // x1, y1 __________ x2, y1
    //   |                 |
    //   |                 |
    //   |                 |
    // x1, y2 __________ x2, y2

    int height_min = height_frame * ZOOM_SIZE_ENEMY < TILE_SIZE ? height_frame * ZOOM_SIZE_ENEMY: TILE_SIZE;

    x1 = (x_pos + x_val) / TILE_SIZE;
    x2 = (x_pos + x_val + width_frame * ZOOM_SIZE_ENEMY - 1) / TILE_SIZE;

    y1 = (y_pos) / TILE_SIZE;
    y2 = (y_pos + height_min - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val > 0) // di sang phai
        {
            if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                x_pos = x2 * TILE_SIZE;
                x_pos -= width_frame * ZOOM_SIZE_ENEMY + 1;
                x_val = 0;
            }
        }
        else if (x_val < 0)
        {
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
            {
                x_pos = (x1 + 1) * TILE_SIZE;
                x_val = 0;
            }
        }
    }

    // check va cham chieu doc
    int width_min = width_frame * ZOOM_SIZE_ENEMY < TILE_SIZE ? width_frame * ZOOM_SIZE_ENEMY : TILE_SIZE;
    x1 = (x_pos) / TILE_SIZE;
    x2 = (x_pos + width_min) / TILE_SIZE;
    y1 = (y_pos + y_val) / TILE_SIZE;
    y2 = (y_pos + y_val + height_frame * ZOOM_SIZE_ENEMY- 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val > 0)
        {
         
            if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                y_pos = (y2)*TILE_SIZE;
                y_pos -= height_frame * ZOOM_SIZE_ENEMY + 1;
                y_val = 0;
            }
        }
        else if (y_val < 0)
        {
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
            {
                y_pos = (y1 + 1) * TILE_SIZE;
                y_val = 0;
            }
        }
    }
// chưa xử lí STATEMONEY

    // thay doi vi tri
    x_pos += x_val;
    y_pos += y_val;

    // set lai do thay doi vi tri sau moi vong lap
    x_val = 0;
    y_val = 0;

    if (x_pos < 0)
    {
        x_pos = 0;
    }
    else if (x_pos + width_frame * ZOOM_SIZE_ENEMY > map_data.max_x_)
    {
        x_pos = map_data.max_x_ - width_frame * ZOOM_SIZE_ENEMY - 1;
    }
}


void Enemy :: ImpMoveType(SDL_Renderer * screen){
    if(type_move == STATIC_ENEMY){
        input_type.left_ = 1;
    }
    else{
        if(x_pos > animation_b){
            input_type.left_ = 1;
            input_type.right_ = 0;
        }
        if (x_pos < animation_a)
        {
            input_type.left_ = 0;
            input_type.right_ = 1;
        }
    }
}

 // xử lí đạn cho enemy p3
// BUG - check - Loadimg diff
void Enemy::InitBullet(Bullet *p_bullet, SDL_Renderer *screen){
    if(p_bullet != NULL){
        p_bullet->LoadImgBullet(screen);
        p_bullet->set_is_moving(true);
        p_bullet->setBulletDir(Bullet ::DIR_LEFT);

        p_bullet->SetRect(rect_.x + 5, rect_.y + 5); // vị trí đạn trên màn hình
        p_bullet->set_x_val(6);
        p_bullet->set_y_val(6);
        bullet_list.push_back(p_bullet);
    }
}

// no pros
void Enemy :: MakeBullet(SDL_Renderer *screen, const int &x_limit, const int &y_limit, Map &map_old){
    // x_pos : vtri x voi full map
    // rect_x : vtri x voi gScreen

    int change_map_x = map_x - map_old.start_x;
    int change_map_y = map_y - map_old.start_y;
    
    for (int i = 0; i < bullet_list.size(); i++)
    {
        Bullet * p_bullet = bullet_list.at(i);
        if(p_bullet != NULL){
            if (p_bullet->get_is_moving()) // đạn đang bay
            {   
                bullet_distance = rect_.x + width_frame* ZOOM_SIZE_ENEMY - p_bullet ->get_bullet_rect().x;
                
                if (abs(bullet_distance) < SCREEN_WIDTH / 4)
                {
                    p_bullet->HandleMove(x_limit, y_limit);
                    // FIX THIS
                    // p_bullet->SetRect(p_bullet->get_bullet_rect().x - change_map_x, p_bullet->get_bullet_rect().y);
                    //p_bullet->SetRect(rect_.x + 5, rect_.y + 5);
                    p_bullet->Show(screen);
                }
                else p_bullet->set_is_moving(false); 
            }else{
                p_bullet->setBulletDir((p_bullet->getBulletDir() + 1) % Bullet::DIR_NUM); // đổi hướng đạn

                p_bullet->set_is_moving(true);
                p_bullet->SetRect(rect_.x + 5, rect_.y + 5); // vị trí đạn trên màn hình rect_x theo enemy
                // phụ thuộc enemy img
                
            }

        }
    }
    
}

void Enemy::RemoveBullet(const int idx)
{
    int size = bullet_list.size();
    if(size > 0 && idx < size)
    {
        Bullet* e_bullet = bullet_list.at(idx);
        bullet_list.erase(bullet_list.begin()+idx);
        if(e_bullet != nullptr)
        {
            delete e_bullet;
            e_bullet = nullptr;
        }
    }
}