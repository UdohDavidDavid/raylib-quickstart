/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "constants.hpp"
#include "snake.hpp"
#include "apple.hpp"



int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(Constants.WINDOW_WIDTH, Constants.WINDOW_HEIGHT, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

    Snake snake;
    Apple apple;


    // game loop
    while (!WindowShouldClose()) // run the loop until the user presses ESCAPE
                                 // or presses the Close button on the window
    {
        SetTargetFPS(snake.speed);
        // drawing
        BeginDrawing();

        // Setup the back buffer for drawing (clear color and depth buffers)
        ClearBackground(BLACK);


        if (IsKeyDown(KEY_D) && snake.direction != Direction::LEFT)
            snake.direction = Direction::RIGHT;
        else if (IsKeyDown(KEY_A) && snake.direction != Direction::RIGHT)
            snake.direction = Direction::LEFT;
        else if (IsKeyDown(KEY_W) && snake.direction != Direction::DOWN)
            snake.direction = Direction::UP;
        else if (IsKeyDown(KEY_S) && snake.direction != Direction::UP)
            snake.direction = Direction::DOWN;

        for (int i = 1; i < Constants.ROW_NUM; ++i) {
            DrawLine(0, Constants.cell_height * i, Constants.WINDOW_WIDTH,
                   Constants.cell_height * i, BLACK);
          for (int j = 1; j < Constants.COL_NUM; ++j) {
            DrawLine(Constants.cell_width * j, 0, Constants.cell_width * j,
                     Constants.WINDOW_HEIGHT, BLACK);
          }
        }

        for (int i = 0; i < snake.Bodies.size(); ++i) {
            DrawRectangleRec({snake.Bodies[i].posX, snake.Bodies[i].posY,
                          (float)Constants.cell_width,
                          (float)Constants.cell_height},
                         RED);
        }

        if (!snake.collided) snake.update(GetFrameTime());

        DrawRectangleRec({(float)apple.x, (float)apple.y, (float)Constants.cell_width, (float)Constants.cell_height}, GREEN);

        if (CheckCollisionRecs(snake.head_rect, apple.apple_rect)) {
            apple.respawn();
            snake.apples++;
            snake.grow = true;
            snake.speed_check++;
        }
        else {
            snake.grow = false;
        }

        for (int i = 1; i < snake.Bodies.size(); ++i) {
            Rectangle snake_body_rect = {(float)snake.Bodies[i].posX, (float)snake.Bodies[i].posY, (float)Constants.cell_width, (float)Constants.cell_height};
            if (CheckCollisionRecs(apple.apple_rect, snake_body_rect)) apple.respawn();
        }
        
        // if (snake.body.posY > Constants)


        // end the frame and get ready for the next one  (display frame, poll
        // input, etc...)
        EndDrawing();
    }

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
