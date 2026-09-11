# basic questions clarified

### Q. what is this pragma line 
### => #pragma is a compiler directive, its means it says "Hey Compiler, I want you to do something special."  
### For example #pragma once means iss file ko ek baar hi include karna (u know what i mean)
### and second example :  #pragma comment(lib, "ws2_32.lib") ,     is basically telling the Microsoft/Windows compiler:
### "Link my program with the Windows Winsock library."
### server bnate smay we need to tell program use the windws networking library(that is WINSOCK , ws2_32) ,  so ham ye line shuru me upar likhe hai,   but we can avoid ye line  if while compiling hm ye flag add kar de  `-lws2_32` ,  it will do same thing




### Q. explicit keyword 
### => `explicit` prevents **implicit conversion** through a constructor.
```cpp
explicit CommandExecutor(KeyValueStore& store);
```
### Without `explicit`, C++ might allow:
```cpp
CommandExecutor obj = store;  // ❌ unwanted implicit conversion
```
### With `explicit`, you must write:
```cpp
CommandExecutor obj(store);    // ✅
```
### **In one line:** `explicit` = *"Don't automatically convert; make the construction intentional."*








# TILL NOWWWWWWWWW

### 🧠 Torus: Mini Redis-like Data Server

**1. Key-Value Store**

* Used `unordered_map` to store `key → value`.
* Implemented:

  * `SET`
  * `GET`
  * `REMOVE`
  * `EXISTS`
* Average lookup/insert/delete: **O(1)**.

**2. Command Parser**

* Converts command to uppercase, so `set`, `SET`, `SeT` all work.
* Checks whether commands have the correct arguments.
* Example:

  ```text
  SET age 18     → valid
  SET age        → error
  GET age extra  → error
  ```

**3. Command Executor**

* Takes the parsed command.
* Calls the appropriate `KeyValueStore` function.
* Keeps parsing separate from actual data operations.

**4. TCP Networking**
Learned the basic server flow:

```text
socket()
   ↓
bind()
   ↓
listen()
   ↓
accept()
   ↓
recv()
   ↓
send()
```

* `IP` → identifies the machine.
* `Port` → identifies the service.
* `127.0.0.1:6379` → our local server.
* TCP gives reliable, ordered communication.

**5. Client ↔ Server**
Our client connects to the server and sends commands:

```text
Client → "SET name anup"
Server → "OK"
```

**6. Persistent Connection**
Instead of handling only one command, we added a loop:

```text
recv → parse → execute → send
              ↑          ↓
              └──────────┘
```

So one client can execute multiple commands without reconnecting.

**7. Message Framing**
Important networking issue: **TCP is a byte stream, not a message system.**

So we decided:

```text
SET name anup\n
GET name\n
```

`'\n'` marks the end of a command.

The server stores incoming data in a buffer and extracts commands whenever it finds `\n`.

---

### 🚀 Current status

```text
✅ Key-value storage
✅ Command parsing
✅ Command validation
✅ Command execution
✅ TCP server
✅ TCP client
✅ Multiple commands per connection
✅ Basic message framing
```

### Next

**Multiple clients → server loop → threads → mutex/concurrency.**
