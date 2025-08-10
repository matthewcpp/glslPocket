#pragma once

#include "graph/node.hpp"
#include "graph/typeRegistry.hpp"

namespace graphdev {

class EnterNode : public Node {
public:
    EnterNode(TypeRegistry& typeRegistry);
    Node* targetNode = nullptr;

};

Node* enterNode(TypeRegistry& typeRegistry);

}