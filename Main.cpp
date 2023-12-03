#include "raylib.h"

#include "Player.h"
#include "Obstacle.h"
#include "Coins.h"

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen { TITLE, GAMEPLAY, ENDING } GameScreen;
const int MAX_OBSTACLES = 5;
const int MAX_COINS = 5;
int MAX_LIVES = 3;
float TREE_HEIGHT = 190;
    float TREE_WIDTH = 104;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Slippery Slopes!");

    InitAudioDevice();

    Music music = LoadMusicStream("resources/BGMusic.wav");  

    Texture2D lives = LoadTexture("resources/Heart.png");
    Texture2D trees = LoadTexture("resources/Big Tree.png");
    Texture2D bg = LoadTexture("resources/BG.png");               

    GameScreen currentScreen = TITLE;

    Player player({screenWidth/2, screenHeight-50}, 20, BLUE);
    
    for (int i = 0; i < MAX_LIVES; i++) 
    DrawTexture( lives, 20 + 40*i, screenHeight - 40, WHITE);

    Obstacle obstacles[MAX_OBSTACLES];

    for(int i = 0; i<MAX_OBSTACLES; ++i){
        float x = (float)GetRandomValue(0, screenWidth-(int)TREE_WIDTH);
        float y = (float)(-TREE_HEIGHT-i*60);
        obstacles[i] = Obstacle({x, y}, {TREE_WIDTH, TREE_HEIGHT}, 4.0f);
    }
   
    Coins coins[MAX_COINS];
    
    for(int i = 0; i<MAX_COINS; ++i){
         coins[i] = Coins({(float)GetRandomValue(0 , screenWidth-10.0f), (float)(-10.0f-i*60)}, {10.0f}, YELLOW, 2.0f);
    }

    SetTargetFPS(60);               
    int score = 0;
    bool gameOver = false;
    bool pause = false;
       //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(music);

        switch(currentScreen)
        {
            case TITLE:
            {
                gameOver = false;
                score = 0;
                MAX_LIVES = 3;

                for (int i = 0; i< MAX_OBSTACLES; ++i){
                    float x = (float)GetRandomValue(0, screenWidth-(int)TREE_WIDTH);
                    float y = (float)(-TREE_HEIGHT-i*60);
                    obstacles[i] = Obstacle({x, y}, {TREE_WIDTH, TREE_HEIGHT}, 4.0f);
                }

                for (int i = 0; i< MAX_COINS; ++i){
                    coins[i] = Coins({(float)GetRandomValue(0 , screenWidth-10.0f), (float)(-10.0f-i*60)}, {10.0f}, YELLOW, 2.0f);
                }
                
                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = GAMEPLAY;
                }
            } break;

            case GAMEPLAY:
            {
                if(!gameOver){
                        
                    // pause functionality
                    if (IsKeyPressed(KEY_SPACE))
                    pause = !pause;
                    
                    if (!pause){
                        //player movement logic
                        if(IsKeyDown(KEY_D)&& player.GetPosition().x< screenWidth-player.GetRadius())
                        player.Move ({5, 0});
                        
                        if(IsKeyDown(KEY_A)&& player.GetPosition().x> player.GetRadius())
                        player.Move ({-5, 0});
                        
                        
                        for (int i = 0; i< MAX_OBSTACLES; ++i){
                             if(obstacles[i].IsOutOfScreen()){
                               float x = (float)GetRandomValue(0, screenWidth-(int)TREE_WIDTH);
                               float y = (float)(-TREE_HEIGHT-i*60);
                               obstacles[i] = Obstacle({x, y}, {TREE_WIDTH, TREE_HEIGHT}, 4.0f);
                                }
                            
                            obstacles[i].Update();

                             if(obstacles[i].CheckCollision(player.GetPosition(), player.GetRadius())){
                                float x = (float)GetRandomValue(0, screenWidth-(int)TREE_WIDTH);
                                float y = (float)(-TREE_HEIGHT-i*60);
                                obstacles[i] = Obstacle({x, y}, {TREE_WIDTH, TREE_HEIGHT}, 4.0f);
                                MAX_LIVES --;
                             
                             }
                             
                            }

                        for (int i = 0; i< MAX_COINS; ++i){
                            
                            if(coins[i].IsOutOfScreen()){
                                coins[i] = Coins({(float)GetRandomValue(0 , screenWidth-10.0f), (float)(-10.0f-i*60)}, {10.0f}, YELLOW, 2.0f);
                                }

                                if (coins[i].CheckCollision(player.GetPosition(), player.GetRadius())){
                                    
                                coins[i] = Coins({(float)GetRandomValue(0 , screenWidth-10.0f), (float)(-10.0f-i*60)}, {10.0f}, YELLOW, 2.0f);
                                    
                                score++;
                                    
                                 } 
                            
                            coins[i].Update();
                            
                            }
                            
                        
                             if(MAX_LIVES == 0){
                                gameOver = true;

                                }
                    }
                    
                }

                if (gameOver)
                {
                    currentScreen = ENDING;
                }
                
            } break;

            case ENDING:
            {
                if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = TITLE;
                }
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            PlayMusicStream(music);

            switch(currentScreen)
            {
                case TITLE:
                {
                    DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
                    DrawText("SLIPPERY SLOPES!", 200, 160, 40, BLUE);
                    DrawText("PRESS ENTER to PLAY", 270, 220, 20, LIGHTGRAY);

                } break;

                case GAMEPLAY:
                {
                    DrawTexture(bg, 0, 0, WHITE);

                     player.Draw();
                     for (int i = 0; i < MAX_LIVES; i++){
                        DrawTexture( lives, 20 + 40*i, screenHeight - 40, WHITE);
                        }
                        
                    for(int i = 0; i<MAX_OBSTACLES; ++i){
                        obstacles[i].Draw(trees);
                        }
                        
                    for(int i = 0; i<MAX_COINS; ++i){
                        coins[i].Draw();
                        }
                        
                        DrawText(TextFormat("Score: %i", score), 10, 10, 20, LIGHTGRAY);
                        if (pause) DrawText("GAME PAUSED", screenWidth/2 - MeasureText("GAME PAUSED", 40)/2, screenHeight/2 - 40, 40, GRAY);

                  

                } break;

                case ENDING:
                {
                    DrawText("GAME OVER", screenWidth/2 -60, screenHeight/2, 20, BLUE);
                    DrawText("PRESS ENTER to PLAY AGAIN", 310, 260, 12, LIGHTGRAY);

                } break;

                default: break;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadMusicStream(music);

    UnloadTexture(lives); 
    UnloadTexture(trees);    
    UnloadTexture(bg);

    CloseAudioDevice(); 

    CloseWindow();     
    //--------------------------------------------------------------------------------------

    return 0;
}