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

}