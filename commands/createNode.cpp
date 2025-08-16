#include "commands/createNode.hpp"

namespace command {

bool CreateNode::execute() {
    graph::Node* node = _nodeFactory.createNode(_userFunc->graph, _nodeType);
    if (!node) {
        return false;
    }

    _createdNodeId = node->uniqueId();
    return true;
}

void CreateNode::undo() {
    _userFunc->graph.deleteNode(_createdNodeId);
}

void CreateNode::redo() {
    _nodeFactory.createNodeWithId(_userFunc->graph, _createdNodeId, _nodeType);
}

}