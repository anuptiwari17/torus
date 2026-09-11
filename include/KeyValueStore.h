#pragma once

#include<string>
#include<unordered_map>

//why not namespace?

class KeyValueStore{
private:
    std::unordered_map<std::string, std::string> data;
public:
    void set(const std::string& key, const std::string& value);
    std::string get(const std::string& key) const;
    bool exists(const std::string& key) const;
    bool remove(const std::string& key);
};

