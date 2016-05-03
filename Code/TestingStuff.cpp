//
// Created by Shaun on 3/05/2016.
//
# include <stdio.h>
# include <time.h>

extern "C" int InitHardware();
extern "C" int Sleep(int sec, int usec);
extern "C" int SetPWM(int chan, int value);

int main() {
    InitHardware();
    SetPWM(7, 255);
    Sleep(5,0);
    SetPWM(7,0);
    return 0;
}