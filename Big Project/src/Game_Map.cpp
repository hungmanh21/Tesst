#include "Game_Map.h"

void Game_Map::LoadMap(char* filename) {
    FILE* fp = nullptr;
    fopen_s(&fp, filename, "rb");
    if(fp == nullptr) {
        return;
    }

    game_map_.max_x_ = 0, game_map_.max_y_ = 0;

    for(int i = 0; i < MAX_MAP_Y; i++) {
        for (int j = 0; j < MAX_MAP_X; j++)
        {
            fscanf(fp, "%d", &game_map_.tile[i][j]);
            int val = game_map_.tile[i][j];
            if(val > 0)
            {
                if(j > game_map_.max_x_)
                {
                    game_map_.max_x_ = j;
                }

                if(i > game_map_.max_y_)
                {
                    game_map_.max_y_ = i;
                }
            }
        }
        
    }

    game_map_.max_x_ = (game_map_.max_x_+ 1)*TILE_SIZE;
    game_map_.max_y_ = (game_map_.max_y_ + 1)*TILE_SIZE;

    game_map_.start_x = game_map_.start_y = 0;

    game_map_.file_name = filename;
    fclose(fp);
}

void Game_Map::LoadTiles(SDL_Renderer * screen)
{
    char file_img[30];
    FILE *fp = nullptr;

    for (int i = 0; i < MAX_TILE; i++)
    {
        sprintf_s(file_img, "Assets/Maps/%d.png", i);

        fopen_s(&fp, file_img, "rb");

        if(fp == nullptr) continue;
        fclose(fp);

        tile_map[i].LoadImage(file_img, screen);
    }
    
}

void Game_Map::DrawMap(SDL_Renderer * screen)
{
    int x1 = 0, x2 = 0;

    int y1 = 0, y2 = 0;

    int map_x = 0, map_y = 0;

    map_x = game_map_.start_x/TILE_SIZE;
    x1 = (game_map_.start_x%TILE_SIZE)*(-1);
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    map_y = game_map_.start_y/TILE_SIZE;
    y1 = (game_map_.start_y%TILE_SIZE)*(-1);
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i = y1; i < y2; i += TILE_SIZE)
    {
        map_x = game_map_.start_x/TILE_SIZE;
        for (int j = x1; j < x2; j += TILE_SIZE)
        {
            int val = game_map_.tile[map_y][map_x];
            if(val > 0)
            {
                tile_map[val].SetRect(j , i);
                tile_map[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
    
}

void Game_Map::SetMap(Map& map_data) 
{
    game_map_ = map_data;
}