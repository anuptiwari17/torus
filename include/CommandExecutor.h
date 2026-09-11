#pragma once

#include <string>

#include "CommandParser.h"
#include "KeyValueStore.h"

class CommandExecutor {
private:
    KeyValueStore& store;

public:

//explicit ka matlab => don't automatically convert other things into my class, make the programmer explicitly say they want to construct this object
    explicit CommandExecutor(KeyValueStore& store);

    std::string execute(const Command& command);
};