//#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

extern "C" int init(int d_lev);
extern "C" int connect_to_server(char server_addr[15], int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);


int main() {
    init(0);
    int pass;
    char gateIp[] = "130.195.6.196";
    char msg[] = "my-password";
    connect_to_server(gateIp, 22);
    pass = receive_from_server(msg);
    send_to_server((char *) pass);
    return 0;
}
