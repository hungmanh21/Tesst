#include <main.h>

int main(int argc, char* args[]){
    cout << "I'm running normally???";

    SDL_Init(SDL_INIT_EVERYTHING);
    auto window = SDL_CreateWindow("HELLO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 720, 0);
    auto renderer = SDL_CreateRenderer(window, - 1, 0 );
    SDL_Event e;

    bool running = true;

    while(running){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0 , 0 , 0 , 255);
        SDL_RenderClear(renderer);

        SDL_Rect p = {100, 100, 100 , 100};
        SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255);

        SDL_RenderFillRect( renderer, &p );

        SDL_RenderPresent(renderer);
        SDL_Delay(25);
    }

    return 0;
}