#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Game_Map.h"
#include "Player.h"
#include "Player_Health.h"
#include "Enemy.h"
#include "Bullet.h"
#include "TextObject.h"
#include "Menu.h"


using namespace std;

Mix_Music *bg_music = nullptr;

// Font
TTF_Font* font[kFonts];
// 0. Arial
// 1. Calligraphy/ Thu phap
// 2. Pen brush/ but long net to

bool Init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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
        // open audio and load the audio
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            std::cerr << "Can't open audio" << std::endl;
            return false;
        }
        bg_music = Mix_LoadMUS("Assets\\Music\\game_music.mp3");
        if(bg_music == nullptr)
        {
            std::cerr << "Can't load music" << std::endl;
            return false;
        }

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

        // Khởi tạo đối tượng text
        if(TTF_Init() == -1)
        {
            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }
        
        // Initilize font
        font[0] = TTF_OpenFont("Assets\\font\\ArialCE.ttf", 30);
        font[1] = TTF_OpenFont("Assets\\font\\VNI-Thu fap2.ttf", 30);
        font[2] = TTF_OpenFont("Assets\\font\\Vbutlong.ttf", 70);
        for (int i = 0; i < kFonts; i ++) {
            if (font[i] == NULL) {
                std::cerr << "Failed to initilize font" << std::endl;
                return false;
            }
        }
    }
    return success;
}

void Close(){
    
    SDL_DestroyWindow(g_Window);
    g_Window = nullptr;

    SDL_DestroyRenderer(g_Screen);
    g_Screen = nullptr;

    Mix_FreeMusic(bg_music);
    bg_music = nullptr;

    IMG_Quit();
    SDL_Quit();
    Mix_Quit();


}

// no pros
vector<Enemy*> MakeEnemiesList(){
    vector<Enemy*> list_enemies;
    
    // enemy đứng yên , sau này đổi thành trụ, đứng sát mép map hoặc ở giữa bản đồ
    Enemy* enemy_objs = new Enemy[10];

    for (int i = 0; i < 10; i++)
    {
        Enemy* p_enemy = (enemy_objs + i);
        if(p_enemy != NULL){
            p_enemy->LoadImg("Assets/Enemy/big_zom_L_R.png", g_Screen);
            
            p_enemy -> set_x_pos(SCREEN_WIDTH * 3 / 4 + i * SCREEN_WIDTH / 2);
            // middle of height screen
            p_enemy-> set_y_pos(SCREEN_HEIGHT * 2 / 3 - 50);

            // p2 
            p_enemy->set_type_move(Enemy::STATIC_ENEMY);
            p_enemy->set_input_left(0);
            
            // p3 bullet
            Bullet * p_bullet = new Bullet();
            p_enemy -> InitBullet(p_bullet, g_Screen);
            
            list_enemies.push_back(p_enemy); 
        }
    }

    // enemy di chuyen, lính canh tuần tra 
    Enemy *dynamic_enemies = new Enemy[5];

    for (int i = 0; i < 5; i++)
    {
        Enemy *p_enemy = (dynamic_enemies + i);
        if (p_enemy != NULL)
        {
            p_enemy->LoadImg("Assets/Enemy/big_zom_L_R.png", g_Screen);

            p_enemy->set_type_move(Enemy::MOVE_IN_SPACE_ENEMY);

            p_enemy->set_x_pos(SCREEN_WIDTH * 2 / 3 + i * SCREEN_WIDTH / 2);
            // middle of height screen
            p_enemy->set_y_pos(SCREEN_HEIGHT / 3 );

            // set vung di chuyen qua lai
            int pos1 = p_enemy->get_x_pos() - 40;
            int pos2 = p_enemy->get_x_pos() + 40;

            p_enemy->set_animation_pos(pos1, pos2);
            p_enemy->set_input_left(1);
            // p3 bullet
            // Bullet *p_bullet = new Bullet();
            // p_enemy->InitBullet(p_bullet, g_Screen);

            list_enemies.push_back(p_enemy);
        }
    }

    return list_enemies;
    
}

