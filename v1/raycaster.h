#include<SDL2/SDL.h>
#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

class Raycaster{
    private:
        vector<vector<int>> mapData;
        int cellSize = 100;
        int xMouse;
        int yMouse;
        int xFinal;
        int yFinal;
        int xPlayer;
        int yPlayer;
    public:
        void drawRay(SDL_Renderer *renderWindow, vector<vector<int>> mapData, int xPos, int yPos);
        void calculate();
        void setY(int difference,float xHyp, int adj);
        void setX(int difference, float yHyp, int adj);
};

