#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Game_Map.h"
#include "Player.h"

BaseObject g_Background;

bool Init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error: SDL_Init() failed" << std::endl;
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "3");

    g_Window = SDL_CreateWindow("SwordMan_Nhom19", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(g_Window == NULL)
    {
        std::cerr << "Error: SDL_CreateWindow" << std::endl;
        return false;
    }
    else
    {
        g_Screen = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(g_Screen == nullptr)
        {
            std::cerr << "Failed to create renderer" << std::endl;
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_Screen, 255, 255, 255, 255 );
            int imgFlags = IMG_INIT_PNG;
            if( !IMG_Init(imgFlags)  && imgFlags)
            {
                success = false;
            }
        }
    }
    return success;
}

bool LoadBackground()
{
    bool res = g_Background.LoadImage("Assets/game_background.png", g_Screen);
    return (res == true);
}

void Close(){
    g_Background.Free();
    
    SDL_DestroyWindow(g_Window);
    g_Window = nullptr;

    SDL_DestroyRenderer(g_Screen);
    g_Screen = nullptr;

    IMG_Quit();
    SDL_Quit();


}


int main(int argc, char* args[]){
    if(Init() == false)
    {
        return -1;
    }

    if(LoadBackground() == false)
    {
        return -1;
    }

    // map
    Game_Map game_map;
    game_map.LoadMap("Assets/Maps/map01.dat");
    game_map.LoadTiles(g_Screen);

    // player
    Player player;
    player.LoadImg("Assets/Player/Player-Sprite.png", g_Screen);

    // main loop
    bool is_quit = false;
    int top_x = 0, top_y = 0;
    while(!is_quit)
    {
        // mingw32-make run
        while(SDL_PollEvent(&g_Event) )
        {
            if(g_Event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            else
                player.HandleInputAction(g_Event, g_Screen);
        }

        // clear va load background
        SDL_SetRenderDrawColor(g_Screen, 255, 255, 255, 255);
        SDL_RenderClear(g_Screen);
        g_Background.Render(g_Screen, nullptr);

        // Xu ly chuyen dong & va cham
        Map map_data = game_map.getMap();
        
        
        player.CheckToMap(map_data);

        player.SetMapXY(map_data.start_x, map_data.start_y);

        //player.CheckToMap(map_data);
        player.CenterEntityOnMap(map_data, top_x, top_y);

        player.HandleArrows(g_Screen);

        player.Render(g_Screen);

        // Ve map
        game_map.SetMap(map_data);
        game_map.DrawMap(g_Screen);
        
        // Cap nhat man hinh
        SDL_RenderPresent(g_Screen);
    }

    Close();
    return 0;
}