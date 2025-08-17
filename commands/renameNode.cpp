#include "commands/renameNode.hpp"

namespace command {

RenameNode::RenameNode(graph::UserFunction* userFunc, graph::Node* node, const std::string newName)
    : _userFunc(userFunc), _nodeId(node->uniqueId()), _newName(newName)
{}

bool RenameNode::execute() {
    graph::Node* node = _userFunc->graph.getNodeById(_nodeId);

    if (node->flags | (graph::NodeFlags::PlatformDependant | graph::NodeFlags::PlatformDependant)) {
        return false;
    }

    _existingName = node->name();

    node->setName(_newName);

    return true;
}

void RenameNode::undo() {
    graph::Node* node = _userFunc->graph.getNodeById(_nodeId);
    node->setName(_existingName);
}

void RenameNode::redo() {
    graph::Node* node = _userFunc->graph.getNodeById(_nodeId);
    node->setName(_newName);
}

}