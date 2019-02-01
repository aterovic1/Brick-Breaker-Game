#ifndef BRICKBREAKER_H
#define BRICKBREAKER_H

#include "Utils.h"
#include "Brick.h"
#include "Ball.h"
#include "Paddle.h"

class BrickBreaker {
    Timer game_time;
    int brick_count;
    int destroyed_bricks_count;
    int lives;
    AnalogIn start_stop;
public:
    Paddle paddle;
    Ball ball;
    Brick* bricks;
    bool lost;
    bool paused;

    BrickBreaker(int level);
    ~BrickBreaker();
    void start();
    void stop();
    double get_time() {return game_time.read(); }
    int get_lives() { return lives; }
    void add_life();
    void take_life();
    void show_win_message();
    void show_lose_message();
    bool is_lost() { return lost; }
};

BrickBreaker::BrickBreaker(int level) : start_stop(dp10) {
    display.background(Blue);
    display.cls();
    lives = 3;
    lost = false;
    paused = false;
    //draw header
    display.line(0, 10, 320, 10, White);
    display.locate(lives_no_x, lives_no_y);
    display.set_font((unsigned char*) Arial12x12);
    char lives_char[5];
    sprintf(lives_char, "%d", lives);
    printf(lives_char);
    //drawing paddle, ball and bricks
    paddle = Paddle(paddle_start_x, paddle_start_y);
    ball = Ball(ball_start_x, ball_start_y);
    destroyed_bricks_count = 0;
    if(level == 1) {
        brick_count = 40;
        bricks = new Brick[brick_count];
        //for level1
        int colours[5] = {Red, Orange, Yellow, DarkCyan, Green};
        int x = 30, y = 30 + game_border_y_min, space = 3, ind = 0;
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 8; j++) {
                bricks[ind++] = Brick(x, y, colours[i]);
                x += space + brick_x_length;
            }
            y += space + brick_y_length;
            x = 30;
        }
    }
    //add grey non-destroyble bricks for level2
    else if(level == 2) {
        brick_count = 44;   
        bricks = new Brick[brick_count];
        int colours[5] = {Purple, Orange, Yellow, DarkCyan, DarkGreen};
        int x = 30, y = 30 + game_border_y_min, space = 3, ind = 0;
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 8; j++) {
                bricks[ind++] = Brick(x, y, colours[i]);
                x += space + brick_x_length;
            }
            y += space + brick_y_length;
            x = 30;
        }
        y += (4 * space + brick_y_length);
        //4 grey bricks on left and right side
        bricks[ind++] = Brick(x, y, LightGrey);
        x += space + brick_x_length;
        bricks[ind++] = Brick(x, y, LightGrey);
        x += 5 * (space + brick_x_length);
        bricks[ind++] = Brick(x, y, LightGrey);
        x += space + brick_x_length;
        bricks[ind++] = Brick(x, y, LightGrey);
    }
    //level 3
    else {
        brick_count = 40;   
        bricks = new Brick[brick_count];
        int colours[2] = {Magenta, GreenYellow};
        int x = 10, y = 20 + game_border_y_min, x_space = 37, y_space = 3, ind = 0, col_ind = 0;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 5; j++) {
                if(j % 2 == 0)
                    col_ind = 0;
                else
                    col_ind = 1;
                bricks[ind++] = Brick(x, y, colours[col_ind]);
                x += x_space + brick_x_length;
            }
            y += y_space + brick_y_length;
            x = 10;
        }
    }
}

void BrickBreaker::stop() {
    game_time.stop();
    paused = true;
    while(paused);
}

BrickBreaker::~BrickBreaker() {
    delete[] bricks;
}

void BrickBreaker::add_life() {
    lives += 1;
    display.locate(lives_no_x, lives_no_y);
    display.set_font((unsigned char*) Arial12x12);
    char lives_char[5];
    sprintf(lives_char, "%d", lives);
    printf(lives_char);
}

void BrickBreaker::take_life() {
    lives -= 1;
    display.locate(lives_no_x, lives_no_y);
    display.set_font((unsigned char*) Arial12x12);
    char lives_char[5];
    sprintf(lives_char, "%d", lives);
    printf(lives_char);
}

