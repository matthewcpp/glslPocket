#include "graph/exitNode.hpp"

#include "graph/nodeId.hpp"

namespace graph {

ExitNode::ExitNode(NodeUniqueId uniqueId, TypeRegistry& typeRegistry)
    : Node(uniqueId, GraphdevNodeExit, "Exit")
{

}



}