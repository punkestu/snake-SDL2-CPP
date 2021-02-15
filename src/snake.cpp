#include "snake.h"

snake::snake()
{
    lcmd = 0;
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

void snake::control(SDL_Event* event){
    if(event->type == SDL_KEYDOWN){
        if(event->key.keysym.sym == SDLK_w){
            if(lcmd != 2){
                lcmd = 1;
            }
        }
        if(event->key.keysym.sym == SDLK_s){
            if(lcmd != 1){
                lcmd = 2;
            }
        }
        if(event->key.keysym.sym == SDLK_a){
            if(lcmd != 4){
                lcmd = 3;
            }
        }
        if(event->key.keysym.sym == SDLK_d){
            if(lcmd != 3){
                lcmd = 4;
            }
        }
    }
}

void snake::update(){
    switch(lcmd){
    case 1:
        head.y-=10;
        break;
    case 2:
        head.y+=10;
        break;
    case 3:
        head.x-=10;
        break;
    case 4:
        head.x+=10;
        break;
    default:
        break;
    }
}

snake::~snake()
{
    //dtor
}
