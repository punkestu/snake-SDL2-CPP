#ifndef SNAKE_H
#define SNAKE_H

#include "include.h"

class snake
{
private:
    SDL_Rect head;
    std::vector <SDL_Rect> tail;
    short lcmd;
public:
    snake();
    void render(SDL_Renderer* renderer);
    void control(SDL_Event* event);
    void update();
    ~snake();
};

#endif // SNAKE_H
