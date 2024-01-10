#include"window.h"

void Window::init(int x,int y,int xDim, int yDim){
    this->xDim = xDim;
    this->yDim = yDim;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        cout << "Initializing...\n";
        window = SDL_CreateWindow(title,x,y,xDim,yDim,SDL_WINDOW_SHOWN);
        if(window){
            cout << "Window Crated...\n";
        }
        renderer = SDL_CreateRenderer(window,-1,0);
        if(renderer){
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            cout << "Render Created...\n";
        }
        isRunning = true;
    }else{
        isRunning = false;
    }
}

void Window::eventHandler(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){;
        if(event.type == SDL_QUIT){
            isRunning = false;
        }
        SDL_PushEvent(&event);
    }
}

void Window::render(Map map){
    SDL_RenderClear(renderer);

    map.drawMap(renderer);

    player.drawPlayer(renderer);
    ray.drawRay(renderer,map.getMap(),player.getX(),player.getY());

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderPresent(renderer);
}

void Window::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "System Quit...\n";
}

void Window::update(){
    SDL_Event keyE;
    if(SDL_PollEvent(&keyE)){
        if(keyE.type == SDL_KEYDOWN){
            if(SDLK_a == keyE.key.keysym.sym){
                player.setAngle(-1);
            }
            if(SDLK_d == keyE.key.keysym.sym){
                player.setAngle(1);
            }
            if(SDLK_s == keyE.key.keysym.sym){
                
            }
            if(SDLK_w == keyE.key.keysym.sym){
                float radians = player.getAngle()*M_PI/180.0f;
                cout << "moveing forward\n";
                player.setXPos(cos(radians)*1);
                player.setYPos(sin(radians)*1);
            }
        }
    }
}

bool Window::running(){
    return isRunning;
}