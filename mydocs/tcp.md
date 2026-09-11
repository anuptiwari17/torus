# TCP server


### Abhi tak kya hai? abhi mai terminal me type karta hu 'SET name Nitin' , now this command goes to -> main.cpp file and communicates with -> KeyValueStore

### But suppose I have another program on my laptop `Client Program` and I want it to communicate with our data server.
### We need a communication channel : TCP is one way to create that reliable communication channel between `Client` and `Our Server`.


## Socket
### basically an endpoint for communication
### in networking for communication there are things like this ->  `Client Socket` <----> `Server Socket`.
### This socket allows programs to send data and receive data


### socket is combo of IP + port (u know thiss)


## TCP
### for reliable connection between two programs


## on high level ye sb chize implement karni haii!

### 1. Create socket
### 2. Bind socket to IP + port
### 3. Listen for clients
### 4. Accept a client
### 5. Receive data
### 6. Process data
### 7. Send response
### 8. Close client connection


## FOR NOW ONE CLIENT AT A TIME

Kuch aisa ->

Client
  │
  │ TCP
  ▼
Server
  │
  ├── receives request
  │
  ▼
CommandParser
  │
  ▼
CommandExecutor
  │
  ▼
KeyValueStore





### socket() : create a socket, basically give me a communication endpoint

### bind() : Now we tell the socket - "I want you to use this IP and port"

### listen() : "I am a server. Start waiting for clients"

### accept() : A client connects. The server calls - accept() and gets a new socket for communicating with that particular client.
### Remember this accept() has created a new client socket, the original listening socket continues to listen for new clinets.

### recv() : receives the data

### sends() : sends the data, bich me processing hm apna karenge




Windows me linux se thoda sa different hota hia socket API

Linux wale -> 
socket()
bind()
listen()
accept()
recv()
send()
close()


In Windows -> 
socket()
bind()
listen()
accept()
recv()
send()
closesocket()   [ye wala waha close() naam se tha]

SAATH hi Saath windows also requires initialising Winsock first :
### WSAStartup(...)

and also cleaning it up
### WSACleanup()



## to phir hamara server kuch aisa dikhega 

WSAStartup
     ↓
socket
     ↓
bind
     ↓
listen
     ↓
accept
     ↓
recv/send
     ↓
closesocket
     ↓
WSACleanup




## Windows ka thoda dekh lete hai :

### we need -> #include <winsock2.h>
### and before creating sockets ->  WSAStartup(...)     and when we are finished   WSACleanup()


### Now this scary line   
### if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
###    std::cerr << "WSAStartup failed\n";
###    return 1;
### }

### ROUGHLY MEANS "Initialize Winsock version 2.2 and put the resulting information into wsaData."

