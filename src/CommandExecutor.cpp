#include "CommandExecutor.h"

CommandExecutor::CommandExecutor(KeyValueStore& store)
    : store(store) {
}

std::string CommandExecutor::execute(const Command& command) {
    switch (command.type) {

        case CommandType::SET:
            store.set(command.key, command.value);
            return "OK";

        case CommandType::GET:
            return store.get(command.key);

        case CommandType::DELETE:
            return store.remove(command.key) ? "1" : "0";

        case CommandType::EXISTS:
            return store.exists(command.key) ? "1" : "0";
    }

    return "ERR unknown command";
}