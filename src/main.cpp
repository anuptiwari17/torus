#include<iostream>
#include "KeyValueStore.h"

int main() {
    KeyValueStore store;

    store.set("name", "Nitin");
    store.set("age", "19");

    std::cout<<store.get("name")<<"\n";
    std::cout<<store.get("unknown")<<"\n";
    std::cout<<store.exists("name")<<"\n";
    std::cout<<store.exists("city")<<"\n";

    store.remove("name");

    std::cout<<store.exists("name")<<"\n";
    return 0;
}