#include"player.h"

Player::Player(){
    moveSpeed = 10;
    turnRate = 20;
    player.x = 242;
    player.y = 242;
    player.h = 15;
    player.w = 15;
}

void Player::drawPlayer(SDL_Renderer *window){
    SDL_SetRenderDrawColor(window,0,0,255,255);
    SDL_RenderFillRect(window,&player);
}

int Player::getMoveSpeed(){
    return moveSpeed;
}

void Player::setXPos(int ms){
    player.x+=ms;
}

void Player::setYPos(int ms){
    player.y+=ms;
}

void Player::setAngle(float tr){
    angle+=turnRate*tr;
}

int Player::getAngle(){
    return angle;
}

int Player::getX(){
    return player.x+8;
}

int Player::getY(){
    return player.y+8;
}
