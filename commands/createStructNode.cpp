#include "commands/createStructNode.hpp"

namespace command {

bool CreateStructNode::execute() {
    graph::Node* node = _userFunc->graph.createNode(_schemaName, _nodeName);
    if (!node) {
        return false;
    }

    _createdNodeId = node->uniqueId();
    return true;
}

void CreateStructNode::undo() {
    _userFunc->graph.deleteNode(_createdNodeId);
}

void CreateStructNode::redo() {
    _userFunc->graph.createNodeWithId(_createdNodeId, _schemaName, _nodeName);
}

}