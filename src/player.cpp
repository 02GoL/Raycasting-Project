#include"player.h"

void Player::playerInit(SDL_Renderer *renderWindow,vector<vector<int>> mapData){
    this->renderWindow = renderWindow;
    this->mapData = mapData;
    playerSprite.h = 15;
    playerSprite.w = 15;
    playerSprite.x = 0;
    playerSprite.y = 0;
    turnRate = 4;
    moveSpeed = 5;
    dx = cos(angle)*moveSpeed;
    dy = sin(angle)*moveSpeed;
    ray.rayInit(renderWindow,mapData);
}

void Player::setPosition(int x, int y){
    playerSprite.x = x;
    playerSprite.y = y;
}

void Player::renderPlayer(){
    SDL_SetRenderDrawColor(renderWindow,0,255,0,255);
    //SDL_RenderFillRect(renderWindow,&playerSprite);
    
    ray.renderWalls(playerSprite.x+(playerSprite.h/2),
                playerSprite.y+(playerSprite.w/2),
                (playerSprite.x+(playerSprite.h/2))+dx,
                (playerSprite.y+(playerSprite.w/2))+dy,
                angle);
}

void Player::inputHandler(){
    SDL_Event keyE;
    while(SDL_PollEvent(&keyE)){
        if(keyE.type == SDL_KEYDOWN){
            if(SDLK_q == keyE.key.keysym.sym){
                turnDir = 1;
            }
            if(SDLK_e == keyE.key.keysym.sym){
                turnDir = -1;
            }
            if(SDLK_a == keyE.key.keysym.sym){
                sideOffset = 1;
                velocity = -1;
            }
            if(SDLK_d == keyE.key.keysym.sym){
                sideOffset = 1;
                velocity = 1;
            }
            if(SDLK_s == keyE.key.keysym.sym){
                velocity = -1;
            }
            if(SDLK_w == keyE.key.keysym.sym){
                velocity = 1;
            }
        }
        if(keyE.type == SDL_KEYUP){
            if(keyE.key.keysym.sym == SDLK_w || 
               keyE.key.keysym.sym == SDLK_s || 
               keyE.key.keysym.sym == SDLK_a ||
               keyE.key.keysym.sym == SDLK_d){
                velocity = 0;
                sideOffset = 0;
            }
            if(keyE.key.keysym.sym == SDLK_q || 
               keyE.key.keysym.sym == SDLK_e){
                turnDir = 0;
            }
        }
    }
}

void Player::movementHandler(){
    if(turnDir == 1){
        angle-=turnRate*M_PI/180.0f;
        if(angle < 0){
            angle+=2*M_PI;
        }
    }else if(turnDir == -1){
        angle+=turnRate*M_PI/180.0f;
        if(angle > 2*M_PI){
            angle-=2*M_PI;
        }
    }
    dx = cos(angle+(M_PI/2*sideOffset))*moveSpeed;
    dy = sin(angle+(M_PI/2*sideOffset))*moveSpeed;

    // Play position + offset since the position is from the top left
    int gridX = floor((playerSprite.x+8+dx*velocity*4)/100);
    int gridY = floor((playerSprite.y+8+dy*velocity*4)/100);
    if(mapData[gridY][gridX] == 1){
        velocity = 0;
    }

    playerSprite.x+=dx*velocity;
    playerSprite.y+=dy*velocity;
}
