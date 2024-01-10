#include<iostream>
#include<vector>
#include<SDL2/SDL.h>

using namespace std;

class Player{
    private:
        SDL_Rect player;
        int moveSpeed;
        int turnRate;
        float angle;
    public:
        Player();
        void drawPlayer(SDL_Renderer *window);
        int getX();
        int getY();
        int getMoveSpeed();
        void setXPos(int ms);
        void setYPos(int ms);
        int getAngle();
        void setAngle(float tr);
};