#pragma once

#include "commands/command.hpp"

#include <vector>

namespace command {

class Processor {
public:
    /** Command processor will manage the lifetime of the command object */
    bool execute(Command* command);
    void undo();
    void redo();

    const Command* last() const;

private:
    std::vector<Command*> _command_history;
    size_t _command_index = 0;
};

}