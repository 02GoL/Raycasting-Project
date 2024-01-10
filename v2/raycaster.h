#include<SDL2/SDL.h>
#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

class Raycaster{
    private:
        SDL_Renderer *renderWindow;
        vector<vector<int>> mapData;
        SDL_Rect wall;
        int cellSize = 100;
        int xMouse;
        int yMouse;
        int xPosFinal;
        int yPosFinal;
        int xPos;
        int yPos;
        int xDir;
        int yDir;
        int rayOffset;
        int rayCount;
        int wallOffset;
        float angle;
        float fov;
        float interval;
        float rayLength;
        float rayAngle;
    public:
        void rayInit(SDL_Renderer *renderWindow, vector<vector<int>> mapData);
        void renderRays(int xPos, int yPos, int xDir, int yDir, float angle);
        void renderWalls(int xPos, int yPos, int xDir, int yDir, float angle);
        void calculate();
        int setFinalPos(int currPos, int diff, float hyp, int adj);
        void addWalls();
};

