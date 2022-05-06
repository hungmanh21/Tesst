#ifndef COMMONFUNCC_H_
#define COMMONFUNCC_H_

#include <iostream>
#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "TextObject.h"
#include "BaseObject.h"

static SDL_Window* g_Window = nullptr;
static SDL_Renderer* g_Screen = nullptr;

// Menu surface
static SDL_Surface* g_img_menu = nullptr;
static SDL_Event g_Event;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32; 
const int kFonts = 3; 

#define BLANK_TILE 0 // o trong
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
    int jump; // chắc cái này không cần
};

struct Map {
    int start_x, start_y;

    int max_x_ , max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;
};

namespace SDLCommonFunc{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
   
    // Kiem tra chuot trong nut bam
    bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect); 
}

#endif 