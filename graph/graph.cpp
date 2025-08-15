#include "graph.hpp"

namespace graph {

Node* Graph::createNode(const std::string& schemaName, const std::string& nodeName) {
    return createNodeWithSchema(_schemaRegistry.get(schemaName), nodeName);
}

Node* Graph::createNodeForType(const Type* type, const std::string& nodeName) {
    return createNodeWithSchema(_schemaRegistry.getForType(type), nodeName);
}

Node* Graph::createNodeWithSchema(const Schema* schema, const std::string& nodeName) {
    if (!schema) {
        return nullptr;
    }

    Node* node = new Node(++_nextNodeUniqueId, nodeName);
    schema->apply(node);

    _nodes.emplace_back().reset(node);
    _nodesById[node->uniqueId()] = node;

    return node;
}

Node* Graph::findNodeByName(const std::string& name) {
    auto result = std::find_if(_nodes.begin(), _nodes.end(), [&name](const std::unique_ptr<Node>& n) {
        return n.get()->name() == name;
    });

    return result != _nodes.end() ? result->get() : nullptr;
}

Node* Graph::getNodeById(NodeUniqueId id) {
    auto result = _nodesById.find(id);

    return result != _nodesById.end() ? result->second : nullptr;
}

void Graph::iterateNodes(NodeItrFunc func) const {
    for (const auto& node : _nodes) {
        func(node.get());
    }
}

void Graph::iterateConnections(ConnectionItrFunc func) const {
    for (const auto& conn : _connections) {
        func(conn.get());
    }
}

const Connection* Graph::connect(Node* fromNode, size_t fromPortIndex, Node* toNode, size_t toPortIndex) {
    auto connection = std::make_unique<Connection>(++_nextConnectionUniqueId, fromNode, fromPortIndex, toNode, toPortIndex);
    auto* c = connection.get();
    _connections.emplace_back(std::move(connection));
    _connectionsById[c->uniqueId()] = c;

    fromNode->addOutputConnection(fromPortIndex, c);
    toNode->setInputConnection(toPortIndex, c);

    return c;
}

const Connection* Graph::connect(NodeUniqueId fromNode, size_t fromPortIndex, NodeUniqueId toNode, size_t toPortIndex) {
    auto fromNodeResult = _nodesById.find(fromNode);
    auto toNodeResult = _nodesById.find(toNode);

    if (fromNodeResult == _nodesById.end() || toNodeResult == _nodesById.end()) {
        return nullptr;
    }

    return connect(fromNodeResult->second, fromPortIndex, toNodeResult->second, toPortIndex);
}

}