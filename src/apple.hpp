#ifndef APPLE_H
#define APPLE_H

#include "constants.hpp"
#include <random>
#include "raylib.h"

class Apple {
public:
    int x = Constants.ROW_NUM / 2 * Constants.cell_width;
    int y = Constants.COL_NUM / 2 * Constants.cell_height;
    Rectangle apple_rect = {(float)x, (float)y, (float)Constants.cell_width,
                            (float)Constants.cell_height};

    void respawn() {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> random_x(1, Constants.ROW_NUM - 1);
        std::uniform_int_distribution<std::mt19937::result_type> random_y(1, Constants.COL_NUM - 1);
        x = random_x(rng) * Constants.cell_width;
        y = random_y(rng) * Constants.cell_height;
        apple_rect.x = x;
        apple_rect.y = y;
    }

    void draw() {
        DrawRectangleRec({(float)x, (float)y, (float)Constants.cell_width, (float)Constants.cell_height}, GREEN);
    }
};

#endif