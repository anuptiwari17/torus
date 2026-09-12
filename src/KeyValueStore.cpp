#include "KeyValueStore.h"

void KeyValueStore::set(
    const std::string& key,
    const std::string& value
) {
    std::lock_guard<std::mutex> lock(mutex);

    data[key] = {
        value,
        {},
        false
    };
}

void KeyValueStore::set(
    const std::string& key,
    const std::string& value,
    int ttlSeconds
) {
    std::lock_guard<std::mutex> lock(mutex);

    data[key] = {
        value,
        std::chrono::steady_clock::now()
            + std::chrono::seconds(ttlSeconds),
        true
    };
}

std::string KeyValueStore::get(
    const std::string& key
) {
    std::lock_guard<std::mutex> lock(mutex);

    auto it = data.find(key);

    if (it == data.end()) {
        return "(nil)";
    }

    if (
        it->second.hasExpiry &&
        std::chrono::steady_clock::now() >= it->second.expiry
    ) {
        data.erase(it);
        return "(nil)";
    }

    return it->second.value;
}

bool KeyValueStore::exists(
    const std::string& key
) {
    std::lock_guard<std::mutex> lock(mutex);

    auto it = data.find(key);

    if (it == data.end()) {
        return false;
    }

    if (
        it->second.hasExpiry &&
        std::chrono::steady_clock::now() >= it->second.expiry
    ) {
        data.erase(it);
        return false;
    }

    return true;
}

bool KeyValueStore::remove(
    const std::string& key
) {
    std::lock_guard<std::mutex> lock(mutex);

    return data.erase(key) > 0;
}