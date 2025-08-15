#pragma once

#include "graph/connection.hpp"
#include "graph/node.hpp"
#include "graph/schemaRegistry.hpp"

#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>

namespace graph {

class Graph{
public:
    Graph(SchemaRegistry& schemaRegistry) : _schemaRegistry(schemaRegistry) {}

public:
    Node* createNode(const std::string& nodeType);
    Node* createNodeForType(const Type* type);

    using NodeItrFunc = std::function<void(const Node*)>;
    void iterateNodes(NodeItrFunc func) const;

    using ConnectionItrFunc = std::function<void(const Connection* connection)>;
    void iterateConnections(ConnectionItrFunc func) const;

    Node* findNodeByName(const std::string& name);

    const Connection* connect(Node* fromNode, size_t fromPortIndex, Node* toNode, size_t toPortIndex);
    const Connection* connect(NodeUniqueId fromNode, size_t fromPortIndex, NodeUniqueId toNode, size_t toPortIndex);

private:
    Node* createNodeWithSchema(const Schema* schema);

private:
    std::vector<std::unique_ptr<Node>> _nodes;
    std::unordered_map<NodeUniqueId, Node*> _nodesById;
    std::vector<std::unique_ptr<Connection>> _connections;
    std::unordered_map<ConnectionUniqueId, Connection*> _connectionsById;

    SchemaRegistry& _schemaRegistry;
    NodeUniqueId _nextNodeUniqueId = 0;
    ConnectionUniqueId _nextConnectionUniqueId = 0;
};

}