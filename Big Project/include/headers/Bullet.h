#ifndef BULLET_H_
#define BULLET_H_
#include "BaseObject.h"
#include "CommonFunc.h"

int const BULLET_FRAME_NUM_W = 4;
int const ZOOM_SIZE_BULLET = 2;
class Bullet : public BaseObject
{
public:
    Bullet();
    ~Bullet();

    enum BulletDir
    {   
        DIR_UP_RIGHT = 0,
        DIR_RIGHT = 1,
        DIR_DOWN_RIGHT = 2,
        DIR_DOWN = 3,
        DIR_DOWN_LEFT = 4,
        DIR_LEFT = 5,
        DIR_UP_LEFT = 6,
        DIR_UP = 7,

        DIR_NUM = 8,
        // other dir if needed
    };

    void set_x_val(const int & xVal){x_val = xVal;}
    void set_y_val(const int & yVal) { y_val = yVal; }
    int get_x_val() const { return x_val; }
    int get_y_val() const { return y_val; }
    
    void set_is_moving(const bool & isMoving){is_moving = isMoving;}
    bool get_is_moving(){return is_moving;}

    // for animation
    void set_clips();
    bool LoadImgBullet(SDL_Renderer *screen);
    void Show(SDL_Renderer *des);
    
    // direction
   
    void setBulletDir(const int & Dir){bullet_dir = Dir;}
    int getBulletDir() const { return bullet_dir; }
    void HandleMove(const int & x_border, const int &y_border);

    SDL_Rect get_bullet_rect();

private:
    int x_val, y_val;
    bool is_moving;
    
    // direction 
    int bullet_dir;

    // time to change spritesheet
    int frameTime;
    // khung hình crop spritesheet
    SDL_Rect frame_clip[BULLET_FRAME_NUM_W];

    int width_frame, height_frame; // size frame
    int frame_H, frame_W;          // frame present
};



#endif