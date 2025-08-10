#pragma once

#include "graph/node.hpp"
#include "graph/typeRegistry.hpp"

namespace graph {

class EnterNode : public Node {
public:
    EnterNode(NodeUniqueId uniqueId, TypeRegistry& typeRegistry);
    Node* targetNode = nullptr;

};

Node* enterNode(NodeUniqueId uniqueId, TypeRegistry& typeRegistry);

}