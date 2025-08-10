#include "graph/enterNode.hpp"

#include "graph/nodeId.hpp"

namespace graph {

EnterNode::EnterNode(TypeRegistry& typeRegistry)
    : Node(GraphdevNodeEnter, "Enter")
{

}

Node* enterNode(TypeRegistry& typeRegistry) {
    return new EnterNode(typeRegistry);
}

}