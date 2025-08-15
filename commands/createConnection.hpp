#pragma once

#include "commands/command.hpp"
#include "commands/nodeConnections.hpp"

#include "graph/userFunction.hpp"

namespace command {

class CreateConnection : public Command {
public:
    CreateConnection(graph::UserFunction* userFunc, graph::Node* fromNode, size_t fromPortIndex, graph::Node* toNode, size_t toPortIndex)
        : _userFunc(userFunc), _fromNode(fromNode->uniqueId()), _fromPortIndex(fromPortIndex), _toNode(toNode->uniqueId()), _toPortIndex(toPortIndex), _nodeConnections(userFunc->graph) {}

    virtual bool execute() override;
    virtual void undo() override;
    virtual void redo() override;

private:
    graph::UserFunction* _userFunc;
    graph::NodeUniqueId _fromNode;
    size_t _fromPortIndex;
    graph::NodeUniqueId _toNode;
    size_t _toPortIndex;

    graph::ConnectionUniqueId _createdConnectionId;
    NodeConnections _nodeConnections;
};

}