# Torus

A lightweight in-memory key-value data server built from scratch in **C++17**.

The project is being developed incrementally to understand how systems like Redis work internally, while practicing software architecture, data structures, TCP networking, concurrency, persistence, and performance.

## Current Features

* In-memory key-value storage
* `SET` command
* `GET` command
* `REMOVE` command
* `EXISTS` command
* Command parsing and argument validation
* Separate command execution layer
* Error handling for invalid commands
* Case-insensitive commands
* Hash-table-based storage using `std::unordered_map`
* TCP client-server communication using Winsock
* Persistent client connections
* Multiple commands per client connection
* Newline-delimited message framing
* Buffering of TCP data to handle incomplete or combined reads

## Architecture

```text
Client
   │
   │ TCP
   ▼
Server
   │
   ▼
CommandParser
   │
   ▼
Command
   │
   ▼
CommandExecutor
   │
   ▼
KeyValueStore
   │
   ▼
std::unordered_map
```

### Components

**KeyValueStore**

Responsible for storing and managing key-value data using `std::unordered_map`.

**CommandParser**

Converts raw text commands into structured `Command` objects and validates their arguments.

Example:

```text
SET name Nitin
```

becomes:

```text
Command {
    type  = SET,
    key   = "name",
    value = "Nitin"
}
```

**CommandExecutor**

Executes parsed commands against the `KeyValueStore` and returns a response.

**Server**

Handles TCP socket setup, client connections, receiving commands, message framing, and sending responses.

## Project Structure

```text
torus/

│
├── include/
│   ├── KeyValueStore.h
│   ├── CommandParser.h
│   └── CommandExecutor.h
│
├── src/
│   ├── KeyValueStore.cpp
│   ├── CommandParser.cpp
│   ├── CommandExecutor.cpp
│   ├── Server.cpp
│   ├── BasicServer.cpp
│   ├── BasicClient.cpp
│   └── main.cpp
│
└── README.md
```

## Build

Requires a C++17-compatible compiler.

### Windows

Compile with:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/main.cpp src/KeyValueStore.cpp src/CommandParser.cpp src/CommandExecutor.cpp src/Server.cpp -lws2_32 -o torus
```

Run:

```powershell
.\torus.exe
```

The server starts on:

```text
127.0.0.1:6379
```

## TCP Communication

Torus uses TCP for communication between the client and server.

TCP provides a reliable ordered byte stream, but it does not preserve application-level message boundaries.

To solve this, Torus uses **newline-delimited message framing**.

```text
SET name Nitin\n
GET name\n
```

The client adds `\n` to each command.

The server buffers received bytes and extracts complete commands whenever a newline is found.

```text
TCP → Buffer → Find \n → Command → Parser
```

This allows the server to correctly handle cases where:

* A command arrives in multiple TCP reads.
* Multiple commands arrive in a single TCP read.

## Supported Commands

### SET

```text
SET name Nitin
```

Response:

```text
OK
```

### GET

```text
GET name
```

Response:

```text
Nitin
```

### EXISTS

```text
EXISTS name
```

Response:

```text
1
```

### REMOVE

```text
REMOVE name
```

Response:

```text
1
```

### Invalid Commands

Invalid commands or incorrect arguments return an error.

Example:

```text
SET name
```

Response:

```text
ERR SET requires key and value
```

## Example

```text
> SET name Nitin
OK

> GET name
Nitin

> EXISTS name
1

> REMOVE name
1

> GET name
(nil)

> EXISTS name
0
```

## Current Design

The project intentionally separates responsibilities:

```text
Networking
     ↓
Parsing
     ↓
Execution
     ↓
Storage
```

Each layer has a focused responsibility:

```text
Server
  → handles TCP communication

CommandParser
  → validates and parses commands

CommandExecutor
  → executes operations

KeyValueStore
  → manages data
```

This separation makes it easier to add future functionality without tightly coupling networking, command handling, and storage.

## Roadmap

The project is being developed incrementally:

* [x] In-memory key-value store
* [x] Command parser
* [x] Command executor
* [x] TCP networking
* [x] Persistent client connections
* [x] Newline-delimited message framing
* [ ] Multiple clients sequentially
* [ ] Concurrent client handling
* [ ] Thread synchronization with mutexes
* [ ] TTL / key expiration
* [ ] Persistent append-only log
* [ ] Recovery after restart
* [ ] LRU eviction and memory limits
* [ ] Benchmarking and performance analysis
* [ ] Pub/Sub (Optional)

The goal is to build a compact but technically meaningful systems project rather than reproduce the entire Redis codebase.
