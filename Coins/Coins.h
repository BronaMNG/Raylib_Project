#ifndef Coins_h
#define Coins_h

#include "raylib.h"

// Here I am making a coin class combining my knowledge from the Player and Obstacle classes

class Coins{
    private:
    Vector2 position;
    float radius;
    float speed;
    Color color;

    public:
   Coins(Vector2 pos, float r, Color c);

    void Draw();

    void Update(Vector2);

    bool CheckCollision(Vector2 playerPosition, float playerRadius);

    bool IsOutOfScreen();

    #endif