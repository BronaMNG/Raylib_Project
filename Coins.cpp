#include "Coins.h"

Coins::Coins(Vector2 pos, Vector2 sz, float s)
  : position(pos),
      size(sz),
      speed(s) {}

Coins::Coins()
    : position({0, 0}),
      size({0, 0}),
      speed(0.0f) {}

void Coins::Draw(Texture2D snowflakes){
    DrawTextureV(snowflakes, position, WHITE);
}

void Coins::Update() {
    position.y += speed;
}

bool Coins::CheckCollision(Vector2 playerPosition, float playerRadius) {
    Rectangle coinsRect = {position.x, position.y, size.x, size.y};
    return CheckCollisionCircleRec(playerPosition, playerRadius, coinsRect);
    //Changed from CheckCollisionCircleRec because we are checking the collision of two circles (player and coins)
}

bool Coins::IsOutOfScreen() {
    return position.y > GetScreenHeight() + size.y;
}
