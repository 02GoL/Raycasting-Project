#include<iostream>
#include<vector>
#include<SDL2/SDL.h>

using namespace std;

class Map{
    private:
        vector<vector<int>> mapVector;
        int my;
        int mx;
        int cellSize;
    public:
        Map(vector<vector<int>> mapVector,int cellSize);
        void drawMap(SDL_Renderer *window);
        vector<vector<int>> getMap(){return mapVector;}
};