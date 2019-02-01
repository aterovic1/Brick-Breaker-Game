#ifndef BALL_H
#define BALL_H

#include "Utils.h"

class Ball {
    int x;
    int y;
    int angle;
public:
    Ball(int x, int y); 
    Ball() : x(0), y(0), angle(4) {}
    int get_x() { return x; } 
    int get_y() { return y; } 
    void set_x(int x) { this -> x = x; }
    void set_y(int y) { this -> y = y; }
    int get_angle() { return angle; }
    void set_angle(int angle) { this -> angle = angle; }
    void calculate_bounce_angle(int border);
    bool is_in_game();
    void hide();
    void move();
    void draw();
};

Ball::Ball(int x, int y) {
    angle = 4;
    this -> x = x;
    this -> y = y;
}

void Ball::draw() {
    display.fillcircle(x, y, ball_r_length, White);    
}

void Ball::hide() {
    display.fillcircle(x, y, ball_r_length, Blue); 
}

bool Ball::is_in_game() {
    return (y < game_border_y_max);
}

void Ball::move() {
    switch(angle) {
        case 1: //22.5
            x += 2; y -= 1;
            break;
        case 2: //45
            x += 1; y -= 1;
            x += 1; y -= 1;
            break;
        case 3: //67.5
            x += 1; y -= 2;
            break;
        case 4: //90
            y -= 1;
            y -= 1;
            y -= 1;
            break;
        case 5: //112.5
            x -= 1; y -= 2;
            break;
        case 6: //135
            x -= 1; y -= 1;
            x -= 1; y -= 1;
            break;
        case 7: //157.5
            x -= 2; y -= 1;
            break;
        case 8: //202.5
            x -= 2; y += 1;
            break;
        case 9: //225
            x -= 1; y += 1;
            x -= 1; y += 1;
            break;
        case 10: //247.5
            x -= 1; y += 2;
            break;
        case 11: //270
            y += 1;
            y += 1;
            y += 1;
            break;
        case 12: //292.5
            x += 1; y += 2;
            break;
        case 13: //315
            x += 1; y += 1;
            x += 1; y += 1;
            break;
        case 14: //337.5
            x += 2; y += 1;
            break;
        default:
            break;
    }
}

void Ball::calculate_bounce_angle(int border) {
    // 1: left border, 2: top border, 3: right border, 4: bottom border
    switch(angle) {
        case 1:
            if(border == 2)
                set_angle(14);
            else if(border == 3)
                set_angle(7);
            break;
        case 2:
            if(border == 2)
                set_angle(13);
            else if(border == 3)
                set_angle(6);
            break;
        case 3:
            if(border == 2)
                set_angle(12);
            else if(border == 3)
                set_angle(5);
            break;
        case 4:
            if(border == 2)
                set_angle(11);
            break;
        case 5:
            if(border == 1)
                set_angle(3);
            else if(border == 2)
                set_angle(10);
            break;
        case 6:
            if(border == 1)
                set_angle(2);
            else if(border == 2)
                set_angle(9);
            break;
        case 7:
            if(border == 1)
                set_angle(1);
            else if(border == 2)
                set_angle(8);
            break;
        case 8:
            if(border == 1)
                set_angle(14);
            else if(border == 4)
                set_angle(7);
            break;
        case 9:
            if(border == 1)
                set_angle(13);
            else if(border == 4)
                set_angle(6);
            break;
        case 10:
            if(border == 1)
                set_angle(12);
            else if(border == 4)
                set_angle(5);
            break;
        case 11:
            if(border == 4)
                set_angle(4);
            break;
        case 12:
            if(border == 3)
                set_angle(10);
            else if(border == 4)
                set_angle(3);
            break;
        case 13:
            if(border == 3)
                set_angle(9);
            else if(border == 4)
                set_angle(2);
            break;
        case 14:
            if(border == 3)
                set_angle(8);
            else if(border == 4)
                set_angle(1);
            break;
    }
}

#endif