int main(int argc, char* args[]){
    Menu GameMenu;
    if(Init() == false)
    {
        return -1;
    }
    // map
    Game_Map game_map;
    game_map.LoadMap("Assets/Maps/game_map.dat");
    game_map.LoadTiles(g_Screen);

    // player
    Player player;
    player.LoadImg("Assets/Player/Player-Sprite.png", g_Screen);

    // Enemies
    vector<Enemy*> list_enemies = MakeEnemiesList();

    // Text
    // Time -> Count Down
    TextObject time_game;
    
    // main loop
    bool is_quit = false;
    int top_x = 0, top_y = 0;

    // Menu
    GameMenu.Load(g_Screen);
    int ret_menu = GameMenu.Show(g_Screen, font);
    if (ret_menu == 1) {
        is_quit = true;
    }

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
        // Play background music
        // if(Mix_PlayingMusic() == 0)
        // {
        //     Mix_PlayMusic(bg_music, -1);
        // }
        // else if(Mix_PausedMusic()) Mix_ResumeMusic();

        // clear va load background
        SDL_SetRenderDrawColor(g_Screen, 255, 255, 255, 255);
        SDL_RenderClear(g_Screen);

        // Xu ly chuyen dong & va cham
        Map map_data = game_map.getMap();
        Map map_data_old = game_map.getMap();

        player.SetMapXY(map_data.start_x, map_data.start_y);
        player.CheckToMap(map_data); // player đã di chuyển x,y_pos
        player.CenterEntityOnMap(map_data, top_x, top_y);
        
      
        // Ve map
        game_map.SetMap(map_data); // di chuyển map theo player
        game_map.DrawMap(g_Screen);
       

        player.Render(g_Screen);
        for (int i = 0; i < list_enemies.size(); i++)
        { // BUG
            Enemy *p_enemy = list_enemies.at(i);
            if (p_enemy != NULL)
            {
                p_enemy->SetMapXY(map_data.start_x, map_data.start_y); // lấy vị trí map_x map_y
             
                p_enemy->ImpMoveType(g_Screen); // thừa gscreen- sửa sau

                p_enemy->DoPlayer(map_data);                                // enemy bắt đầu di chuyển
                                                                            // đạn bắn
                p_enemy->MakeBullet(g_Screen, SCREEN_WIDTH, SCREEN_HEIGHT, map_data_old); // bullet bắt đầu lấy rect_x
                
                p_enemy->Show(g_Screen); // vẽ enemy và bullet

            }


            // va cham kiem vs enemy
            SDL_Rect blade_Rect = player.get_slash_Rect();
            SDL_Rect enemy_Rect = p_enemy->GetRect();

            bool is_collied = SDLCommonFunc::CheckCollision(blade_Rect, enemy_Rect);
            if(is_collied)
            {
                p_enemy->Free();
                list_enemies.erase(list_enemies.begin()+i);
            }

            // va cham dan vs player
            std::vector<Bullet*> p_enemy_bullets = p_enemy->get_bullet_list();
            for(int j = 0; j < p_enemy_bullets.size(); j++)
            {
                Bullet* temp_bullet = p_enemy_bullets.at(j);
                if(temp_bullet != nullptr)
                {
                    SDL_Rect player_Rect = player.get_player_Rect();
                    bool is_collied2 = SDLCommonFunc::CheckCollision(temp_bullet->get_bullet_rect(), player_Rect);
                    if(is_collied2)
                    {
                        std::cerr << player_Rect.x << " " << player_Rect.y << " " << player_Rect.w << " " << player_Rect.h << std::endl;
                        std::cerr << temp_bullet->get_bullet_rect().x << " " << temp_bullet->get_bullet_rect().y << " " << temp_bullet->get_bullet_rect().w << " " << temp_bullet->get_bullet_rect().w << std::endl << std::endl; 
                        player.DecreaseHp();
                        p_enemy->RemoveBullet(j);
                        player.Set_Position(map_data.start_x + 128,map_data.start_y + 320);
                        // p->enemy->InitBullet
                        
                    }
                }
            }

            if(player.get_hp() <= 0)
            {
                is_quit = true;
                break;
            }
        }
        // Time
        std::string str_time = "Time: ";
        Uint32 time_val = SDL_GetTicks() / 1000;
        Uint32 val_time = 300 - time_val;
        if (val_time <= 0){
            // message: game over
        } else {
            std::string str_val = std::to_string(val_time);
            str_time += str_val;
            time_game.Set(SCREEN_WIDTH - 200, 15, str_time, TextObject::WHITE_TEXT);
    
            time_game.LoadFromRenderText(font[0], g_Screen);
            time_game.RenderText(g_Screen);
        }

        // Cap nhat man hinh
        SDL_RenderPresent(g_Screen);
    }
    for (int i = 0; i < list_enemies.size(); i++){
        Enemy * p_enemy = list_enemies.at(i);
        if(p_enemy){
            p_enemy ->Free();
            p_enemy = NULL;
        }
    }
    
    list_enemies.clear();

    Close();
    return 0;
}