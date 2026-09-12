#include "CommandParser.h"

#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

namespace {

std::string toUpper(std::string value) {
    std::transform(
        value.begin(),
        value.end(),
        value.begin(),
        [](unsigned char c) {
            return static_cast<char>(std::toupper(c));
        }
    );

    return value;
}

}

Command CommandParser::parse(const std::string& input) {

    std::stringstream ss(input);

    std::string command;
    std::string key;
    std::string value;
    std::string extra;

    ss >> command;

    if (command.empty()) {
        throw std::invalid_argument("Empty command");
    }

    command = toUpper(command);

    if (command == "SET") {

    if (!(ss >> key >> value)) {
        throw std::invalid_argument(
            "SET requires key and value"
        );
    }

    int ttl = 0;

    if (ss >> ttl) {

        if (ttl <= 0) {
            throw std::invalid_argument(
                "TTL must be greater than 0"
            );
        }

        if (ss >> extra) {
            throw std::invalid_argument(
                "SET accepts key, value and optional TTL"
            );
        }
    }

    return {
        CommandType::SET,
        key,
        value,
        ttl
    };
}

    if (command == "GET") {

        if (!(ss >> key) || (ss >> extra)) {
            throw std::invalid_argument(
                "GET requires exactly one key"
            );
        }

        return {CommandType::GET, key, ""};
    }

    if (command == "REMOVE") {

        if (!(ss >> key) || (ss >> extra)) {
            throw std::invalid_argument(
                "REMOVE requires exactly one key"
            );
        }

        return {CommandType::REMOVE, key, ""};
    }

    if (command == "EXISTS") {

        if (!(ss >> key) || (ss >> extra)) {
            throw std::invalid_argument(
                "EXISTS requires exactly one key"
            );
        }

        return {CommandType::EXISTS, key, ""};
    }

    throw std::invalid_argument("Unknown command");
}