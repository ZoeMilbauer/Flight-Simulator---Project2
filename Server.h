#ifndef PROJECT2_SERVER_H
#define PROJECT2_SERVER_H

#include "MyClientHandler.h"
class Server {

public:
    virtual void open(int port,ClientHandler* c) = 0;
    virtual void stop() = 0;
};

#endif
