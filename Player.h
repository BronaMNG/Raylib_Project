#ifndef Player_H
#define Player_H

#include "raylib.h"

class Player{
    private:
    Vector2 position;
    float radius;
    Color color;

    public:
    Player(Vector2 pos, float r, Color c);

    void Draw();

    void Move(Vector2);

    float GetRadius()const;
    
    Vector2 GetPosition() const;
    };

    #endif