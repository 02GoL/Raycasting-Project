#include"map.h"

void Map::mapInit(){
    this->mapData = {
        {1,1,1,1,1,1,1,1},
        {1,0,0,0,1,0,0,1},
        {1,1,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,1,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,0,1},
        {1,1,1,1,1,1,1,1}
    };
    this->mx = mapData[0].size();
    this->my = mapData.size();
    this->cellSize = 100;
}

void Map::renderMap(SDL_Renderer *renderWindow){
    SDL_Rect cell;
    cell.h = cellSize*0.95;
    cell.w = cellSize*0.95;
    
    int offset = (cellSize-cellSize*0.95)/2;

    for(int y = 0; y < my; y++){
        for(int x = 0; x < mx; x++){
            if(mapData[y][x] == 1){
                SDL_SetRenderDrawColor(renderWindow,255,255,255,255);
            }else{
                SDL_SetRenderDrawColor(renderWindow,50,50,75,255);
            }
            cell.x = x*cellSize+offset;
            cell.y = y*cellSize+offset;
            SDL_RenderFillRect(renderWindow,&cell);
        }
    }
}