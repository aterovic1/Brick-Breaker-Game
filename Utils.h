#ifndef UTILS_H
#define UTILS_H

#include "mbed.h"
#include "stdio.h"
#include "SPI_TFT_ILI9341.h"
#include "string"
#include "Arial12x12.h"
#include "Arial24x23.h"
#include "Arial28x28.h"
#include "font_big.h"

#define dp23 P0_0

//brick length
#define brick_x_length 30
#define brick_y_length 7

//paddle length and distance between paddle and bottom of the screen
#define paddle_x_length 50
#define paddle_y_length 8
#define paddle_height 30
#define areas_no 7

//ball diameter
#define ball_r_length 4

//game borders
#define game_border_x_min 0
#define game_border_x_max 320
#define game_border_y_min 10
#define game_border_y_max 240

//ball and paddle start positions
#define paddle_start_x 135
#define paddle_start_y 202
#define ball_start_x 162
#define ball_start_y 198

//heart and number of lives location
#define heart_x 3
#define heart_y 2
#define lives_no_x 10
#define lives_no_y 2
#define heart_size_x 7
#define heart_size_y 6

#define expand_size_x 8
#define expand_size_y 5

//display
//mosi, miso, sclk, cs, reset, dc
SPI_TFT_ILI9341 display(dp2, dp1, dp6, dp24, dp23, dp25, "TFT");
//joystick
AnalogIn VRx(dp11);
AnalogIn VRy(dp10);
InterruptIn SW(dp9);

#endif