#include "KeyValueStore.h"


//average complexity in unordered_set : SET => O(1), GET => O(1), EXISTS => O(1), DELETE => O(1)
void KeyValueStore::set(const std::string& key, const std::string& value){
    data[key] = value;
}

std::string KeyValueStore::get(const std::string& key) const{
    auto it = data.find(key);    //why i am using find instead of data[key], kyuki operator[] can create the key if it doesn't exist.

    if(it == data.end()){
        return "(nil)";
    }
    return it->second;
}

bool KeyValueStore::exists(const std::string& key) const{
    return data.find(key) != data.end();
}

bool KeyValueStore::remove(const std::string& key){
    return data.erase(key) > 0;      //erase returns how many elements were removed, mai use true/false me convert kar diya!!
}