#ifndef PADDLE_H
#define PADDLE_H

#include "Utils.h"

class Paddle {
    int x;
    int y;
    int length;
public:
    Paddle() : x(paddle_start_x), y(paddle_start_y), length(paddle_x_length) {}
    Paddle(int x, int y);
    void move_left();
    void move_right();
    void draw();
    int get_x() { return x; } 
    int get_y() { return y; } 
    int get_length() { return length; }
    void expand();
    void shrink();
    bool is_in_game_right();
    bool is_in_game_left();
    void hide();
};

void Paddle::hide() {
    display.fillrect(x, y, x + length, y + paddle_y_length, Blue);
}

Paddle::Paddle(int x, int y) {
    length = paddle_x_length;
    this -> x = x;
    this -> y = y;
}

void Paddle::draw() {
    display.fillrect(x, y, x + length, y + paddle_y_length, White);
}

void Paddle::move_left() {
    x -= 1;
}

void Paddle::move_right() {
    x += 1;
}

void Paddle::expand() {
    x -= 10;
    length += 20;
}

void Paddle::shrink() {
    x += 10;
    length -= 20;
}

bool Paddle::is_in_game_right() {
    return ((x - 2) + length <= game_border_x_max);
}

bool Paddle::is_in_game_left() {
    return ((x + 2) >= game_border_x_min);
}

#endif