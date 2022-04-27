#include "Bullet.h"

Bullet::Bullet()
{
    x_val = y_val = 0;
    is_moving = false;

    frameTime = 0;
    
    width_frame = height_frame = 0;
    frame_H = frame_W = 0;
    bullet_dir = DIR_LEFT;
}

Bullet::~Bullet()
{
    Free();
}



bool Bullet ::LoadImgBullet(SDL_Renderer *screen)
{
    bool ret = BaseObject::LoadImage("Assets/Bullets/bullet_moon_4frs.png", screen);
    if (ret)
    {
        width_frame = rect_.w / BULLET_FRAME_NUM_W;
        height_frame = rect_.h;
    }
    set_clips();
    return ret;
}

void Bullet ::set_clips()
{
    if (width_frame > 0 && height_frame > 0)
    {
        for (int j = 0; j < BULLET_FRAME_NUM_W; j++) 
        {
            frame_clip[j].x = j * width_frame; 
            frame_clip[j].y = 0;
            frame_clip[j].w = width_frame;
            frame_clip[j].h = height_frame;
        }
        
    }
}

// check check 
void Bullet ::Show(SDL_Renderer *des)
{
    if (frameTime == 2)
    { // time to change spritesheet
        frameTime = 0;
        frame_W++;
        if (frame_W >= BULLET_FRAME_NUM_W)
            frame_W = 0;
    }
    frameTime++;

    SDL_Rect *currentClip = &frame_clip[frame_W];
    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame * ZOOM_SIZE_BULLET, height_frame * ZOOM_SIZE_BULLET};
    SDL_RenderCopy(des, p_object_, currentClip, &renderQuad);
}

void Bullet :: HandleMove(const int &x_border, const int &y_border){
    // right    rect_.x += x_val;
    // left     rect_.x -= x_val;
    // up       rect_.y -= y_val;
    // down     rect_.y += y_val;
    if(bullet_dir == DIR_RIGHT)
    {
        rect_.x += x_val;
    }
    else if(bullet_dir == DIR_LEFT)
    {
        rect_.x -= x_val;
    }
    else if (bullet_dir == DIR_UP)
    {
        // right    rect_.x += x_val;
        // left     rect_.x -= x_val;
        rect_.y -= y_val;
        // down     rect_.y += y_val;
    }
    else if (bullet_dir == DIR_DOWN)
    {
        // right    rect_.x += x_val;
        // left     rect_.x -= x_val;
        // up       rect_.y -= y_val;
        rect_.y += y_val;
    }
    else if (bullet_dir == DIR_UP_LEFT)
    {
        // right    rect_.x += x_val;
        rect_.x -= x_val * 0.7;
        rect_.y -= y_val * 0.7;
        // down     rect_.y += y_val;
    }
    else if (bullet_dir == DIR_UP_RIGHT)
    {
        rect_.x += x_val * 0.7;
        // left     rect_.x -= x_val;
        rect_.y -= y_val * 0.7;
        // down     rect_.y += y_val;
    }
    else if (bullet_dir == DIR_DOWN_LEFT)
    {
        // right    rect_.x += x_val;
        rect_.x -= x_val * 0.7;
        // up       rect_.y -= y_val;
        rect_.y += y_val * 0.7;
    }
    else if (bullet_dir == DIR_DOWN_RIGHT)
    {
        rect_.x += x_val * 0.7;
        // left     rect_.x -= x_val;
        // up       rect_.y -= y_val;
        rect_.y += y_val * 0.7;
    }
    // check outside
    if (rect_.x > x_border || rect_.x < 0 || rect_.y > y_border || rect_.y < 0)
    {
        is_moving = 0;
    }
    
}