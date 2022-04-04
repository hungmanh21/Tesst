#ifndef ARROW_H_
#define ARROW_H_

#include "CommonFunc.h"
#include "BaseObject.h"

class Arrow
{
public:
    Arrow();
    ~Arrow();

    enum ARROW_DIRECTION
    {
        DIR_RIGHT = 20, 
        DIR_LEFT = 21,
        DIR_DOWN = 22,
        DIR_UP = 23
    };

    void LoadImage(std::string filename, SDL_Renderer* renderer);

    void Set_X_Val(const int& val) { x_val = val; }
    void Set_Y_Val(const int& val) { y_val = val; }

    int Get_X_Val() const { return x_val; }
    int Get_Y_Val() const { return y_val; }

    void Set_is_move(const bool& move) {is_moving = move;}
    bool Get_is_move() const {return is_moving;}

    void HandleArrow(const int& x_border, const int& y_border);

    void SetRect(const int& x, const int& y) {arrow_rect.x = x; arrow_rect.y = y;}

    void Render(SDL_Renderer* screen);

    void Set_Arrow_Dir(const int& direction) {arrow_direction = direction;}
    int Get_Arrow_Dir() const {return arrow_direction;}

private:
    int x_val, y_val; 
    bool is_moving;
    SDL_Rect arrow_rect;
    SDL_Texture* arrow_texture;
    int arrow_direction;
};


#endif