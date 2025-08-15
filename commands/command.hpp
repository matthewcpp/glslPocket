#pragma once

namespace command {

class Command{
public:
    virtual ~Command() = default;

    virtual bool execute() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;

};

}