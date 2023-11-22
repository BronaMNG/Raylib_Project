#ifndef Obstacle_H
#define Obstacle_H

#include "raylib.h"

class Obstacle {
public:
    Obstacle(Vector2 pos, Vector2 sz, Color c, float s);
    Obstacle(); 

    void Draw();
    void Update();
    bool CheckCollision(Vector2 playerPosition, float playerRadius);
    bool IsOutOfScreen();

private:
    Vector2 position;
    Vector2 size;
    Color color;
    float speed;
};

#endif