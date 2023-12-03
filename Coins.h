#ifndef Coins_h
#define Coins_h

#include "raylib.h"

// Here I am making a coin class combining my knowledge from the Player and Obstacle classes

class Coins{
    private:
    Vector2 position;
    Vector2 size;
    float speed;

    public:
    Coins(Vector2 pos, Vector2 sz, float s);

    Coins();

    void Draw(Texture2D snowflakes);

    void Update();

    bool CheckCollision(Vector2 playerPosition, float playerRadius);

    bool IsOutOfScreen();
};

  

    #endif