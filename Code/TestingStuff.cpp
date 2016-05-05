//
// Created by Shaun on 3/05/2016.
//
# include <stdio.h>
# include <time.h>

extern "C" int init();
extern "C" int Sleep(int sec, int usec);
extern "C" int set_motor(int motor , int speed );
extern "C" int take_picture();
extern "C" int save_picture(char filename[5]);

int main() {
    init();
    set_motor(1,255);
    set_motor(2,255);
    Sleep(5,0);
    set_motor(1,0);
    set_motor(2,0);
    Sleep(2,0);
    take_picture();
    save_picture("test");
    return 0;
}

void turn(int dir) {
    if(dir == 1) {
        set_motor(1,128);
        set_motor(2, 64);
    }
    else if(dir == 2) {
        set_motor(1,64);
        set_motor(2,128);
    }
}
