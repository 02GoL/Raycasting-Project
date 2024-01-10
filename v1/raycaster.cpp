#include"raycaster.h"

void Raycaster::drawRay(SDL_Renderer *renderWindow, vector<vector<int>> mapData, int xPos, int yPos){
    this->mapData = mapData;
    xPlayer = xPos;
    yPlayer = yPos;
    SDL_GetMouseState(&xMouse,&yMouse);
    SDL_SetRenderDrawColor(renderWindow,255,0,0,255);
    calculate();
    SDL_RenderDrawLine(renderWindow,xPlayer,yPlayer,xFinal,yFinal);
}
void Raycaster::calculate(){
    int xStepCount = 0;
    int yStepCount = 0;
    int xOffset = 0;
    int yOffset = 0;

    float xScaler;
    float yScaler;
    float xHyp = 0;
    float yHyp = 0;

    bool borderFound = false;

    int xGridPos = floor(xPlayer/cellSize);
    int yGridPos = floor(yPlayer/cellSize);

    int xDiff = (xMouse-xPlayer);
    int yDiff = (yMouse-yPlayer);

    //Finds the offset location of the player relative to the cell and 
    //the direction they are facing
    if(xDiff < 0){
        xOffset = xPlayer%cellSize;
    }else if(xDiff > 0){
        xOffset = cellSize-(xPlayer%cellSize);
    }
    if(yDiff < 0){
        yOffset = yPlayer%cellSize;
    }else if(yDiff > 0){
        yOffset = cellSize-(yPlayer%cellSize);
    }

    //Finds the scaler value and sets the inital hypotenuse from
    //the offset values for both x and y
    if(xDiff != 0){
        xScaler = sqrt(1+(float)(yDiff*yDiff)/(xDiff*xDiff));
        xHyp = xScaler*xOffset;
    }
    if(yDiff != 0){
        yScaler = sqrt(1+(float)(xDiff*xDiff)/(yDiff*yDiff));
        yHyp = yScaler*yOffset;
    }
    
    //Checks if index is occupied by a barrier
    while(!borderFound){
        if(xHyp == 0 || yHyp == 0){
            if(xHyp == 0 && yHyp == 0){
                xFinal = xPlayer;
                yFinal = yPlayer;
            }else if(xHyp == 0){ //Step in the y direction
                if(yDiff > 0){ //Checks depending on the direction the entity is facing
                    if(mapData[++yGridPos][xGridPos] == 1){ //check down
                        borderFound = true;
                        xFinal = xPlayer;
                        yFinal = yPlayer+(yOffset+yStepCount*cellSize);
                    }
                }else if(yDiff < 0){ 
                    if(mapData[--yGridPos][xGridPos] == 1){ //check up
                        borderFound = true;
                        xFinal = xPlayer;
                        yFinal = yPlayer-(yOffset+yStepCount*cellSize);
                    }
                }
                yHyp+=yScaler*cellSize;
                yStepCount++;
            }else if(yHyp == 0){ //Step in the x direction
                if(xDiff > 0){    
                    if(mapData[yGridPos][++xGridPos]){ //check right
                        borderFound = true;
                        xFinal = xPlayer+(xOffset+xStepCount*cellSize);
                        yFinal = yPlayer;
                    }
                }else{
                    if(mapData[yGridPos][--xGridPos]){ //check left
                        borderFound = true;
                        xFinal = xPlayer-(xOffset+xStepCount*cellSize);
                        yFinal = yPlayer;
                    }
                }
                xHyp+=xScaler*cellSize;
                xStepCount++;
            }
        }else{
            if(xHyp > yHyp){
                //step y
                if(yDiff > 0){ //point is fruther down than the player VV
                    //check down 
                    if(mapData[++yGridPos][xGridPos] == 1){
                        borderFound = true;
                        int yAdj = yOffset+yStepCount*cellSize;
                        setX(xDiff,yHyp,yAdj);
                        yFinal = yPlayer+yAdj;
                    }
                }else if(yDiff < 0){ //point is further up than the player ^^
                    //check up
                    if(mapData[--yGridPos][xGridPos] == 1){
                        borderFound = true;
                        int yAdj = yOffset+yStepCount*cellSize;
                        setX(xDiff,yHyp,yAdj);
                        yFinal = yPlayer-yAdj;
                    }
                }
                yHyp+=(yScaler*cellSize);
                yStepCount++;
            }else if(xHyp < yHyp){
                //step x
                if(xDiff > 0){ //point is further right than the player
                    //check right
                    if(mapData[yGridPos][++xGridPos] == 1){
                        borderFound = true;
                        int xAdj = xOffset+xStepCount*cellSize;
                        xFinal = xPlayer+xAdj;
                        setY(yDiff,xHyp,xAdj);
                    }
                }else if(xDiff <  0){ //point is further left than the player
                    //chekc left
                    if(mapData[yGridPos][--xGridPos] == 1){
                        borderFound = true;
                        int xAdj = xOffset+xStepCount*cellSize;
                        xFinal = xPlayer-xAdj;
                        setY(yDiff,xHyp,xAdj);
                    }
                }
                xHyp+=(xScaler*cellSize);
                xStepCount++;  
            }else if(xHyp == yHyp){
                if(xDiff > 0){
                    if(yDiff > 0){
                        if(mapData[++yGridPos][++xGridPos] == 1){
                            borderFound = true;
                            setX(xDiff,yHyp,yOffset+yStepCount*cellSize);
                            setY(yDiff,xHyp,xOffset+xStepCount*cellSize);
                        }
                    }else if(yDiff < 0){
                        if(mapData[--yGridPos][++xGridPos] == 1){
                            borderFound = true;
                            setX(xDiff,yHyp,yOffset+yStepCount*cellSize);
                            setY(yDiff,xHyp,xOffset+xStepCount*cellSize);
                        }
                    }
                }else if(xDiff < 0){
                    if(yDiff > 0){
                        if(mapData[++yGridPos][--xGridPos] == 1){
                            borderFound = true;
                            setX(xDiff,yHyp,yOffset+yStepCount*cellSize);
                            setY(yDiff,xHyp,xOffset+xStepCount*cellSize);
                        }
                    }else if(yDiff < 0){
                        if(mapData[--yGridPos][--xGridPos] == 1){
                            borderFound = true;
                            setX(xDiff,yHyp,yOffset+yStepCount*cellSize);
                            setY(yDiff,xHyp,xOffset+xStepCount*cellSize);
                        }
                    }
                }
                yHyp+=yScaler*cellSize;
                xHyp+=xScaler*cellSize;
                xStepCount++;
                yStepCount++;
            }
        }
    }
}
void Raycaster::setY(int difference,float xHyp, int adj){ 
    if(difference > 0){
        yFinal = yPlayer+sqrt(pow(xHyp,2)-pow(adj,2));
    }else if(difference < 0){
        yFinal = yPlayer-sqrt(pow(xHyp,2)-pow(adj,2));
    }
}
void Raycaster::setX(int difference, float yHyp, int adj){ 
    if(difference > 0){
        xFinal = xPlayer+sqrt(pow(yHyp,2)-pow(adj,2));
    }else if(difference < 0){
        xFinal = xPlayer-sqrt(pow(yHyp,2)-pow(adj,2));
    }
}