//
// Created by Shaun on 3/05/2016.
//
# include <stdio.h>
# include <time.h>

extern "C" int init();
extern "C" int Sleep(int sec, int usec);
extern "C" int set_motor(int motor , int speed );

int main() {
    init();
    set_motor(1,255);
    set_motor(2,255);
    Sleep(5,0);
    set_motor(1,0);
    set_motor(2,0);
    return 0;
}