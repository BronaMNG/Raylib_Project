#ifndef Player_H
#define Player_H

#include "raylib.h"

class Player{
    private:
    Vector2 position;
    float size;
    Color color;

    public:
    Player(Vector2 pos, float sz, Color c);

    void Draw(Texture2D skiier);

    void Move(Vector2);

    Rectangle GetRect() const;

    float GetSize() const;
    
    Vector2 GetPosition() const;
    };

    #endif