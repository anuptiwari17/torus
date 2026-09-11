#pragma once

#include<winsock2.h>

#include "CommandParser.h"
#include "CommandExecutor.h"
#include "KeyValueStore.h"

class Server {
private:
    SOCKET serverSocket;
    int port;

    KeyValueStore store;
    CommandParser parser;
    CommandExecutor executor;

public:
    explicit Server(int port);

    void start();
    void stop();
};