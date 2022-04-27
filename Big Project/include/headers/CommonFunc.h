#ifndef COMMONFUNCC_H_
#define COMMONFUNCC_H_

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "SDL_mixer.h"
#include <vector>

static SDL_Window* g_Window = nullptr;
static SDL_Renderer* g_Screen = nullptr;
static SDL_Event g_Event;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;  

#define BLANK_TILE 0 
#define MONEY_TILE 27
#define HEART_TILE 28
#define TILE_SIZE 64

#define MAX_MAP_X 85
#define MAX_MAP_Y 10

struct Input{
    int left_;
    int right_;
    int up_;
    int down_;
};


struct Map {
    int start_x, start_y;

    int max_x_ , max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;
};

namespace SDLCommonFunc{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}

#endif 