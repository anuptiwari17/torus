#pragma once

#include <winsock2.h>
#include <thread>

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

    void handleClient(SOCKET clientSocket);

public:
    explicit Server(int port);

    void start();
    void stop();
};