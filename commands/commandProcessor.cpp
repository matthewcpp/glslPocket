#include "commands/commandProcessor.hpp"

namespace command {

const Command* Processor::last() const {
    if (_command_index == 0) {
        return nullptr;
    }

    return _command_history[_command_index - 1].get();
}

bool Processor::execute(Command* command) {
    bool result = command->execute();
    if (!result) {
        delete command;
        return false;
    }

    // clear any commands that came after
    if (_command_index < _command_history.size()) {
        _command_history.erase(_command_history.begin() + _command_index, _command_history.end());
    }

    _command_history.emplace_back().reset(command);
    _command_index = _command_history.size();

    return true;
}

void Processor::undo() {
    if (_command_index == 0) {
        return;
    }

    _command_history[--_command_index]->undo();
}

void Processor::redo() {
    if (_command_index >= _command_history.size()) {
        return;
    }

    _command_history[_command_index++]->redo();
}

}