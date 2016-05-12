#include <stdio.h>
#include <time.h>

extern "C" int init(int d_lev);
extern "C" int take_picture();
extern "C" int set_motor(int motor, int speed);
extern "C" char get_pixel(int row, int col, int colour);
extern "C" int Sleep(int sec, int usec);

int main(void) {
    init(0);
    while(true) {
        take_picture();
        float kp = 1;
        int error = 0;
        int whiteBlack =0;
        for(int i = 0; i < 320; i++) {
            if(get_pixel(i, 120, 3) > 127) {
                whiteBlack=1;
            }else {
                whiteBlack=0;
            }
            error += (i - 160)*whiteBlack;
            }
      	 float  proportional_signal = error * kp;
        set_motor(1, -(proportional_signal/(160*kp))*128);
        set_motor(2, (proportional_signal/(160*kp))*128);
    }
}
