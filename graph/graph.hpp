#pragma once

#include "graph/connection.hpp"
#include "graph/hooks.hpp"
#include "graph/node.hpp"
#include "graph/schemaRegistry.hpp"

#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>

namespace graph {

class Graph{
public:
    Graph(SchemaRegistry& schemaRegistry, Hooks& hooks) : _schemaRegistry(schemaRegistry), _hooks(hooks) {}

public:
    Node* createNode(const std::string& schemaName, const std::string& nodeName);
    Node* createNodeWithId(NodeUniqueId, const std::string& schemaName, const std::string& nodeName);
    Node* createNodeForType(const Type* type, const std::string& nodeName);

    bool deleteNode(NodeUniqueId id);

    using NodeItrFunc = std::function<void(const Node*)>;
    void iterateNodes(NodeItrFunc func) const;

    using ConnectionItrFunc = std::function<void(const Connection* connection)>;
    void iterateConnections(ConnectionItrFunc func) const;

    Node* findNodeByName(const std::string& name);
    Node* getNodeById(NodeUniqueId id);

    const Connection* createConnection(Node* fromNode, size_t fromPortIndex, Node* toNode, size_t toPortIndex);
    const Connection* createConnection(NodeUniqueId fromNode, size_t fromPortIndex, NodeUniqueId toNode, size_t toPortIndex);
    const Connection* createConnectionWithId(ConnectionUniqueId id, NodeUniqueId fromNode, size_t fromPortIndex, NodeUniqueId toNode, size_t toPortIndex);
    bool deleteConnection(ConnectionUniqueId id);
    bool deleteConnection(Connection* connection);

private:
    Node* createNewNode(NodeUniqueId nodeId, const Schema* schema, const std::string& nodeName);
    Connection* createNewConnection(ConnectionUniqueId connectionId, Node* fromNode, size_t fromPortIndex, Node* toNode, size_t toPortIndex);

private:
    std::unordered_map<NodeUniqueId, std::unique_ptr<Node>> _nodesById;
    std::unordered_map<ConnectionUniqueId, std::unique_ptr<Connection>> _connectionsById;
    Hooks& _hooks;
    SchemaRegistry& _schemaRegistry;
    NodeUniqueId _nextNodeUniqueId = 0;
    ConnectionUniqueId _nextConnectionUniqueId = 0;
};

}