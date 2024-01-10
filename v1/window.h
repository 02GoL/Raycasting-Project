#include<iostream>
#include<vector>
#include<SDL2/SDL.h>
#include"map.h"
#include"player.h"
#include"raycaster.h"

using namespace std;

class Window{
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        Player player;
        Raycaster ray;
        const char *title = "Raycasting";
        int xDim;
        int yDim;
        bool isRunning;
    public: 
        void init(int x, int y, int xDim, int yDim);
        void eventHandler();
        void render(Map map);
        void clean();
        void update();
        bool running();

};
