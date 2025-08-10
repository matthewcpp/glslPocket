#include "graph/enterNode.hpp"

#include "graph/nodeId.hpp"

namespace graph {

EnterNode::EnterNode(NodeUniqueId uniqueId, TypeRegistry& typeRegistry)
    : Node(uniqueId, GraphdevNodeEnter, "Enter")
{

}

Node* enterNode(NodeUniqueId uniqueId, TypeRegistry& typeRegistry) {
    return new EnterNode(uniqueId, typeRegistry);
}

}