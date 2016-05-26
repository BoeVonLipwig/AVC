//#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>

extern "C" int init(int d_lev);
extern "C" int connect_to_server(char server_addr[15], int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

extern "C" int take_picture();
extern "C" int set_motor(int motor, int speed);
extern "C" char get_pixel(int row, int col, int colour);
extern "C" int Sleep(int sec, int usec);

/*void terminate(void) {
    set_motor(1,0);
    set_motor(2,0);
    exit(0);
}*/

int main(void) {
   // signal(SIGINT, terminate); //trying to catch CTRL + C to ensure problem stops properly

    init(0);
    char pass[24];
    connect_to_server("130.195.6.196", 1024);
    send_to_server("Please");
    receive_from_server(pass);
    send_to_server(pass);

    int base_speed = 40;
    int total_error = 0;
    int previous_error = 0;
    int last_non_zero_error = 0;
    bool first = true;
    time_t sec = time(NULL);
    while(true) {
        take_picture();
        float kp = -0.1; //proportional constant (might need to be changed later based on testing)
        float ki = 0; //integral constant
        float kd = -1.0; //derivative constant

        float  proportional_signal = 0;
        float integral_signal = 0;
        float derivative_signal = 0;

        int current_error = 0;
        float error_period = 0.1; //try to get a default number by testing (currently set to 1 to avoid dividing by 0)
        int error_diff = 0;
        int whiteBlack = 0;

        int count =0;
        for(int i = 0; i < 32; i++) { //check every 10 pixels to improve response time
            if(get_pixel(i * 10, 120, 3) > 127) { //to compare the brightness
                whiteBlack = 1; //white
                count++;
            }
            else {
                whiteBlack = 0; //black
            }
            current_error += (i - 16) * whiteBlack; //help determine scale of adjustment
        }

        total_error += current_error; //the sum of all errors

	if(count >= 15) {
		last_non_zero_error = current_error;
		//printf("%d\n", count);
	}
        proportional_signal = current_error * kp;
        integral_signal = total_error * ki;

        if(first) {
            previous_error = current_error;
            first = false;
        }
        //error_diff = current_error - previous_error;
        //derivative_signal = (error_diff/error_period) * kd;

        //printf("derivative signal: %d\n", derivative_signal)
        if(count > 0) {
	    previous_error = current_error;
            set_motor(1, base_speed + (proportional_signal + integral_signal + derivative_signal)); //might need smaller speed to help testing
            set_motor(2, base_speed - (proportional_signal + integral_signal + derivative_signal));
        }
        else {
            set_motor(1, -base_speed); //backup when line is lost
            set_motor(2, -base_speed);
            if(last_non_zero_error < 0) { //make a sharp turn if line is lost
                set_motor(1, 50);
                set_motor(2, -50);
            }
            else if(last_non_zero_error > 0) {
                set_motor(1, -50);
                set_motor(2, 50);
            }
        }
       	//error_period = TIME(NULL) - sec; //check actual time delay
        //printf("%d\n", error_period);
    }

}
