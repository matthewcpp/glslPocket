#include "commands/nodeConnections.hpp"

namespace command {

void NodeConnections::gatherForNewConnection(graph::NodeUniqueId toNode, size_t toPortIndex) {
    graph::Node* to = _graph.getNodeById(toNode);
    if (!to) {
        return;
    }

    const auto& inputs = to->inputs();

    if (inputs[0].connection) {

    }
}

void NodeConnections::add(const graph::Connection* connection) {
    auto& info = _connections.emplace_back();
    info.id = connection->uniqueId();
    info.fromNode = connection->fromNode->uniqueId();
    info.fromPortIndex = connection->fromPortIndex;
    info.toNode = connection->toNode->uniqueId();
    info.toPortIndex = connection->toPortIndex;
}

void NodeConnections::create() {
    for (const auto& info : _connections) {
        _graph.createConnectionWithId(info.id, info.fromNode, info.fromPortIndex, info.toNode, info.toPortIndex);
    }
}

}