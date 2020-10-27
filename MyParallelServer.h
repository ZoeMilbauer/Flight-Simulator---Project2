#ifndef PROJECT2_MYPARALLELSERVER_H
#define PROJECT2_MYPARALLELSERVER_H
#include "Server.h"
#include "ClientHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <thread>





class MyParallelServer : public Server {
    int sockfd;
public:
    MyParallelServer();
    void open(int port, ClientHandler* c);
    void stop();
};


#endif
