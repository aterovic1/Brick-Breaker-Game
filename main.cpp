#include "Utils.h"
#include "BrickBreaker.h"

DigitalOut enable(dp14);

int selected_level = 1;

void start_menu() {
    
    display.background(White);
    display.foreground(Red);
    display.set_font((unsigned char*) Arial12x12);
    display.locate(100, 70);
    printf("BRICKBREAKER");
    
    if(selected_level == 1)
        display.background(Blue);
    else
        display.background(White);
    display.locate(120, 120);
    display.set_font((unsigned char*) Arial12x12);
    display.fillcircle(120, 120, 5, Red);
    display.locate(130, 115);
    printf("LEVEL 1");
    
    if(selected_level == 2)
        display.background(Blue);
    else
        display.background(White);
    display.locate(120, 150);
    display.set_font((unsigned char*) Arial12x12);
    display.fillcircle(120, 150, 5, Red);
    display.locate(130, 145);
    printf("LEVEL 2");
    
    if(selected_level == 3)
        display.background(Blue);
    else
        display.background(White);
    display.locate(120, 180);
    display.set_font((unsigned char*) Arial12x12);
    display.fillcircle(120, 180, 5, Red);
    display.locate(130, 175);
    printf("LEVEL 3");
    wait(0.1);
}

void choose_level() {
    BrickBreaker game(selected_level);
    game.start();
}

int main() {
    //joystick
    enable = 1;
    SW.mode(PullUp);
    //initialize display
    display.claim(stdout);
    display.set_orientation(1);
    display.background(White);
    display.foreground(Blue);
    display.cls();
    
    while(1) {
        SW.rise(&choose_level);
        start_menu();
        if(VRy > 0.7) {
            selected_level++;
            if(selected_level == 4)
                selected_level = 1;
        }
        if(VRy < 0.3) {
            selected_level--;
            if(selected_level == 0)
                selected_level = 3;
        }
        
    }
}