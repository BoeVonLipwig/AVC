#include <iostream>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>

extern "C" int init(int d_lev);
extern "C" int connect_to_server(char server_addr[15], int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);


int main() {
    init(1);
    int pass;
    connect_to_server("130.195.6.196", 22);
    pass=receive_from_server("my-password");
    send_to_server((char *) pass);
    return 0;
}