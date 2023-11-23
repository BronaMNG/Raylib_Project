#include "Coins.h"

Coins::Coins(Vector2 pos, float r, Color c, float s)
  : position(pos),
      radius(r),
      color(c),
      speed(s) {}

Coins::Coins()
    : position({0, 0}),
      radius(0.0f),
      color(BLANK),
      speed(0.0f) {}

void Coins::Draw(){
    DrawCircleV(position, radius, color);
}

void Coins::Update() {
    position.y += speed;
}

bool Coins::CheckCollision(Vector2 playerPosition, float playerRadius) {
    return CheckCollisionCircles(position, radius, playerPosition, playerRadius); 
    //Changed from CheckCollisionCircleRec because we are checking the collision of two circles (player and coins)
}

bool Coins::IsOutOfScreen() {
    return position.y > GetScreenHeight() + radius;
}