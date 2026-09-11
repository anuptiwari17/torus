#include <iostream>
#include <string>

#include "KeyValueStore.h"
#include "CommandParser.h"
#include "CommandExecutor.h"

int main() {
    KeyValueStore store;
    CommandParser parser;
    CommandExecutor executor(store);

    std::string input;

    std::cout << "Mini Redis Server\n";
    std::cout << "Type commands or EXIT to quit.\n";

    while (true) {
        std::cout << "> ";

        if (!std::getline(std::cin, input)) {
            break;
        }

        if (input == "EXIT") {
            break;
        }

        try {
            Command command = parser.parse(input);
            std::string response = executor.execute(command);

            std::cout<<response<<'\n';
        }
        catch (const std::exception& e) {
            std::cout<<"ERR "<<e.what()<<'\n';
        }
    }

    return 0;
}