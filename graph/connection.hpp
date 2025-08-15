#pragma once

#include <cstddef>
#include <cstdint>

namespace graph {

class Node;

/** A unique identifer for this node in it's graph. */
typedef uint32_t ConnectionUniqueId;

struct Connection {
    Connection() = default;
    Connection(ConnectionUniqueId uniqueId, Node* fromNode, size_t fromPortIndex, Node* toNode, size_t toPortIndex)
        : _uniqueId(uniqueId), fromNode(fromNode), fromPortIndex(fromPortIndex), toNode(toNode), toPortIndex(toPortIndex) {}

    Node* fromNode;
    size_t fromPortIndex;
    Node* toNode;
    size_t toPortIndex;

    ConnectionUniqueId uniqueId() const { return _uniqueId; }

private:
    ConnectionUniqueId _uniqueId;
};

}