#include <iostream>
#include <string>
#include <winsock2.h>

int main() {

    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    SOCKET clientSocket = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(6379);

    if (connect(
        clientSocket,
        reinterpret_cast<sockaddr*>(&serverAddress),
        sizeof(serverAddress)
    ) == SOCKET_ERROR) {

        std::cerr << "Connection failed\n";

        closesocket(clientSocket);
        WSACleanup();

        return 1;
    }

    std::cout << "Connected to server!\n";
    std::cout << "Type commands. Type EXIT to quit.\n";

    std::string input;

    while (true) {

        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "EXIT") {
            break;
        }

        input += '\n';

        send(
            clientSocket,
            input.c_str(),
            static_cast<int>(input.size()),
            0
        );

        char buffer[1024];

        int bytesReceived = recv(
            clientSocket,
            buffer,
            sizeof(buffer) - 1,
            0
        );

        if (bytesReceived <= 0) {
            std::cout << "Server disconnected.\n";
            break;
        }

        buffer[bytesReceived] = '\0';

        std::cout << buffer << '\n';
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}