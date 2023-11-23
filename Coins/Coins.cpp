#include "Coins.h"

Coins::Coins(Vector2 pos, float r, float (s), Color c)
: position(pos),
  radius (r),
  color (c),
  speed (s){}


Coins::Coins()
    : position({0, 0}),
      radius(0.0f),
      speed(0.0f),
      color(BLANK) {}

void Coins::Draw(){
    DrawCircleV(position, radius, color);
}

void Coins::Update() {
    position.y += speed;
}

bool Coins::CheckCollision(Vector2 playerPosition, float playerRadius) {
    return CheckCollisionCircleRec(playerPosition, playerRadius, {position.x, position.y, radius});
}

bool Coins::IsOutOfScreen() {
    return position.y > GetScreenHeight() + radius;
}