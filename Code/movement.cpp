#include <stdio.h>
#include <time.h>

extern "C" int init(int d_lev);
extern "C" int take_picture();
extern "C" int set_motor(int motor, int speed);
extern "C" char get_pixel(int row, int col, int colour);
extern "C" int Sleep(int sec, int usec);

int main() {
    init(0);
    while(true) {
        take_picture();
        float kp = 0.5; //proportional constant (might need to be changed later based on testing)
        float ki = 0.5; //integral constant
        float kd = 0.5; //derivatve constant
        
        int proportional_signal = 0;
        int integral_signal = 0;
        int derivative_signal = 0;
        
        int current_error = 0;
        int total_error = 0;
        int previous_error = 0;
        int error_period = 0; //try to get a default number by testing
        int error_diff = 0;
        int whiteBlack = 0;
        
        for(int i = 0; i < 320; i++) {
            if(get_pixel(i, 120, 3) > 127) { //to compare the brightness
                whiteBlack = 1; //white
            }
            else {
                whiteBlack = 0; //black
            }
            current_error += (i - 160) * whiteBlack; //help determine scale of adjustment
        }
            
        total_error += current_error; //the sum of all errors
        
      	proportional_signal = current_error * kp;
      	integral_signal = total_error * ki;
      	
      	error_diff = current_error - previous_error;
      	derivative_signal = (error_diff/error_period) * kd;
      	
      	previous_error = current_error;
      	
        set_motor(1, 64 - proportional_signal + integral_signal + derivative_signal); //might need smaller speed to help testing
        set_motor(2, 64 + proportional_signal + integral_signal + derivative_signal);
    }
}
