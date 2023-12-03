#ifndef Obstacle_H
#define Obstacle_H

#include "raylib.h"

class Obstacle {
private:
    Vector2 position;
    Vector2 size;
    float speed;
    
public:
    Obstacle(Vector2 pos, Vector2 sz, float s);
    Obstacle(); 

    void Draw(Texture2D trees);
    void Update();
    bool CheckCollision(Vector2 playerPosition, Rectangle playerRect);
    bool IsOutOfScreen();


};

#endif