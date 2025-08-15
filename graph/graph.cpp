#include "graph.hpp"

namespace graph {

Node* Graph::createNode(const std::string& schemaName, const std::string& nodeName) {
    return createNewNode(++_nextNodeUniqueId, _schemaRegistry.get(schemaName), nodeName);
}

Node* Graph::createNodeWithId(NodeUniqueId nodeId, const std::string& schemaName, const std::string& nodeName) {
    if (_nodesById.find(nodeId) != _nodesById.end()) {
        return nullptr;
    }

    return createNewNode(nodeId, _schemaRegistry.get(schemaName), nodeName);
}

Node* Graph::createNodeForType(const Type* type, const std::string& nodeName) {
    return createNewNode(++_nextNodeUniqueId, _schemaRegistry.getForType(type), nodeName);
}

Node* Graph::createNewNode(NodeUniqueId nodeId, const Schema* schema, const std::string& nodeName) {
    if (!schema) {
        return nullptr;
    }

    auto& node = _nodesById[nodeId];
    node = std::make_unique<Node>(nodeId, nodeName);
    schema->apply(node.get());

    _hooks.nodeCreated(node.get());

    return node.get();
}

bool Graph::deleteNode(NodeUniqueId id) {
    auto nodeResult = _nodesById.find(id);

    if (nodeResult == _nodesById.end()) {
        return false;
    }

    Node* node = nodeResult->second.get();

    for (auto & input : node->_inputs) {
        if (input.connection) {
            deleteConnection(const_cast<Connection*>(input.connection));
        }
    }

    for (auto& output : node->_outputs) {
        for (auto connection : output.connections) {
            deleteConnection(const_cast<Connection*>(connection));
        }
    }

    _hooks.nodeDeleted(node);

    _nodesById.erase(id);

    return true;
}

Node* Graph::findNodeByName(const std::string& name) {
    for (const auto& node : _nodesById) {
        if (node.second->name() == name) {
            return node.second.get();
        }
    }

    return nullptr;
}

Node* Graph::getNodeById(NodeUniqueId id) {
    auto result = _nodesById.find(id);

    return result != _nodesById.end() ? result->second.get() : nullptr;
}

void Graph::iterateNodes(NodeItrFunc func) const {
    for (const auto& node : _nodesById) {
        func(node.second.get());
    }
}

void Graph::iterateConnections(ConnectionItrFunc func) const {
    for (const auto& conn : _connectionsById) {
        func(conn.second.get());
    }
}

const Connection* Graph::createConnection(Node* fromNode, size_t fromPortIndex, Node* toNode, size_t toPortIndex) {
    return createNewConnection(_nextConnectionUniqueId++, fromNode, fromPortIndex, toNode, toPortIndex);
}

const Connection* Graph::createConnection(NodeUniqueId fromNode, size_t fromPortIndex, NodeUniqueId toNode, size_t toPortIndex) {
    return createConnectionWithId(_nextConnectionUniqueId++, fromNode, fromPortIndex, toNode, toPortIndex);
}

const Connection* Graph::createConnectionWithId(ConnectionUniqueId connectionId, NodeUniqueId fromNode, size_t fromPortIndex, NodeUniqueId toNode, size_t toPortIndex) {
    if (_connectionsById.find(connectionId) != _connectionsById.end()) {
        return nullptr;
    }

    auto fromNodeResult = _nodesById.find(fromNode);
    auto toNodeResult = _nodesById.find(toNode);

    if (fromNodeResult == _nodesById.end() || toNodeResult == _nodesById.end()) {
        return nullptr;
    }

    return createNewConnection(connectionId, fromNodeResult->second.get(), fromPortIndex, toNodeResult->second.get(), toPortIndex);
}

Connection* Graph::createNewConnection(ConnectionUniqueId connectionId, Node* fromNode, size_t fromPortIndex, Node* toNode, size_t toPortIndex) {
    auto& connection = _connectionsById[connectionId];
    connection = std::make_unique<Connection>(connectionId, fromNode, fromPortIndex, toNode, toPortIndex);

    auto& targetInput = toNode->_inputs[toPortIndex];
    if (targetInput.connection){
        deleteConnection(const_cast<Connection*>(targetInput.connection));
    }

    fromNode->_outputs[fromPortIndex].connections.push_back(connection.get());
    targetInput.connection = connection.get();

    _hooks.connectionCreated(connection.get());
    return connection.get();
}

bool Graph::deleteConnection(ConnectionUniqueId id) {
    auto result = _connectionsById.find(id);

    if (result != _connectionsById.end()) {
        return deleteConnection(result->second.get());
    }

    return false;
}

bool Graph::deleteConnection(Connection* connection) {
    _hooks.connectionDeleted(connection);

    connection->toNode->_inputs[connection->toPortIndex].connection = nullptr;

    auto& outputPort = connection->fromNode->_outputs[connection->fromPortIndex];
    auto target = std::find_if(outputPort.connections.begin(), outputPort.connections.end(), [connection](const Connection* c){
        return connection == c;
    });

    if (target != outputPort.connections.end()) {
        outputPort.connections.erase(target);
    }

    _connectionsById.erase(connection->uniqueId());

    return true;
}

}