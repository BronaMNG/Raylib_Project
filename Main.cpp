#include "raylib.h"

#include "Player.h"
#include "Obstacle.h"
#include "Coins.h"

//For base logic (player, obstacles and collisions) lecture 6 was referenced
//for pause functionality, Raylib example arkanoid was referenced https://github.com/raysan5/raylib-games/blob/master/classics/src/arkanoid.c
//for lives, Raylib example arkanoid was referenced https://github.com/raysan5/raylib-games/blob/master/classics/src/arkanoid.c
//for screen switches, Raylib example was referenced https://www.raylib.com/examples.html
//for sound implementation, Raylib example was referenced https://www.raylib.com/examples.html

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen { TITLE, GAMEPLAY, ENDING } GameScreen;

//Defining amounts for arrays
const int MAX_OBSTACLES = 5;
const int MAX_COINS = 5;
int MAX_LIVES = 3;
float TREE_HEIGHT = 190;
float TREE_WIDTH = 104;
float SNOWFLAKE_HEIGHT = 25;
float SNOWFLAKE_WIDTH = 25;
int score = 0;

//Defining bools
bool gameOver = false;
bool pause = false;


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

  //Loading audio
  Music music = LoadMusicStream("resources/BGMusic.wav");
  Sound chime = LoadSound("resources/chime.wav"); 
  Sound snow = LoadSound("resources/SnowCrunch.wav");

  //Loading Textures
  Texture2D lives = LoadTexture("resources/Heart.png");
  Texture2D bg = LoadTexture("resources/BG.png");
  Texture2D trees = LoadTexture("resources/Big Tree.png");
  Texture2D snowflakes = LoadTexture("resources/Snowflake.png");
  Texture2D skiier = LoadTexture("resources/Player.png");

  //initialising game screen
  GameScreen currentScreen = TITLE;

  //initialising player
  Player player({screenWidth/2, screenHeight-50}, 45, WHITE);

  //initialising lives  
  for (int i = 0; i < MAX_LIVES; i++) 
  DrawTexture( lives, 20 + 40*i, screenHeight - 40, WHITE);

  //initialising obstacles
  Obstacle obstacles[MAX_OBSTACLES];
  
  for(int i = 0; i<MAX_OBSTACLES; ++i){
    float x = (float)GetRandomValue(0, screenWidth-(int)TREE_WIDTH);
    float y = (float)(-TREE_HEIGHT-i*60);
    obstacles[i] = Obstacle({x, y}, {TREE_WIDTH, TREE_HEIGHT}, 4.0f);
    }

  //initialising coins
  Coins coins[MAX_COINS];
  
  for(int i = 0; i<MAX_COINS; ++i){
    float x = (float)GetRandomValue(0, screenWidth-(int)TREE_WIDTH);
    float y = (float)(-SNOWFLAKE_HEIGHT-i*60);
    coins[i] = Coins({x, y}, {SNOWFLAKE_WIDTH, SNOWFLAKE_HEIGHT}, 2.0f);
    }

    SetTargetFPS(60);  //setting target fps

       //--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateMusicStream(music);

    //setting music volume so it doesn't drown out sound fx
    SetMusicVolume(music, 0.2f); 

    switch(currentScreen)
    {
        case TITLE:
        {   //here I am resetting game components so the game loops effectively
            gameOver = false;
            score = 0;
            MAX_LIVES = 3;

            for (int i = 0; i< MAX_OBSTACLES; ++i){
                float x = (float)GetRandomValue(0, screenWidth-(int)TREE_WIDTH);
                float y = (float)(-TREE_HEIGHT-i*60);
                obstacles[i] = Obstacle({x, y}, {TREE_WIDTH, TREE_HEIGHT}, 4.0f);
                }

            for (int i = 0; i< MAX_COINS; ++i){
                float x = (float)GetRandomValue(0, screenWidth-(int)TREE_WIDTH);
                float y = (float)(-SNOWFLAKE_HEIGHT-i*60);
                coins[i] = Coins({x, y}, {SNOWFLAKE_WIDTH, SNOWFLAKE_HEIGHT}, 2.0f);
                }
                
            // Press enter to change to GAMEPLAY screen
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsGestureDetected(GESTURE_TAP))
            {
                currentScreen = GAMEPLAY;
            }
            } break;

        case GAMEPLAY:
        {
            if(!gameOver)
            {          
                // pause functionality
                if (IsKeyPressed(KEY_SPACE))
                pause = !pause;
                    
                if (!pause)
                {
                    //player movement logic
                    if(IsKeyDown(KEY_D)&& player.GetPosition().x< screenWidth-player.GetSize())
                    player.Move ({5, 0});

                    if(IsKeyDown(KEY_A)&& player.GetPosition().x> player.GetSize())
                    player.Move ({-5, 0});

                    //player movement audio fx
                    if(IsKeyPressed(KEY_D))
                    PlaySound(snow);

                    if(IsKeyPressed(KEY_A))
                    PlaySound(snow);
                        
                        
                    for (int i = 0; i< MAX_OBSTACLES; ++i){
                    if(obstacles[i].IsOutOfScreen())
                    {
                        float x = (float)GetRandomValue(0, screenWidth-(int)TREE_WIDTH);
                        float y = (float)(-TREE_HEIGHT-i*60);
                        obstacles[i] = Obstacle({x, y}, {TREE_WIDTH, TREE_HEIGHT}, 4.0f);
                    }
                            
                    obstacles[i].Update();

                    if(obstacles[i].CheckCollision(player.GetPosition(), player.GetRect()))
                    {
                        float x = (float)GetRandomValue(0, screenWidth-(int)TREE_WIDTH);
                        float y = (float)(-TREE_HEIGHT-i*60);
                        obstacles[i] = Obstacle({x, y}, {TREE_WIDTH, TREE_HEIGHT}, 4.0f);

                        MAX_LIVES --;
                             
                    }
                             
        }
        
        for (int i = 0; i< MAX_COINS; ++i)
        {
            if(coins[i].IsOutOfScreen())
            {
                float x = (float)GetRandomValue(0, screenWidth-(int)TREE_WIDTH);
                float y = (float)(-SNOWFLAKE_HEIGHT-i*60);
                coins[i] = Coins({x, y}, {SNOWFLAKE_WIDTH, SNOWFLAKE_HEIGHT}, 2.0f);
            }

            if (coins[i].CheckCollision(player.GetPosition(), player.GetRect()))
            {
                                    
                float x = (float)GetRandomValue(0, screenWidth-(int)TREE_WIDTH);
                float y = (float)(-SNOWFLAKE_HEIGHT-i*60);
                coins[i] = Coins({x, y}, {SNOWFLAKE_WIDTH, SNOWFLAKE_HEIGHT}, 2.0f);
                            
                score++;

                PlaySound(chime);
                                    
            } 
                            
                coins[i].Update();
                            
        }
                            
                        
                if(MAX_LIVES == 0)
                {
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

            ClearBackground(RAYWHITE); //clear background to avoid flicker

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
                    //drawing background
                    DrawTexture(bg, 0, 0, WHITE);

                    //drawing player
                    player.Draw(skiier);

                    //drawing lives
                    for (int i = 0; i < MAX_LIVES; i++)
                    {
                        DrawTexture( lives, 20 + 40*i, screenHeight - 40, WHITE);
                    }

                    //drawing obstacles    
                    for(int i = 0; i<MAX_OBSTACLES; ++i)
                    {
                        obstacles[i].Draw(trees);
                    }

                    //drawing coins    
                    for(int i = 0; i<MAX_COINS; ++i)
                    {
                        coins[i].Draw(snowflakes);
                    }

                    //drawing snowflake beside score counter
                    DrawTexture(snowflakes, 10, 10, WHITE);
                    DrawText(TextFormat(": %i", score), 60, 20, 20, DARKGRAY);
                    
                    //drawing pause text
                    if (pause) DrawText("GAME PAUSED", screenWidth/2 - MeasureText("GAME PAUSED", 40)/2, screenHeight/2 - 40, 40, GRAY);

                  

                } break;

                case ENDING:
                {
                    //drawing text
                    DrawText("GAME OVER", screenWidth/2 -60, screenHeight/2, 20, BLUE);
                    DrawText("PRESS ENTER to PLAY AGAIN", 310, 260, 12, DARKGRAY);

                } break;

                default: break;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    //unloading audio
    UnloadMusicStream(music);
    UnloadSound(chime);
    UnloadSound(snow);

    //unloading textures
    UnloadTexture(lives); 
    UnloadTexture(trees);    
    UnloadTexture(bg);
    UnloadTexture(snowflakes);
    UnloadTexture(skiier);

    CloseAudioDevice(); 

    CloseWindow();     
    //--------------------------------------------------------------------------------------

    return 0;
}