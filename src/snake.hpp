#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "constants.hpp"
#include <vector>
#include "raylib.h"
#include <string>

struct Body {
    float posX = (float)Constants.ROW_NUM / 2 * Constants.cell_width;
    float posY = (float)Constants.ROW_NUM / 2 * Constants.cell_height;
};

enum class Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

class Snake {
public:
    bool collided = false;
    bool grow = false;
    int apples = 0;

    int speed_check = 0;

    int size = 4;

    int speed = 6;
    Body body;
    std::vector<Body> Bodies;
    Direction direction = Direction::RIGHT;

    Rectangle head_rect;
    Rectangle current_body_rect;

    Snake() {
        for (int i = 0; i < size; ++i) {
            Bodies.push_back(body);
            Bodies[i].posX -= Constants.cell_width * (i + 1);
        }
        head_rect = {(float)Bodies[0].posX, (float)Bodies[0].posY,
                           (float)Constants.cell_width,
                           (float)Constants.cell_height};
    }

    void update(float deltatime) {
        process_speed();
        process_direction();
        process_collision();
        process_borders();
    }

    void draw() {
        for (int i = 0; i < Bodies.size(); ++i) {
            DrawRectangleRec({Bodies[i].posX, Bodies[i].posY,
                          (float)Constants.cell_width,
                          (float)Constants.cell_height},
                         RED);
        }
    }

    void show_apple_count() {
        // std::string text = "Score" + std::to_string(apple);
        std::string i("Score: ");
        i.append(std::to_string(apples));
        DrawText(i.c_str(), 0, 0, 5, WHITE);
    }

private:
    void process_collision() {
        for (int i = 1; i < Bodies.size(); ++i) {
            current_body_rect = {(float)Bodies[i].posX, (float)Bodies[i].posY, (float)Constants.cell_width, (float)Constants.cell_height};
            if (CheckCollisionRecs(head_rect, current_body_rect)) collided = true;
        }
    }

    void process_borders() {
        if (body.posX > Constants.WINDOW_WIDTH - Constants.cell_width && direction == Direction::RIGHT) {
            Bodies[0].posX = 0;
            body.posX = 0;
        }
        if (body.posX < 0 && direction == Direction::LEFT) {
            Bodies[0].posX = Constants.WINDOW_WIDTH - Constants.cell_width;
            body.posX = Constants.WINDOW_WIDTH - Constants.cell_width;
        }
        if (body.posY < 0 && direction == Direction::UP) {
            Bodies[0].posY = Constants.WINDOW_HEIGHT - Constants.cell_height;
            body.posY = Constants.WINDOW_HEIGHT - Constants.cell_height;
        }
        if (body.posY > Constants.WINDOW_HEIGHT - Constants.cell_width && direction == Direction::DOWN) {
            Bodies[0].posY = 0;
            body.posY = 0;
        }
    }

    void process_speed() {
        if (speed_check == 5) {
            speed += 1;
            speed_check = 0;
        }
    }

    void process_direction() {

        if (!grow) Bodies.pop_back();

        if (direction == Direction::RIGHT) {
            body.posX += Constants.cell_width;
            Bodies.insert(Bodies.begin(), body);
        }
        else if (direction == Direction::LEFT) {
            body.posX -= Constants.cell_width;
            Bodies.insert(Bodies.begin(), body);
        }
        else if (direction == Direction::UP) {
            body.posY -= Constants.cell_height;
            Bodies.insert(Bodies.begin(), body);
        }
        else if (direction == Direction::DOWN) {
            body.posY += Constants.cell_height;
            Bodies.insert(Bodies.begin(), body);
        }
        head_rect.x = Bodies[0].posX;
        head_rect.y = Bodies[0].posY;
    }
};

#endif