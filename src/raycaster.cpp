#include"raycaster.h"

void Raycaster::rayInit(SDL_Renderer *renderWindow, vector<vector<int>> mapData){
    this->renderWindow = renderWindow;
    this->mapData = mapData;
    this->fov = 60*M_PI/180; //FOV in degees -> FOV in radians
    this->rayCount = 400;
    this->wallOffset = 0;
}

void Raycaster::renderRays(int xPos, int yPos, int xDir, int yDir, float angle){
    this->angle = angle-(fov/2); //Offsets the starting angle
    this->rayAngle = angle-(fov/2);
    this->xPos = xPos;
    this->yPos = yPos;
    this->xDir = xDir;
    this->yDir = yDir;

    SDL_SetRenderDrawColor(renderWindow,255,0,0,255);
    for(int i = 0; i < rayCount; i++){
        calculate();
        SDL_RenderDrawLine(renderWindow,this->xPos,this->yPos,
                           xPosFinal,yPosFinal);
    }
}

void Raycaster::renderWalls(int xPos, int yPos, int xDir, int yDir, float angle){
    this->angle = angle; //Offsets the starting angle
    this->rayAngle = angle-(fov/2);
    this->xPos = xPos;
    this->yPos = yPos;
    this->xDir = xDir;
    this->yDir = yDir;
    
    SDL_SetRenderDrawColor(renderWindow,255,0,0,255);
    for(int i = 0; i < rayCount; i++){
        calculate();
        addWalls();
    }
}

