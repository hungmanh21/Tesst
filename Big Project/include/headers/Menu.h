#if !defined(MENU_H_)
#define MENU_H_

#include "CommonFunc.h"

class Menu {
public:
    Menu() {}
    ~Menu() {}

    void Load (SDL_Renderer* des);
    int Show (SDL_Renderer* des, TTF_Font* font[]);

private:
    BaseObject background;

};

#endif
