#ifndef ENEMY_H_
#define ENEMY_H_

#include "BaseObject.h"
#include "Bullet.h"

#include <vector>

int const ENEMY_FRAME_NUM_W = 4;
int const ENEMY_FRAME_NUM_H = 2;
int const ZOOM_SIZE_ENEMY = 2;
int const ENEMY_STEP = 3;

class Enemy : public BaseObject
{

public:
    Enemy();
    ~Enemy();

    enum TypeMove
    {
        STATIC_ENEMY = 0,
        MOVE_IN_SPACE_ENEMY = 1,
    };

    void set_x_val(const double &xVal) { x_val = xVal; }
    void set_y_val(const double &yVal) { y_val = yVal; }
    void set_x_pos(const double &xpos) { x_pos = xpos; }
    void set_y_pos(const double &ypos) { y_pos = ypos; }
    double get_x_pos() const { return x_pos; }
    double get_y_pos() const { return y_pos; }
    void SetMapXY(const int &mapx, const int &mapy)
    {
        map_x = mapx;
        map_y = mapy;
    }
    // tạo hiệu ứng animation setclip
    void set_clips();
    bool LoadImg(std::string path, SDL_Renderer *screen);
    SDL_Texture * LoadTexture(std::string path);
    // show - chạy theo frame
    void Show(SDL_Renderer *des);
    int get_width_frame() const { return width_frame; }
    int get_height_frame() const { return height_frame; }
    void DoPlayer(Map &gMap);
    void CheckToMap(Map &map_data);

    // tạo enemy di chuyển part2
    void set_type_move(const int &typeMove) { type_move = typeMove; }
    void set_animation_pos(const int & pos_a, const int &pos_b){
        animation_a = pos_a; // left
        animation_b = pos_b; // right
    }
    void set_input_left(const int & ipLeft){input_type.left_ = ipLeft;}
    void ImpMoveType(SDL_Renderer* screen);


    // xử lí đạn p3
    void set_bullet_list(std :: vector<Bullet*> & _bullet_list){
        bullet_list = _bullet_list;
    }
    std:: vector <Bullet*> get_bullet_list() const{
        return bullet_list;
    }
    void InitBullet(Bullet * p_bullet, SDL_Renderer *screen);
    void MakeBullet(SDL_Renderer *screen, const int &x_limit, const int &y_limit, Map &map_old);

private:
    int map_x, map_y;
    
    // val - lượng thay đổi
    // pos - vị trí hiện tại
    double x_val, y_val, x_pos, y_pos;

    // time to change spritesheet
    int frameTime;

    // khung hình crop spritesheet
    SDL_Rect frame_clip[ENEMY_FRAME_NUM_H][ENEMY_FRAME_NUM_W];
    
    int width_frame, height_frame; // size frame
    int frame_H, frame_W; // frame present

    // hiệu ứng di chuyển
    int type_move;
    int animation_a, animation_b; // left-right
    Input input_type;

    // băng đạn p3
    std :: vector <Bullet*> bullet_list;
    int bullet_distance;
};

#endif