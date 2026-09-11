#pragma once

#include <string>

enum class CommandType {
    SET,
    GET,
    DELETE,
    EXISTS
};

struct Command {
    CommandType type;
    std::string key;
    std::string value;
};

class CommandParser {
public:
    Command parse(const std::string& input);
};