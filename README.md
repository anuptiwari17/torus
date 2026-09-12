# Torus

A lightweight in-memory key-value data server built from scratch in **C++17**.

The project is being developed incrementally to understand how systems like Redis work internally, while practicing software architecture, data structures, TCP networking, concurrency, persistence, and performance.

## Current Features

* In-memory key-value storage
* `SET` command
* `GET` command
* `REMOVE` command
* `EXISTS` command
* TTL-based key expiration
* Command parsing and argument validation
* Separate command execution layer
* Error handling for invalid commands
* Case-insensitive commands
* Hash-table-based storage using `std::unordered_map`
* TCP client-server communication using Winsock
* Multiple commands per client connection
* Newline-delimited message framing
* Buffering of TCP data to handle incomplete or combined reads
* Multiple clients handled concurrently using threads
* Mutex-protected shared key-value store
* Lazy expiration of expired keys

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
   ├── unordered_map
   └── TTL
```

### Components

**KeyValueStore**

Responsible for storing and managing key-value data using `std::unordered_map`.

It also handles TTL information and removes expired keys when they are accessed.

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

Each connected client is handled using a separate thread.

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

## Multiple Clients

The server continuously accepts new client connections and handles each client in a separate thread.

```text
Client A
   ↓
accept()
   ↓
Thread A
   ↓
handle A

Client B
   ↓
accept()
   ↓
Thread B
   ↓
handle B

Client C
   ↓
accept()
   ↓
Thread C
   ↓
handle C
```

This allows multiple clients to interact with the server concurrently.

Since all client threads share the same `KeyValueStore`, a mutex is used to safely protect access to the shared data.

## TTL / Key Expiration

Torus supports optional TTL when setting a key.

### Syntax

```text
SET key value ttl
```

Example:

```text
SET name Nitin 10
```

The key will expire after 10 seconds.

```text
> SET name Nitin 10
OK

> GET name
Nitin
```

After 10 seconds:

```text
> GET name
(nil)
```

Torus uses **lazy expiration**.

Instead of continuously checking every key in the background, expiration is checked when a key is accessed using `GET` or `EXISTS`.

If the key has expired, it is removed from the store.

## Supported Commands

### SET

```text
SET name Nitin
```

Response:

```text
OK
```

### SET with TTL

```text
SET name Nitin 10
```

Response:

```text
OK
```

The key expires after 10 seconds.

### GET

```text
GET name
```

Response:

```text
Nitin
```

If the key does not exist or has expired:

```text
(nil)
```

### EXISTS

```text
EXISTS name
```

Response:

```text
1
```

Returns `0` if the key does not exist or has expired.

### REMOVE

```text
REMOVE name
```

Response:

```text
1
```

Returns `0` if the key does not exist.

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

TTL example:

```text
> SET city Delhi 10
OK

> GET city
Delhi

(after 10 seconds)

> GET city
(nil)
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
  → accepts clients
  → creates concurrent client threads

CommandParser
  → validates and parses commands

CommandExecutor
  → executes operations

KeyValueStore
  → manages data
  → handles TTL
  → protects shared data with a mutex
```

This separation makes it easier to add future functionality without tightly coupling networking, command handling, and storage.

## Roadmap

The project is being developed incrementally:

* [x] In-memory key-value store
* [x] Command parser
* [x] Command executor
* [x] TCP networking
* [x] Multiple commands per connection
* [x] Newline-delimited message framing
* [x] Multiple client connections
* [x] Concurrent client handling
* [x] Thread synchronization with mutexes
* [x] TTL / key expiration
* [ ] Persistent append-only log
* [ ] Recovery after restart
* [ ] LRU eviction and memory limits
* [ ] Benchmarking and performance analysis
* [ ] Pub/Sub (Optional)

The goal is to build a compact but technically meaningful systems project rather than reproduce the entire Redis codebase.
