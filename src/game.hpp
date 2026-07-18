#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "constants.hpp"
#include "snake.hpp"
#include "apple.hpp"

class Game {
public:
    Snake snake;
    Apple apple;
    bool drawGrid = false;

    Game() {
      // Tell the window to use vsync and work on high DPI displays
      SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

      // Create the window and OpenGL context
      InitWindow(Constants.WINDOW_WIDTH, Constants.WINDOW_HEIGHT,
                 Constants.title);

      // Utility function from resource_dir.h to find the resources folder and
      // set it as the current working directory so we can load from it
      SearchAndSetResourceDir("resources");

    }

    ~Game() {
        // destroy the window and cleanup the OpenGL context
        CloseWindow();
    }

    void run() {
        // game loop
        while (!WindowShouldClose()) {
            SetTargetFPS(snake.speed);
            // drawing
            BeginDrawing();
            ClearBackground(BLACK);

            process_keyboard();
            if (drawGrid) draw_grid();
            snake.draw();
            snake.show_apple_count();
            if (!snake.collided) {
                snake.update(GetFrameTime());
            }
            else {
                print_game_over("Game Over", 67);
            }
            apple.draw();
            check_apple();

            EndDrawing();
        }
    }
private:
    void process_keyboard() {
        if (IsKeyDown(KEY_D) && snake.direction != Direction::LEFT)
            snake.direction = Direction::RIGHT;
        else if (IsKeyDown(KEY_A) && snake.direction != Direction::RIGHT)
            snake.direction = Direction::LEFT;
        else if (IsKeyDown(KEY_W) && snake.direction != Direction::DOWN)
            snake.direction = Direction::UP;
        else if (IsKeyDown(KEY_S) && snake.direction != Direction::UP)
            snake.direction = Direction::DOWN;
    }

    void draw_grid() {
        for (int i = 1; i < Constants.ROW_NUM; ++i) {
            DrawLine(0, Constants.cell_height * i, Constants.WINDOW_WIDTH,
                   Constants.cell_height * i, BLACK);
          for (int j = 1; j < Constants.COL_NUM; ++j) {
            DrawLine(Constants.cell_width * j, 0, Constants.cell_width * j,
                     Constants.WINDOW_HEIGHT, BLACK);
          }
        }
    }

    void check_apple() {
        for (int i = 1; i < snake.Bodies.size(); ++i) {
            Rectangle snake_body_rect = {
                (float)snake.Bodies[i].posX, (float)snake.Bodies[i].posY,
                (float)Constants.cell_width, (float)Constants.cell_height};

            if (CheckCollisionRecs(apple.apple_rect, snake_body_rect))
                apple.respawn();
        }
        if (CheckCollisionRecs(snake.head_rect, apple.apple_rect)) {
            apple.respawn();
            snake.apples++;
            snake.grow = true;
            snake.speed_check++;
        }
        else {
            snake.grow = false;
        }
    }

    void print_game_over(const char* text, int fontsize) {
        int txtlen = MeasureText(text, fontsize);
        DrawText(text, Constants.WINDOW_WIDTH / 2 - txtlen / 2,
                 Constants.WINDOW_HEIGHT / 2 - GetFontDefault().baseSize,
                 fontsize, WHITE);
    }
};

#endif