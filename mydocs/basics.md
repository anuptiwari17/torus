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


