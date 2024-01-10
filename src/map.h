#include<iostream>
#include<vector>
#include<SDL2/SDL.h>

using namespace std;

class Map{
    private:
        vector<vector<int>> mapData;
        int my;
        int mx;
        int cellSize;
    public:
        void mapInit();
        void renderMap(SDL_Renderer *renderWindow);
        int getMapX(){return mx;}
        int getMapY(){return my;}
        int getMapCellSize(){return cellSize;}
        vector<vector<int>> getMap(){return mapData;}
};