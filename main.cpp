#include <snake.h>

int main(int argc, char* argv[]){
    snake player = snake();
    SDL_Window* window = SDL_CreateWindow("app", 100, 100, 480, 480, false);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;

    Uint32 frame = SDL_GetTicks();
    while(true){
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)){
            break;
        }
        player.control(&event);
        if(SDL_GetTicks()-frame >= 1000/15){
            player.update();
            frame = SDL_GetTicks();
        }
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
        player.render(renderer);

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
