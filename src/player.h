#include<iostream>
#include<vector>
#include<SDL2/SDL.h>
#include"raycaster.h"

using namespace std;

class Player{
    private:
        SDL_Rect playerSprite;
        SDL_Rect directionLine;
        SDL_Renderer *renderWindow;
        vector<vector<int>> mapData;
        Raycaster ray;
        int moveSpeed;
        int turnRate;
        int velocity;
        int sideOffset;
        int dx;
        int dy;
        int turnDir;
        float angle;
    public:
        void playerInit(SDL_Renderer *window,vector<vector<int>> mapData);
        void setPosition(int x, int y);
        void renderPlayer();
        void inputHandler();
        void movementHandler();
        void setX();
};