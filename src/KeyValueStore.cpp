#include "KeyValueStore.h"


//average complexity in unordered_set : SET => O(1), GET => O(1), EXISTS => O(1), REMOVE => O(1)
void KeyValueStore::set(const std::string& key, const std::string& value){

    std::lock_guard<std::mutex> lock(mutex);
    data[key] = value;
}

std::string KeyValueStore::get(const std::string& key) const{
    auto it = data.find(key);    //why i am using find instead of data[key], kyuki operator[] can create the key if it doesn't exist.

    std::lock_guard<std::mutex> lock(mutex);
    if(it == data.end()){
        return "(nil)";
    }
    return it->second;
}

bool KeyValueStore::exists(const std::string& key) const{
    std::lock_guard<std::mutex> lock(mutex);
    return data.find(key) != data.end();
}

bool KeyValueStore::remove(const std::string& key){

    std::lock_guard<std::mutex> lock(mutex);
    return data.erase(key) > 0;      //erase returns how many elements were removed, mai use true/false me convert kar diya!!
}