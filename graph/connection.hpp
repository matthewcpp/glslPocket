#pragma once

#include <cstddef>

namespace graph {

class Node;

struct Connection {
    Connection() = default;
    Connection(Node* fromNode, size_t fromPortIndex, Node* toNode, size_t toPortIndex)
        : fromNode(fromNode), fromPortIndex(fromPortIndex), toNode(toNode), toPortIndex(toPortIndex) {}

    Node* fromNode;
    size_t fromPortIndex;
    Node* toNode;
    size_t toPortIndex;
};

}