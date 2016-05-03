//
// Created by Shaun on 3/05/2016.
//
# include <stdio.h>
# include <time.h>

extern "C" int InitHardware();
extern "C" int Sleep(int sec, int usec);
extern "C" int set_motor(int motor , int speed );

int main() {
    InitHardware();
    set_motor(1,255);
    Sleep(5,0);
    set_motor(1,0);
    return 0;
}