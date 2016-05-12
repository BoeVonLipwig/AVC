#include <stdio.h>
#include <time.h>

extern "C" int init(int d_lev);
extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int colour);
extern "C" int Sleep(int sec, int usec);

int main(void) {
    init(0);
    set_motor(2, 64);
    while(true) {
        take_picture();
        float proportional_error;
        float kp = 0.5;
        int error = 0;
        for(int i = 0; i < 320; i++) {
            int w = get_pixel(i, 120, 3);
            if(w > 127) {
                error += (i - 160);
            }
        }
        proportional_error = error * kp;
        set_motor(1, (proportional_signal/(160*1*kp))*128);
    }
}
