#pragma once

#include "commands/command.hpp"

#include "graph/nodeFactory.hpp"
#include "graph/userFunction.hpp"

namespace command {

class CreateNode : public Command {
public:
    CreateNode(graph::UserFunction* userFunc, graph::NodeFactory& nodeFactory, const std::string& nodeType)
        :_userFunc(userFunc), _nodeFactory(nodeFactory), _nodeType(nodeType) {}

    virtual bool execute() override;
    virtual void undo() override;
    virtual void redo() override;

    graph::NodeUniqueId createdNodeId() const { return _createdNodeId; }

private:
    graph::UserFunction* _userFunc;
    graph::NodeFactory& _nodeFactory;
    std::string _nodeType;

    graph::NodeUniqueId _createdNodeId;
};

}