void Raycaster::calculate(){
    int xGridPos = floor(xPos/cellSize);
    int yGridPos = floor(yPos/cellSize);
    int xStepCount = 0;
    int yStepCount = 0;
    int xOffset = 0;
    int yOffset = 0;

    float xScaler;
    float yScaler;
    float xHyp = 0;
    float yHyp = 0;

    bool borderFound = false;

    //Temporarily sets a relative values to get the difference for the ray offset
    int xDiff = (xDir-xPos)*1000;
    int yDiff = (yDir-yPos)*1000;
    float hyp = sqrt(pow(xDiff,2)+pow(yDiff,2)); 
    
    if(rayAngle > 2*M_PI){
        rayAngle-=2*M_PI;
    }
    if(rayAngle < 0){
        rayAngle+=2*M_PI;
    }
    xDiff = hyp*cos(rayAngle);
    yDiff = hyp*sin(rayAngle);
    rayAngle+=fov/(rayCount-1);

    //Finds the offset location of the player relative to the cell
    if(xDiff < 0){
        xOffset = xPos%cellSize;
    }else if(xDiff > 0){
        xOffset = cellSize-(xPos%cellSize);
    }
    
    if(yDiff < 0){
        yOffset = yPos%cellSize;
    }else if(yDiff > 0){
        yOffset = cellSize-(yPos%cellSize);
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
        if(xDiff == 0 || yDiff == 0){
            if(xDiff == 0 && yDiff == 0){
                xPosFinal = xPos;
                yPosFinal = yPos;
            }else if(xDiff == 0){ //Step in the y direction
                if(yDiff > 0){ //Checks depending on the direction the entity is facing
                    if(mapData[++yGridPos][xGridPos] == 1){ //Check down
                        borderFound = true;
                        xPosFinal = xPos;
                        yPosFinal = yPos+(yOffset+yStepCount*cellSize);  
                        SDL_SetRenderDrawColor(renderWindow,255,0,0,255);                  }
                }else if(yDiff < 0){ 
                    if(mapData[--yGridPos][xGridPos] == 1){ //Check up
                        borderFound = true;
                        xPosFinal = xPos;
                        yPosFinal = yPos-(yOffset+yStepCount*cellSize);
                        SDL_SetRenderDrawColor(renderWindow,255,0,0,255);
                    }
                }
                yHyp+=yScaler*cellSize;
                yStepCount++;
            }else if(yDiff == 0){ //Step in the x direction
                if(xDiff > 0){    
                    if(mapData[yGridPos][++xGridPos]){ //Check right
                        borderFound = true;
                        xPosFinal = xPos+(xOffset+xStepCount*cellSize);
                        yPosFinal = yPos;
                        SDL_SetRenderDrawColor(renderWindow,200,0,0,255);
                    }
                }else if(xDiff < 0){
                    if(mapData[yGridPos][--xGridPos]){ //Check left
                        borderFound = true;
                        xPosFinal = xPos-(xOffset+xStepCount*cellSize);
                        yPosFinal = yPos;
                        SDL_SetRenderDrawColor(renderWindow,200,0,0,255);
                    }
                }
                xHyp+=xScaler*cellSize;
                xStepCount++;
            }
        }else{
            if(xHyp > yHyp){ //step y
                if(yDiff > 0){ //point is fruther down than the player VV
                    if(mapData[++yGridPos][xGridPos] == 1){ //check down 
                        borderFound = true;
                        int yAdj = yOffset+yStepCount*cellSize;
                        xPosFinal = setFinalPos(xPos,xDiff,yHyp,yAdj);
                        yPosFinal = yPos+yAdj;
                        SDL_SetRenderDrawColor(renderWindow,255,0,0,255);
                    }
                }else if(yDiff < 0){ //point is further up than the player ^^
                    //check up
                    if(mapData[--yGridPos][xGridPos] == 1){
                        borderFound = true;
                        int yAdj = yOffset+yStepCount*cellSize;
                        xPosFinal = setFinalPos(xPos,xDiff,yHyp,yAdj);
                        yPosFinal = yPos-yAdj;
                        SDL_SetRenderDrawColor(renderWindow,255,0,0,255);
                    }
                }
                yHyp+=(yScaler*cellSize);
                yStepCount++;
            }else if(xHyp < yHyp){
                //step x
                if(xDiff > 0){ //point is further right than the player
                    if(mapData[yGridPos][++xGridPos] == 1){//Check right
                        borderFound = true;
                        int xAdj = xOffset+xStepCount*cellSize;
                        xPosFinal = xPos+xAdj;
                        yPosFinal = setFinalPos(yPos,yDiff,xHyp,xAdj);
                        SDL_SetRenderDrawColor(renderWindow,200,0,0,255);
                    }
                }else if(xDiff <  0){ //point is further left than the player
                    if(mapData[yGridPos][--xGridPos] == 1){ //Check left
                        borderFound = true;
                        int xAdj = xOffset+xStepCount*cellSize;
                        xPosFinal = xPos-xAdj;
                        yPosFinal = setFinalPos(yPos,yDiff,xHyp,xAdj);
                        SDL_SetRenderDrawColor(renderWindow,200,0,0,255);
                    }
                }
                xHyp+=(xScaler*cellSize);
                xStepCount++;  
            }else{
                if(xDiff > 0){
                    if(yDiff > 0){
                        if(mapData[++yGridPos][++xGridPos] == 1){
                            borderFound = true;
                            xPosFinal = setFinalPos(xPos,xDiff,yHyp,yOffset+yStepCount*cellSize);
                            yPosFinal = setFinalPos(yPos,yDiff,xHyp,xOffset+xStepCount*cellSize);
                        }
                    }else if(yDiff < 0){
                        if(mapData[--yGridPos][++xGridPos] == 1){
                            borderFound = true;
                            xPosFinal = setFinalPos(xPos,xDiff,yHyp,yOffset+yStepCount*cellSize);
                            yPosFinal = setFinalPos(yPos,yDiff,xHyp,xOffset+xStepCount*cellSize);
                        }
                    }
                }else if(xDiff < 0){
                    if(yDiff > 0){
                        if(mapData[++yGridPos][--xGridPos] == 1){
                            borderFound = true;
                            xPosFinal = setFinalPos(xPos,xDiff,yHyp,yOffset+yStepCount*cellSize);
                            yPosFinal = setFinalPos(yPos,yDiff,xHyp,xOffset+xStepCount*cellSize);
                        }
                    }else if(yDiff < 0){
                        if(mapData[--yGridPos][--xGridPos] == 1){
                            borderFound = true;
                            xPosFinal = setFinalPos(xPos,xDiff,yHyp,yOffset+yStepCount*cellSize);
                            yPosFinal = setFinalPos(yPos,yDiff,xHyp,xOffset+xStepCount*cellSize);
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

int Raycaster::setFinalPos(int currPos, int diff, float hyp, int adj){ //XFinalPos
    if(diff > 0){
        return currPos+sqrt(pow(hyp,2)-pow(adj,2));
    }else if(diff < 0){
        return currPos-sqrt(pow(hyp,2)-pow(adj,2));
    }else{
        return currPos;
    }
}

void Raycaster::addWalls(){
    int xDiff = xPosFinal-xPos;
    int yDiff = yPosFinal-yPos;
    float ca = angle-rayAngle;
    if(ca < 0){
        ca+=2*M_PI;
    }
    if(ca > 2*M_PI){
        ca-=2*M_PI;
    }

    float dist = sqrt(pow(xDiff,2)+pow(yDiff,2))*cos(ca);

    float lineH = (cellSize*800)/dist;
    if(lineH > 800){
        lineH = 800;
    }

    wall.w = 800/rayCount; //Screen size/raycount
    wall.h = lineH;
    wall.x = wallOffset;
    wall.y = 400-(lineH/2);
    
    SDL_RenderFillRect(renderWindow,&wall);
    wallOffset+=800/rayCount;
    if(wallOffset >= 800){
        wallOffset = 0;
    }
}