#include "graph/enterNode.hpp"

#include "graph/nodeId.hpp"

namespace graphdev {

EnterNode::EnterNode(TypeRegistry& typeRegistry)
    : Node(GraphdevNodeEnter, "Enter")
{

}

Node* enterNode(TypeRegistry& typeRegistry) {
    return new EnterNode(typeRegistry);
}

}