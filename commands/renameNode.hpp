#pragma once

#include "commands/command.hpp"

#include "graph/node.hpp"
#include "graph/userFunction.hpp"

namespace command {

class RenameNode : public Command {
public:
    RenameNode(graph::UserFunction* userFunc, graph::Node* node, const std::string newName);

    virtual bool execute() override;
    virtual void undo() override;
    virtual void redo() override;

private:
    graph::UserFunction* _userFunc;
    graph::NodeTypeId _nodeId;
    std::string _existingName;
    std::string _newName;
};

}