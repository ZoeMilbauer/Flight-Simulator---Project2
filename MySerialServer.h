#ifndef PROJECT2_MYSERIALSERVER_H
#define PROJECT2_MYSERIALSERVER_H

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

class MySerialServer : public Server {
    int sockfd;
public:
    MySerialServer();
    void open(int port, ClientHandler* c);
    void stop();
};
#endif
