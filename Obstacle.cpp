#include "Obstacle.h"

Obstacle::Obstacle(Vector2 pos, Vector2 sz, float s)
    : position(pos),
      size(sz),
      speed(s) {}

Obstacle::Obstacle()
    : position({0, 0}),
      size({0, 0}),
      speed(0.0f) {}

void Obstacle::Draw(Texture2D trees) {
    DrawTextureV(trees, position, WHITE);
}
void Obstacle::Update() {
    position.y += speed;
}

bool Obstacle::CheckCollision(Vector2 playerPosition, float playerRadius) {
    Rectangle obstacleRect = {position.x, position.y, size.x, size.y};
    return CheckCollisionCircleRec(playerPosition, playerRadius, obstacleRect);
}

bool Obstacle::IsOutOfScreen() {
    return position.y > GetScreenHeight() + size.y;
}