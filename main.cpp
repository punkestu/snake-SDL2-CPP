#include <SDL.h>
#include <vector>
#include <stdlib.h>

#define LEFT      0
#define RIGHT     1
#define UP        2
#define DOWN      3

struct turn{
      int x,y;
      int dir;
};

struct tail{
      SDL_Rect _tail;
      int dir;
};

bool in(SDL_Rect obj, SDL_Rect obj2){
      if(obj.x<obj2.x+obj2.w && obj2.x<obj.x+obj.w &&
         obj.y<obj2.y+obj2.h && obj2.y<obj.y+obj.h){
            return true;
      }else{
            return false;
      }
}

int randx(int min, int max){
      int ret;
      srand(SDL_GetTicks()%200*2-rand()-100+50);
      for(int i = 0; i < 1000; i++){
            ret = rand();
      }
      ret=(ret%(max-min+1))+min;
      return ret;
}

class snake{
      private:
            std::vector<tail> tails;
            std::vector<turn> turns;
            int latestDir;
            SDL_Rect head;
      public:
            snake();
            void move();
            void turnit(int dir);
            bool eat(SDL_Rect food);
            void render(SDL_Renderer* renderer);
};

snake::snake(){
      head = {0,0,30,30};
      latestDir = RIGHT;
      tails.push_back({{-29,1,28,28},RIGHT});
      tails.push_back({{-59,1,28,28},RIGHT});
}

void snake::move(){
      for(uint i = 0; i < tails.size(); i++){
            switch (tails[i].dir)
            {
            case LEFT:
                  tails[i]._tail.x-=30;
                  break;
            case RIGHT:
                  tails[i]._tail.x+=30;
                  break;
            case UP:
                  tails[i]._tail.y-=30;
                  break;
            case DOWN:
                  tails[i]._tail.y+=30;
                  break;
            
            default:
                  break;
            }
            for(uint j = 0; j < turns.size(); j++){
                  if(in(tails[i]._tail,{turns[j].x,turns[j].y,30,30})){
                        tails[i].dir = turns[j].dir;
                        if(i==tails.size()-1 && j == 0){
                              turns.erase(turns.begin());
                        }
                        break;
                  }
            }
      }
      switch (latestDir)
      {
      case LEFT:
            head.x-=30;
            break;
      case RIGHT:
            head.x+=30;
            break;
      case UP:
            head.y-=30;
            break;
      case DOWN:
            head.y+=30;
            break;
      
      default:
            break;
      }
}

void snake::turnit(int dir){
      if(dir!=latestDir){
            int comp;
            switch (latestDir){
            case LEFT:
                  comp = RIGHT;
                  break;
            case RIGHT:
                  comp = LEFT;
                  break;
            case UP:
                  comp = DOWN;
                  break;
            case DOWN:
                  comp = UP;
                  break;
            default:
                  break;
            }
            if(dir!=comp){
                  latestDir = dir;
                  turns.push_back({head.x,head.y,dir});
            }
      }
}

bool snake::eat(SDL_Rect food){
      if(in(food,head)){
            SDL_Rect temp;
            temp.w = 28;
            temp.h = 28;
            switch(tails.back().dir){
                  case LEFT   : temp.x = tails.back()._tail.x+30;temp.y = tails.back()._tail.y;break;
                  case RIGHT  : temp.x = tails.back()._tail.x-30;temp.y = tails.back()._tail.y;break;
                  case UP     : temp.y = tails.back()._tail.y+30;temp.x = tails.back()._tail.x;break;
                  case DOWN   : temp.y = tails.back()._tail.y-30;temp.x = tails.back()._tail.x;break;
                  default     : break;
            }
            tails.push_back({temp,tails.back().dir});
            return true;
      }else{
            return false;
      }
}

void snake::render(SDL_Renderer* renderer){
      SDL_SetRenderDrawColor(renderer, 0,0,0,255);
      SDL_RenderDrawRect(renderer, &head);
      for(uint i = 0; i < tails.size(); i++){
            SDL_RenderDrawRect(renderer, &tails[i]._tail);
      }
}

class frm{
      private:
            uint _frm;
      public:
            frm();
            bool limit(uint fps);
            void overLim(uint i);
};

frm::frm(){
      _frm = SDL_GetTicks();
}

void frm::overLim(uint i){
      _frm = i;
}

bool frm::limit(uint fps){
      if(SDL_GetTicks()-_frm>=1000/fps){
            _frm = SDL_GetTicks();
            return true;
      }else{
            return false;
      }
}

int main(int argc, char* argv[]){
      SDL_Init(SDL_INIT_EVERYTHING);

      SDL_Window* window = SDL_CreateWindow("snake",0,0,600,600,false);
      SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

      snake player = snake();
      frm _frm = frm();

      SDL_Rect food = {305,305,20,20};
      food.x=randx(0,19)*30+5;
      food.y=randx(0,19)*30+5;

      while (true){
            SDL_Event e;
            SDL_PollEvent(&e);
            if(e.type == SDL_QUIT){
                  break;
            }
            if(e.type == SDL_KEYDOWN){
                  if(e.key.keysym.sym == SDLK_a){
                        player.turnit(LEFT);
                        _frm.overLim(1000);
                  }else if(e.key.keysym.sym == SDLK_d){
                        player.turnit(RIGHT);
                        _frm.overLim(1000);
                  }else if(e.key.keysym.sym == SDLK_w){
                        player.turnit(UP);
                        _frm.overLim(1000);
                  }else if(e.key.keysym.sym == SDLK_s){
                        player.turnit(DOWN);
                        _frm.overLim(1000);
                  }
            }

            if(_frm.limit(5)){
                  if(player.eat(food)){
                        food.x=randx(0,19)*30+5;
                        food.y=randx(0,19)*30+5;
                        SDL_Log("food: %d,%d",food.x,food.y);
                  }
                  player.move();
            }


            SDL_SetRenderDrawColor(renderer, 255,255,255,255);
            SDL_RenderClear(renderer);

            player.render(renderer);
            SDL_SetRenderDrawColor(renderer, 255,0,0,255);
            SDL_RenderFillRect(renderer, &food);

            SDL_RenderPresent(renderer);
      }
      
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
      
      return 0;
}