void BrickBreaker::start() {
    game_time.start();
    paused = false;
    if(start_stop > 0.7) {
        stop(); 
    }
    while(!lost) {
        //draw paddle
        paddle.draw();
        //draw bricks
        for(int i = 0; i < brick_count; i++) {
            if(!bricks[i].is_destroyed())
                bricks[i].draw();    
            else
                display.fillrect(bricks[i].get_x(), bricks[i].get_y(), bricks[i].get_x() + brick_x_length, bricks[i].get_y() + brick_y_length, Blue);  
        }
        //moving ball
        ball.hide();
        ball.move();
        ball.draw();
        
        if(!ball.is_in_game()) {
            ball.hide();
            take_life();
            ball.set_angle(4);
            ball.set_x(ball_start_x);
            ball.set_y(ball_start_y);
            if(lives == 0) {
                show_lose_message();
                lost = true;
                }
        }
        //moving paddle with joystick
        if(VRx > 0.7 && paddle.is_in_game_right()) {
            paddle.hide();
            paddle.move_right();
            paddle.move_right();
        }
        if(VRx < 0.3 && paddle.is_in_game_left()) {
            paddle.hide();
            paddle.move_left();
            paddle.move_left();
        }
        //if ball touches the paddle
        if((ball.get_x() + ball_r_length) >= paddle.get_x() && (ball.get_x() - ball_r_length) <= (paddle.get_x() + paddle.get_length()) &&
                (ball.get_y() + ball_r_length) >= paddle.get_y()) {
                    
            int area_size = paddle.get_length() / areas_no;
            //which part of paddle ball touched
            if((ball.get_x() + ball_r_length) >= paddle.get_x() && ball.get_x() <= paddle.get_x() + area_size) {
                //angle is 157.5
                ball.set_angle(7);
            }
            else if(ball.get_x() > paddle.get_x() + area_size && ball.get_x() <= paddle.get_x() + 2 * area_size) {
                //angle is 135
                ball.set_angle(6);
            }
            else if(ball.get_x() > paddle.get_x() + 2 * area_size && ball.get_x() <= paddle.get_x() + 3 * area_size) {
                //angle is 112.5
                ball.set_angle(5);
            }
            else if(ball.get_x() > paddle.get_x() + 3 * area_size && ball.get_x() <= paddle.get_x() + 4 * area_size) {
                //angle is 90
                ball.set_angle(4);
            }
            else if(ball.get_x() > paddle.get_x() + 4 * area_size && ball.get_x() <= paddle.get_x() + 5 * area_size) {
                //angle is 67.5
                ball.set_angle(3);
            }
            else if(ball.get_x() > paddle.get_x() + 5 * area_size && ball.get_x() <= paddle.get_x() + 6 * area_size) {
                //angle is 45
                ball.set_angle(2);
            }
            else if(ball.get_x() > paddle.get_x() + 6 * area_size && (ball.get_x() - ball_r_length) <= paddle.get_x() + paddle.get_length()) {
                //angle is 22.5
                ball.set_angle(1);
            }
        }
        
        //if ball touches game borders
        //is it left border
        else if(ball.get_x() - ball_r_length <= game_border_x_min) {
            ball.calculate_bounce_angle(1);
        }
        //or right border
        else if(ball.get_x() + ball_r_length >= game_border_x_max) {
            ball.calculate_bounce_angle(3);
        }
        //or top border
        else if(ball.get_y() - ball_r_length <= game_border_y_min) {
            ball.calculate_bounce_angle(2);
        }
        else {
            //if ball touches the brick
            int i = 0;
            for(; i < brick_count; i++) {
                if(bricks[i].is_destroyed())
                    continue;
                //lower and upper side of the brick
                if((ball.get_x() + ball_r_length) >= bricks[i].get_x() && (ball.get_x() - ball_r_length) <= (bricks[i].get_x() + brick_x_length)) {
                    //if it is lower side
                    if((ball.get_y() - ball_r_length) <= (bricks[i].get_y() + brick_y_length) && (ball.get_y() - ball_r_length) >= (bricks[i].get_y())) {
                        ball.calculate_bounce_angle(2);
                        break;
                    }
                    //if it is upper side
                    else if((ball.get_y() + ball_r_length) >= bricks[i].get_y() && (ball.get_y() + ball_r_length) <= (bricks[i].get_y() + brick_y_length)) {
                        ball.calculate_bounce_angle(4);
                        break;
                    }
                }
                //right and left side of the brick
                else if((ball.get_y() - ball_r_length) <= (bricks[i].get_y() + brick_y_length) && (ball.get_y() + ball_r_length) >= bricks[i].get_y()) {
                    //if it is right side
                    if((ball.get_x() - ball_r_length) <= (bricks[i].get_x() + brick_x_length) && (ball.get_x() - ball_r_length) >= bricks[i].get_x()) {
                        ball.calculate_bounce_angle(1);
                        break;
                    }
                    //if it is left side
                    else if((ball.get_x() + ball_r_length) >= bricks[i].get_x() && (ball.get_x() + ball_r_length) <= bricks[i].get_x() + brick_x_length) {
                        ball.calculate_bounce_angle(3);
                        break;
                    }
                }
            }
            if(i != brick_count && bricks[i].is_destroyable()) {
                bricks[i].destroy();
                destroyed_bricks_count++;
                if(destroyed_bricks_count == brick_count)
                    show_win_message();
            }
        }
    }
}

void BrickBreaker::show_win_message() {
    display.background(White);
    display.cls();
    display.foreground(Red);
    display.set_font((unsigned char*) Arial12x12);
    display.locate(100, 70);
    printf("CONGRATULATIONS!");
    display.locate(100, 100);
    printf("TIME: %.2f", get_time());
    wait(3);
    display.cls();
}

void BrickBreaker::show_lose_message() {
    display.background(White);
    display.cls();
    display.foreground(Red);
    display.set_font((unsigned char*) Arial12x12);
    display.locate(100, 70);
    printf("YOU LOST! TRY AGAIN");
    wait(3);
    display.cls();
}

#endif