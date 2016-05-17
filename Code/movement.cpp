#include <stdio.h>
#include <time.h>

extern "C" int init(int d_lev);
extern "C" int take_picture();
extern "C" int set_motor(int motor, int speed);
extern "C" char get_pixel(int row, int col, int colour);
extern "C" int Sleep(int sec, int usec);

int main() {
    init(0);
    int total_error = 0;
    int previous_error = 0;
    while(true) {
        take_picture();
        float kp = 0.125; //proportional constant (might need to be changed later based on testing)
        float ki = 0; //integral constant
        float kd = 0; //derivatve constant
        
        int proportional_signal = 0;
        int integral_signal = 0;
        int derivative_signal = 0;
        
        int current_error = 0;
        int error_period = 1; //try to get a default number by testing (currently set to 1 to avoid dividing by 0)
        int error_diff = 0;
        int whiteBlack = 0;
        //int count =0;
        for(int i = 0; i < 320; i++) {
            if(get_pixel(i, 120, 3) > 127) { //to compare the brightness
                whiteBlack = 1; //white
                //count++;
            }
            else {
                whiteBlack = 0; //black
            }
            current_error += (i - 160) * whiteBlack; //help determine scale of adjustment
        }
        //current_error/count;
        total_error += current_error; //the sum of all errors
        
      	proportional_signal = current_error * kp;
      	integral_signal = total_error * ki;
      	
      	error_diff = current_error - previous_error;
      	derivative_signal = (error_diff/error_period) * kd;
      	
      	previous_error = current_error;
      	//printf("proportional signal: %d\n", proportional_signal);
        set_motor(1, 32 + (proportional_signal + integral_signal + derivative_signal)); //might need smaller speed to help testing
        set_motor(2, 32 - (proportional_signal + integral_signal + derivative_signal));
    }
}
