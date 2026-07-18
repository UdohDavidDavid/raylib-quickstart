#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define BACKGROUND WHITE

class Constants {
public:

    int WINDOW_WIDTH  = 600;
    int WINDOW_HEIGHT = 600;

    int ROW_NUM = 30;
    int COL_NUM = 30;

    int cell_height = WINDOW_HEIGHT / ROW_NUM;
    int cell_width  = WINDOW_WIDTH / COL_NUM;

    const char* title = "Snake Game";

};

inline Constants Constants;

#endif