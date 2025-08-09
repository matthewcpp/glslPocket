#pragma once

#include "graphdev/node.hpp"
#include "graphdev/typeRegistry.hpp"

namespace graphdev {

class EnterNode : public Node {
public:
    EnterNode(TypeRegistry& typeRegistry);
    Node* targetNode = nullptr;

};

Node* enterNode(TypeRegistry& typeRegistry);

}