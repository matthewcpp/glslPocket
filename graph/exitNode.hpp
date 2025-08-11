#pragma once

#include "graph/node.hpp"
#include "graph/typeRegistry.hpp"

namespace graph {

class ExitNode : public Node {
public:
    ExitNode(NodeUniqueId uniqueId, TypeRegistry& typeRegistry);
    Node* targetNode = nullptr;

};

}