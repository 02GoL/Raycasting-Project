#include"window.h"

void Window::init(int x,int y){
    map.mapInit();
    this->xDim = 800;
    this->yDim = 800;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        cout << "Initializing...\n";
        window = SDL_CreateWindow(title,x,y,xDim,yDim,SDL_WINDOW_SHOWN);
        if(window){
            cout << "Window Created...\n";
        }
        renderer = SDL_CreateRenderer(window,-1,0);
        if(renderer){
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            cout << "Render Created...\n";
        }

        player.playerInit(renderer,map.getMap());
        player.setPosition(420,420);

        isRunning = true;
    }else{
        isRunning = false;
    }
}

void Window::eventHandler(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            isRunning = false;
        }
        SDL_PushEvent(&event);
    }
    player.inputHandler();
}

void Window::render(){
    SDL_RenderClear(renderer);
    
    //map.renderMap(renderer);
    player.renderPlayer();
    
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
    player.movementHandler();
}

bool Window::running(){
    return isRunning;
}