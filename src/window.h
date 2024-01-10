#include<iostream>
#include<SDL2/SDL.h>
#include"map.h"
#include"player.h"

using namespace std;

class Window{
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        Map map;
        Player player;
        const char *title = "Raycasting";
        int xDim;
        int yDim;
        bool isRunning;
    public: 
        void init(int x, int y);
        void eventHandler();
        void render();
        void clean();
        void update();
        bool running();
};
