#pragma once

#include "commands/command.hpp"

#include "graph/userFunction.hpp"

namespace command {

class CreateStructNode : public Command {
public:
    CreateStructNode(graph::UserFunction* userFunc, const std::string& schemaName, const std::string& nodeName)
        :_userFunc(userFunc), _schemaName(schemaName), _nodeName(nodeName) {}

    virtual bool execute() override;
    virtual void undo() override;
    virtual void redo() override;

    graph::NodeUniqueId createdNodeId() const { return _createdNodeId; }

private:
    graph::UserFunction* _userFunc;
    std::string _schemaName;
    std::string _nodeName;

    graph::NodeUniqueId _createdNodeId;
};

}