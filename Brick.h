#ifndef BRICK_H
#define BRICK_H

#include "Utils.h"

class Brick {
    int x;
    int y;
    bool destroyed;
    int colour;
public:
    Brick(int x, int y, int colour);
    Brick() : x(0), y(0), destroyed(false), colour(LightGrey) {}
    int get_x() { return x; } 
    int get_y() { return y; }
    int get_colour() { return colour; }
    void destroy();
    bool is_destroyed() { return destroyed; }
    bool is_destroyable();
    void draw();
};

Brick::Brick(int x, int y, int colour) {
    destroyed = false;
    this -> colour = colour;
    this -> x = x;
    this -> y = y;
}    

void Brick::destroy() {
    destroyed = true;
}    

bool Brick::is_destroyable() {
    return colour != LightGrey;
}

void Brick::draw() {
    display.fillrect(x, y, x + brick_x_length, y + brick_y_length, colour);
}

#endif