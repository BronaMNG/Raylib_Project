#include "raylib.h"

// I will start by using lecture 6 for reference

#include "Player.h"
#include "Obstacle.h"
#include "Coins.h"

const int MAX_OBSTACLES = 10;
const int MAX_COINS = 5;

int main() {

    // Determin the Game Window Width and Height
    const int screenWidth = 800;
    const int screenHeight = 450;

    // Initialize the Window
    InitWindow(screenWidth, screenHeight, "Watch Out!");

    Player player({screenWidth/2, screenHeight-50}, 20, RAYWHITE);

    Obstacle obstacles[MAX_OBSTACLES];

    for(int i = 0; i<MAX_OBSTACLES; ++i){
        float width = GetRandomValue(50,200);
        obstacles[i] = Obstacle({(float)GetRandomValue(0, screenWidth-(int)width), (float)(-20.0f-i*60)}, {width, 20.0f}, RED, 4.0f);
    }
    
    Coins coins[MAX_COINS];

     for(int i = 0; i<MAX_COINS; ++i){
        coins[i] = Coins({(float)GetRandomValue(0 , screenWidth-10.0f), (float)(-10.0f-i*60)}, {10.0f}, YELLOW, 0.5f);
    }



    // Setting the Frames Per Second
    SetTargetFPS(60);

    int score = 0;
    bool gameOver = false;
    bool pause = false;


    // The Game Loop
    while (!WindowShouldClose() /*WindowShouldClose returns true if esc is clicked and closes the window*/)
     { 
        if(!gameOver)

         if (IsKeyPressed(KEY_P)) pause = !pause;

        if (!pause)

        {
            if(IsKeyDown(KEY_D)&& player.GetPosition().x< screenWidth-player.GetRadius())
            player.Move ({5, 0});

            if(IsKeyDown(KEY_A)&& player.GetPosition().x< screenWidth-player.GetRadius())
            player.Move ({-5, 0});
        }


        for (int i = 0; i< MAX_OBSTACLES; ++i){
            if(obstacles[i].IsOutOfScreen()){
                float width = GetRandomValue(50, 200);
                obstacles[i] = Obstacle({(float)GetRandomValue(0, screenWidth - (int)width), -20.0f}, {width, 20.0f}, RED, 4.0f);
            }
            obstacles[i].Update();

            
        for (int i = 0; i< MAX_COINS; ++i){
            if(coins[i].IsOutOfScreen()){
                 coins[i] = Coins({(float)GetRandomValue(0 , screenWidth-10.0f), (float)(-10.0f-i*60)}, {10.0f}, YELLOW, 0.5f);
                }
           coins[i].Update();
            
            }
            
            
            if(obstacles[i].CheckCollision(player.GetPosition(), player.GetRadius())){
                
                gameOver= true;
            }

            score++;
        }



        // Setup Canvas
        BeginDrawing();

        player.Draw();

    for(int i = 0; i<MAX_OBSTACLES; ++i){
       obstacles[i].Draw();
    }
    
    for(int i = 0; i<MAX_COINS; ++i){
       coins[i].Draw();
    }


    DrawText(TextFormat("Score: %i", score), 10, 10, 20, LIGHTGRAY);

    if (pause) DrawText("GAME PAUSED", screenWidth/2 - MeasureText("GAME PAUSED", 40)/2, screenHeight/2 - 40, 40, GRAY);

    if(gameOver){
        DrawText("GAME OVER", screenWidth/2 -60, screenHeight/2, 20, RED);
    }
        // Clear canvas to a specific color to avoid flicker
        ClearBackground(BLACK);

        // Here goes all the Game Logic

        // teardown Canvas
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
