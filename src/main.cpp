#include <raylib.h> 
#include <iostream>
#include <cmath>
#include <string>
#include "levels.cpp"
#include "Ball.h"
#include "Hole.h"
#include "Tile.h"
#include "Arrow.h"

// Get distance between 2 vectors
float getDistance(Vector2 a, Vector2 b)
{
    return sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2));
}

int main() 
{

    const int screenWidth = 480; // Init width
    const int screenHeight = 720; // Init height

    InitWindow(screenWidth, screenHeight, "Golf"); // Set width, height and name
    InitAudioDevice(); // Init audio
    SetWindowState(FLAG_VSYNC_HINT); // Set state of window

    Texture2D background = LoadTexture("../resources/bg.png"); // Init background texture
    Texture2D strokesBg = LoadTexture("../resources/UI_bg.png"); // Init strokes background texture
    Font font = LoadFont("../resources/font.ttf"); // Init font
    Image icon = LoadImage("../resources/icon.ico"); // Init icon
    Sound holeSound = LoadSound("../resources/res_sfx_hole.mp3"); // Init sound of hole
    Sound swingSound = LoadSound("../resources/res_sfx_swing.mp3"); // Init sound of swing
    Sound chargeSound = LoadSound("../resources/res_sfx_charge.mp3"); // Init sound of charge

    SetWindowIcon(icon); // Set icon

    SetTargetFPS(60); // Set FPS

    const char* strokesText = nullptr; // Init strokes text

    int strokes = 0; // Init strokes

    // Create ball object
    Ball ball;
    ball.x = GetScreenWidth() / 2; // Set x location
    ball.y = GetScreenHeight() / 2; // Set y location
    ball.radius = 7; // Set radius
    ball.speedX = 0; // Set speed of x
    ball.speedY = 0; // Set speed of y

    // Create hole object
    Hole hole;
    hole.x = 15+(rand() % (GetScreenWidth() - 15)); // Set random x location
    hole.y = 15+(rand() % (GetScreenHeight() - 15)); // Set random y location
    hole.radius = 10;

    // Create tile object
    Tile tile;
    tile.x = (1+(rand() % 14))*32; // Set random x location
    tile.y = (1+(rand() % 21))*32; // Set random y location

    Vector2 initialPos; // Init pos

    // Main loop (until window is closed)
    while (!WindowShouldClose()) 
    {
        ball.x += ball.speedX * GetFrameTime(); // Set x location from x speed & framerate
        ball.y += ball.speedY * GetFrameTime(); // Set y location from y speed & framerate

        // If ball is above the map
        if (ball.y < 7)
        {
            ball.speedY *= -1; // Reverse speed (make it bounce back)
        }

        // If ball is under the map
        if (ball.y + 7 > GetScreenHeight())
        {
            ball.speedY *= -1; // Reverse speed (make it bounce back)
        }

        // If ball is out of the map (left side)
        if (ball.x < 7)
        {
            ball.speedX *= -1; // Reverse speed (make it bounce back)
        }

        // If ball is out of the map (right side)
        if (ball.x > GetScreenWidth() - 7)
        {
            ball.speedX *= -1; // Reverse speed (make it bounce back)
        }

        // If ball is moving (his speed is not 0)
        if (ball.speedY != 0 || ball.speedY != 0)
        {
            // If ball collides with some object
            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, tile.GetRect()))
            {
                // If absolute y speed is higher than absolute x speed
                if (abs(ball.speedY) > abs(ball.speedX))
                {
                    ball.speedY *= -1; // Reverse y speed
                }
                else // If absolute y speed is lower than absolute x speed
                {
                    ball.speedX *= -1; // Reverse x speed
                }
            }
        }

        // If mouse button is pressed
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // If ball is not moving (x & y speed is 0)
            if (ball.speedX == 0 && ball.speedY == 0)
            {
                initialPos = GetMousePosition(); // Get mouse position and store it
                //arrow.x = ball.x;
                //arrow.y = ball.y;
                //arrow.angle = 10;
                PlaySound(chargeSound); // Play charge sound
            }

        }

        // If mouse button is released
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            // If ball is not moving (x & y speed is 0)
            if (ball.speedX == 0 && ball.speedY == 0)
            {
                Vector2 currPos = GetMousePosition(); // Get current position
                //float dst = getDistance(currPos, initialPos);
                ball.speedX = (currPos.x - initialPos.x)*-2; // Calculate x speed from current x position and x position where the button was firstly pressed, reverse value and multiply it by 2
                ball.speedY = (currPos.y - initialPos.y)*-2; // Calculate y speed from current y position and y position where the button was firstly pressed, reverse value and multiply it by 2

                double Speed2 = sqrt(ball.speedX * ball.speedX + ball.speedY * ball.speedY); // Calculate total speed

                // If that speed is more than 0
                if (Speed2 > 0)
                {
                    PlaySound(swingSound); // Play swing sound
                    strokes++; // Increase strokes value by 1
                }

                
            }
        }

        double Speed = sqrt(ball.speedX * ball.speedX + ball.speedY * ball.speedY); // Get total speed
        //double Angle = atan(ball.speedY / ball.speedX) * (180 / PI);

        // If speed is more than 15
        if (Speed > 15)
        {
            ball.speedX /= 1.015; // Decrease x speed
            ball.speedY /= 1.015; // Decrease y speed
        }
        else // If speed is less than 15
        {
            ball.speedX = 0; // Set the x speed to 0
            ball.speedY = 0; // Set the y speed to 0
        }

        strokesText = "STROKES: 0"; // Show strokes text

        float dst = getDistance(Vector2{ball.x, ball.y}, Vector2{hole.x, hole.y}); // Get distance between hole and the ball
        if (dst < 10) // If distance is less than 10
        {
            //printf("dst: %f        ", dst);
            //printf("Speed: %f\n", Speed);

            // If speed is less than 400
            if (Speed < 400)
            {
                // Ball
                ball.x = GetScreenWidth() / 2; // Set ball x position to the middle of the screen
                ball.y = GetScreenHeight() / 2; // Set ball y position to the middle of the screen
                ball.speedX = 0; // Set ball x speed to 0
                ball.speedY = 0; // Set ball y speed to 0

                // Hole
                hole.x = 15+(rand() % (GetScreenWidth() - 30)); // Set x position of hole to random location
                hole.y = 40+(rand() % (GetScreenHeight() - 65)); // Set y position of hole to random location

                // Tile
                tile.x = (1+(rand() % 14))*32; // Set x position of tile to random location
                tile.y = (1+(rand() % 21))*32; // Set y position of tile to random location

                PlaySound(holeSound); // Play hole sound
            }
            else // If speed is more than 400
            {
                // Make random ball direction (physics)
                ball.speedX = ball.speedX - 15+(rand() % 100); // Set x speed to random value
                ball.speedY = ball.speedY - 15+(rand() % 100); // Set y speed to random value
            }
        }

        char strokesChar[100]; // Init strokes char array
        sprintf(strokesChar,"STROKES: %d",strokes); // Show strokes

        // Draw pictures
        BeginDrawing();

            ClearBackground(BLACK);

            DrawTexture(background, 0, 0, WHITE);

            hole.Draw(); // Draw hole

            //arrow.Draw();

            ball.Draw(); // Draw ball

            tile.Draw(); // Draw tile

            DrawTexture(strokesBg, (GetScreenWidth() / 2)-98, 0, WHITE); // Draw strokes background
        
            // Draw strokes text
            DrawTextEx(font, strokesChar, Vector2{((float) GetScreenWidth() / 2) - (MeasureText(strokesText, font.baseSize*0.9f) / 2), (32 - font.baseSize*0.9f) / 2}, font.baseSize*0.9f, (float)1, WHITE);

            DrawFPS(10, 10); // Draw FPS

        EndDrawing();

    }

    UnloadTexture(background); // Unload textures

    CloseAudioDevice(); // Close audio
    CloseWindow(); // Close window

    return 0;
}