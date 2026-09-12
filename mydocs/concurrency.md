# Concurrency

### why do we need this?

Abhi server ek time pe ek client ko handle karta hai.

```text
Client A
   ↓
server handles A
   ↓
A disconnects
   ↓
server handles B
```

If A is connected for a long time, B has to wait.

So we want:

```text
Client A → Thread A
Client B → Thread B
Client C → Thread C
```

Now server can handle multiple clients concurrently.

---

## Thread in C++

C++ provides:

```cpp
#include <thread>
```

Create a thread:

```cpp
std::thread t(function);
```

Basically:

> "is function ko ek alag thread me run karo."

Example:

```cpp
void work() {
    // something
}

std::thread t(work);
```

### join()

```cpp
t.join();
```

Means current thread waits until `t` finishes.

Basically:

> "pehle ye thread complete hone do."

---

## Thread with function arguments

```cpp
void handleClient(SOCKET clientSocket) {
    // handle client
}

std::thread t(handleClient, clientSocket);
```

The `clientSocket` is passed to the new thread.

---

## Member function as a thread

If function belongs to a class:

```cpp
std::thread t(
    &Server::handleClient,
    this,
    clientSocket
);
```

Roughly:

```text
&Server::handleClient
        ↓
which function?

this
        ↓
which Server object?

clientSocket
        ↓
argument to the function
```

---

## detach()

```cpp
t.detach();
```

Means thread runs independently and we don't wait for it using `join()`.

For our server:

```text
accept client
     ↓
create thread
     ↓
detach thread
     ↓
accept next client
```

The server can immediately continue accepting clients.

Need to be careful with detached threads because the main/server object must remain alive while those threads are using it.

---

# Shared data

Our clients all use the same:

```cpp
KeyValueStore store;
```

So after threads:

```text
Thread A ──┐
Thread B ──┼──> same KeyValueStore
Thread C ──┘
```

This is shared state.

Multiple threads can access the same `unordered_map`.

---

# Mutex

C++:

```cpp
#include <mutex>
```

Create:

```cpp
std::mutex mutex;
```

Basically:

> mutex ko use karke shared data ko protect karenge.

---

## lock_guard

Instead of manually doing:

```cpp
mutex.lock();

// use shared data

mutex.unlock();
```

we can use:

```cpp
std::lock_guard<std::mutex> lock(mutex);
```

Then:

```cpp
{
    std::lock_guard<std::mutex> lock(mutex);

    data[key] = value;
}
```

Basically:

```text
lock
 ↓
critical section
 ↓
scope ends
 ↓
automatic unlock
```

This is safer because we don't have to remember to manually unlock.

---

## Critical section

The part where shared data is being accessed/modified.

Example:

```cpp
std::lock_guard<std::mutex> lock(mutex);

data[key] = value;
```

Here accessing/modifying `data` is the important part we want to protect.

---

## Important design decision

The `KeyValueStore` owns the data.

So it should also protect the data.

Not:

```text
Server
 ↓
lock
 ↓
KeyValueStore
```

Instead:

```text
Server
 ↓
CommandExecutor
 ↓
KeyValueStore
 ↓
mutex
 ↓
data
```

This keeps the locking responsibility inside the class that owns the shared state.






# NOTE THIS   
## Mutex doesn't lock a variable. It locks access to a critical section of code. 

std::lock_guard<std::mutex> lock(mtx);
counter++;

means:

"Before I enter this section of code, I want to acquire this lock."

The mutex protects the code section, not a specific variable.