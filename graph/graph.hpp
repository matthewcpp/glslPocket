#pragma once

#include "connection.hpp"
#include "node.hpp"
#include "nodeRegistry.hpp"

#include <functional>
#include <memory>
#include <vector>

namespace graph {

class Graph{
public:
    Graph(NodeRegistry& nodeRegistry) : _nodeRegistry(nodeRegistry) {}

public:
    Node* createNode(const std::string& nodeType);
    Node* createNodeForType(const std::string& typeName);

    using NodeItrFunc = std::function<void(const Node*)>;
    void iterateNodes(NodeItrFunc func) const;

    using ConnectionItrFunc = std::function<void(const Connection* connection)>;
    void iterateConnections(ConnectionItrFunc func) const;

    Node* findNodeByName(const std::string& name);

    Connection* connect(Node* fromNode, size_t fromPortIndex, Node* toNode, size_t toPortIndex);

private:
    std::vector<std::unique_ptr<Node>> _nodes;
    std::vector<std::unique_ptr<Connection>> _connections;

    NodeRegistry& _nodeRegistry;
    NodeUniqueId _nextUniqueId = 0;
};

}