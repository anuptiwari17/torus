#pragma once

#include <string>
#include <unordered_map>
#include <mutex>
#include <chrono>

class KeyValueStore {
private:
    struct Entry {
        std::string value;
        std::chrono::steady_clock::time_point expiry;
        bool hasExpiry;
    };

    std::unordered_map<std::string, Entry> data;
    std::mutex mutex;

public:
    void set(
        const std::string& key,
        const std::string& value
    );

    void set(
        const std::string& key,
        const std::string& value,
        int ttlSeconds
    );

    std::string get(const std::string& key);
    bool exists(const std::string& key);
    bool remove(const std::string& key);
};