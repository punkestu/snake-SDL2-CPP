#ifndef SNAKE_H
#define SNAKE_H

#include "include.h"

class snake
{
private:
    SDL_Rect head;
    std::vector <SDL_Rect> tail;
public:
    snake();
    void render(SDL_Renderer* renderer);
    ~snake();
};

#endif // SNAKE_H
