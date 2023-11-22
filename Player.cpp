#include "Player.H"

Player::Player(Vector2 pos, float r, Color c)
: position(pos),
radius (r),
color (c){}

void Player ::Draw(){
    DrawCircleV(position, radius, color);
}

void Player::Move(Vector2 offset){
    position.x += offset.x;
    position.y += offset.y;

}

float Player::GetRadius() const{
    return radius;

}

Vector2 Player::GetPosition() const{
    return position;

}
