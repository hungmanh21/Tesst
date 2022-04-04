#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILE 30

class TileMap : public BaseObject
{
public:
    TileMap() {}
    ~TileMap() {}
};

class Game_Map
{
public:
    Game_Map() {}
    ~Game_Map() {}

    void LoadMap(char* filename);

    void LoadTiles(SDL_Renderer* screen);

    void DrawMap(SDL_Renderer* screen);
    
    Map getMap() const {return game_map_;}

    void SetMap(Map& map_data);

private:
    Map game_map_;
    TileMap tile_map[MAX_TILE];
    
};



#endif 