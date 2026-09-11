#include "CommandParser.h"
#include <sstream>
#include <stdexcept>
#include<algorithm>

//this anonnymous nampespacemeans ye helper is private to this .cpp file
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





Command CommandParser::parse(const std::string& input){
    std::stringstream ss(input);

    std::string command;
    std::string key;
    std::string value;

    ss >> command;

    if(command == "SET"){
        ss>>key>>value;
        return {CommandType::SET, key, value};
    }

    if(command== "GET"){
        ss>>key;
        return {CommandType::GET, key, ""};
    }

    if(command == "DELETE"){
        ss>>key;
        return {CommandType::DELETE, key, ""};
    }

    if(command == "EXISTS"){
        ss>>key;
        return {CommandType::EXISTS, key, ""};
    }

    throw std::invalid_argument("Unknown command");
}