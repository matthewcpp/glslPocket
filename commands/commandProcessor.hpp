#pragma once

#include "commands/command.hpp"

#include <vector>

namespace command {

class Processor {
public:
    /** Command processor will manage the lifetime of the command object */
    bool execute(Command* command);

    const Command* last() const { return !_command_history.empty() ? _command_history.back() : nullptr; }

private:
    std::vector<Command*> _command_history;
};

}