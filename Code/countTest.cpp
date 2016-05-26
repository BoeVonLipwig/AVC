//
// Created by Rachel on 26/05/2016.
//
extern "C" int init(int d_lev);
extern "C" int take_picture();
extern "C" int set_motor(int motor, int speed);
extern "C" char get_pixel(int row, int col, int colour);
extern "C" int Sleep(int sec, int usec);

int main() {
    int count = 0;
    while(true) {
        for (int i = 0; i < 32; i++) { //check every 10 pixels to improve response time
            if (get_pixel(i * 10, 120, 3) > 127) { //to compare the brightness
                count++;
            }
            current_error += (i - 16) * whiteBlack; //help determine scale of adjustment
        }
        printf("%d\n", count);
    }
}
