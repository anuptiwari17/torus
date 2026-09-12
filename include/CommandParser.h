#pragma once

#include <string>

enum class CommandType {
    SET,
    GET,
    REMOVE,
    EXISTS
};

struct Command {
    CommandType type;
    std::string key;
    std::string value;
    int ttl = 0;
};

class CommandParser {
public:
    Command parse(const std::string& input);
};