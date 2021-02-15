#include "snake.h"

snake::snake()
{
    head = {30,30,10,10};
    tail.push_back({24,32,5,5});
}

void snake::render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderFillRect(renderer, &head);
    for(unsigned int i = 0; i < tail.size(); i++){
        SDL_RenderFillRect(renderer, &tail[i]);
    }
}

snake::~snake()
{
    //dtor
}
