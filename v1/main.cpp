#include<iostream>
#include"window.h"

using namespace std;

Window *frame = nullptr;

int main(){
    vector<vector<int>> mapData = {
        {1,1,1,1,1,1,1,1},
        {1,0,0,0,1,0,0,1},
        {1,1,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,1},
        {1,0,0,0,0,1,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,0,1},
        {1,1,1,1,1,1,1,1}
    };
    Map map(mapData,100);

    Uint32 frameStart;
    int frameTime;

    const int FPS = 300;
    const int frameDelay = 1000/FPS;

    frame = new Window();
    frame->init(SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,mapData[0].size()*100,mapData.size()*100);
    
    while(frame->running()){
        frameStart = SDL_GetTicks();
        
        frame->eventHandler();
        frame->update();
        frame->render(map);
        
        frameTime = SDL_GetTicks()-frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay-frameTime);
        }
    }

    frame->clean();

    return 0;
}