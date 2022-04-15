// #include "Audio.h"

// bool Audio::Init()
// {
//     if(SDL_Init(SDL_INIT_AUDIO) < 0)
//     {
//         std::cerr << "Audio can't be initialized" << std::endl;
//         return false;
//     }

//     if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048, 0) < 0)
//     {
//         std::cerr << "Audio can't be opened" << std::endl;
//         return false;
//     }

//     bg_music = Mix_LoadMUS("Assets\\Music\\bg_music.mp3");
//     coin_music = 
// }