# Torus

A lightweight in-memory key-value data server built from scratch in **C++17**.

The project is being developed incrementally to understand how systems like Redis work internally, while practicing clean software architecture, data structures, networking, concurrency, persistence, and performance.

## Current Features

* In-memory key-value storage
* `SET` command
* `GET` command
* `DELETE` command
* `EXISTS` command
* Command parsing and validation
* Separate command execution layer
* Error handling for invalid commands
* Case-insensitive commands
* Hash-table-based storage using `std::unordered_map`

## Architecture

```text
User Input
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

Responsible only for storing and managing key-value data.

**CommandParser**

Converts raw text commands into structured `Command` objects.

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
│   └── main.cpp
│
└── README.md
```

## Build

Requires a C++17-compatible compiler.

Compile with:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude \
src/main.cpp \
src/KeyValueStore.cpp \
src/CommandParser.cpp \
src/CommandExecutor.cpp \
-o torus
```

Run:

### Windows

```powershell
.\torus.exe
```

### Linux/macOS

```bash
./torus
```

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

### DELETE

```text
DELETE name
```

Response:

```text
1
```

### EXIT

```text
EXIT
```

Stops the server.

## Example

```text
Mini Redis Server
Type commands or EXIT to quit.

> SET name Nitin
OK

> GET name
Nitin

> EXISTS name
1

> DELETE name
1

> GET name
(nil)

> EXISTS name
0

> EXIT
```

## Current Design

The project intentionally separates responsibilities:

```text
Parsing ≠ Execution ≠ Storage
```

This allows new layers such as networking, concurrency, expiration, persistence, and caching to be added without tightly coupling them to the storage implementation.

## Roadmap

The project will be developed incrementally:

* [x] In-memory key-value store
* [x] Command parser
* [x] Command executor
* [ ] TCP networking
* [ ] Multiple clients
* [ ] Concurrent request handling
* [ ] TTL / key expiration
* [ ] Persistent append-only log
* [ ] Recovery after restart
* [ ] LRU eviction and memory limits 
* [ ] Benchmarking and performance analysis (Optional)
* [ ] Pub/Sub (Optional)

The goal is to build a compact but technically meaningful systems project rather than reproduce the entire Redis codebase.
