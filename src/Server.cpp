#include "Server.h"

#include<iostream>
#include<cstring>
#include<stdexcept>

Server::Server(int port)
    : serverSocket(INVALID_SOCKET),
      port(port),
      store(),
      parser(),
      executor(store) {
}



void Server::start(){

    WSADATA wsaData;

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
        throw std::runtime_error("WSAStartup failed");
    }

    serverSocket = socket(
        AF_INET,   //iska mtlb ipv4
        SOCK_STREAM,   //iska matlab i need streaming socket
        0
    );

    if(serverSocket == INVALID_SOCKET){
        WSACleanup();
        throw std::runtime_error("Socket creation failed");
    }

    //server socket ban gya now have to give it port + IP

    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(port);

    if(bind(
        serverSocket,
        reinterpret_cast<sockaddr*>(&serverAddress),
        sizeof(serverAddress)
    ) == SOCKET_ERROR){

        closesocket(serverSocket);
        WSACleanup();

        throw std::runtime_error("Bind failed");
    }

    if(listen(serverSocket, 5) == SOCKET_ERROR){

        closesocket(serverSocket);
        WSACleanup();

        throw std::runtime_error("Listen failed");
    }

    std::cout << "Server listening on 127.0.0.1:"
              << port << '\n';

    SOCKET clientSocket = accept(
        serverSocket,
        nullptr,
        nullptr
    );

    if(clientSocket == INVALID_SOCKET){

        closesocket(serverSocket);
        WSACleanup();

        throw std::runtime_error("Accept failed");
    }

    std::cout << "Client connected!\n";

    char buffer[1024];

    int bytesReceived = recv(
        clientSocket,
        buffer,
        sizeof(buffer) - 1,
        0
    );

    if(bytesReceived > 0){

        buffer[bytesReceived] = '\0';

        std::string input(buffer);

        std::cout << "Received: " << input << '\n';

        try{
            Command command = parser.parse(input);

            std::string response =
                executor.execute(command);

            send(
                clientSocket,
                response.c_str(),
                static_cast<int>(response.size()),
                0
            );
        }
        catch(const std::exception& e){

            std::string error =
                "ERR " + std::string(e.what());

            send(
                clientSocket,
                error.c_str(),
                static_cast<int>(error.size()),
                0
            );
        }
    }

    closesocket(clientSocket);
}

void Server::stop(){

    if(serverSocket != INVALID_SOCKET){
        closesocket(serverSocket);
        serverSocket = INVALID_SOCKET;
    }

    WSACleanup();
}