#include "graph.hpp"

namespace graph {

Node* Graph::createNode(const std::string& nodeType) {
    auto* node_ptr = _nodeRegistry.createNode(nodeType);

    if (node_ptr) {
        _nodes.emplace_back().reset(node_ptr);
    }

    return node_ptr;
}

Node* Graph::createNodeForType(const std::string& typeName) {
    auto* node_ptr = _nodeRegistry.createNodeForType(typeName);

    if (node_ptr) {
        _nodes.emplace_back().reset(node_ptr);
    }

    return node_ptr;
}

Node* Graph::findNodeByName(const std::string& name) {
    auto result = std::find_if(_nodes.begin(), _nodes.end(), [&name](const std::unique_ptr<Node>& n) {
        return n.get()->name() == name;
    });

    return result != _nodes.end() ? result->get() : nullptr;
}

Connection* Graph::connect(Node* fromNode, size_t fromPortIndex, Node* toNode, size_t toPortIndex) {
    auto connection = std::make_unique<Connection>(fromNode, fromPortIndex, toNode, toPortIndex);
    auto* c = connection.get();
    _connections.emplace_back(std::move(connection));

    fromNode->setOutputConnection(fromPortIndex, c);
    toNode->setInputConnection(toPortIndex, c);

    return c;
}

}