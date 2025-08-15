#include "commands/commandProcessor.hpp"

namespace command {

bool Processor::execute(Command* command) {
    bool result = command->execute();
    if (result) {
        _command_history.push_back(command);
    } else {
        delete command;
    }

    return result;
}

}