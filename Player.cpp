#include "Player.h"

// Making a player class

Player::Player(Vector2 pos, float sz, Color c)
: position(pos),
    size (sz), 
    color (c){}

void Player::Draw(Texture2D skiier){
    DrawTextureV(skiier, position, color); 
}

void Player::Move(Vector2 offset){
    position.x += offset.x;
    position.y += offset.y;

}

Rectangle Player::GetRect()const { 
    Rectangle playerRect = {position.x, position.y, size, size};
    return playerRect;

}

float Player::GetSize()const {
    return size;
}

Vector2 Player::GetPosition() const{
    return position;

}
