#include"map.h"

Map::Map(vector<vector<int>> mapVector,int cellSize){
    this->mapVector = mapVector;
    this->my = this->mapVector.size();
    this->mx = this->mapVector[0].size();
    this->cellSize = cellSize;
}
void Map::drawMap(SDL_Renderer *window){
    SDL_Rect cell;
    cell.h = cellSize*0.95;
    cell.w = cellSize*0.95;
    
    int offset = (cellSize-cellSize*0.95)/2;
    for(int y = 0; y < my; y++){
        for(int x = 0; x < mx; x++){
            if(mapVector[y][x] == 1){
                SDL_SetRenderDrawColor(window,255,255,255,255);
            }else{
                SDL_SetRenderDrawColor(window,0,255,0,255);
            }
            cell.x = x*cellSize+offset;
            cell.y = y*cellSize+offset;
            SDL_RenderFillRect(window,&cell);
        }
    }
}