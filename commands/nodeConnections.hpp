#pragma once

#include "graph/graph.hpp"

#include <vector>

namespace command {

class NodeConnections {
public:
    NodeConnections(graph::Graph& graph) : _graph(graph) {}

    void gatherForNewConnection(graph::NodeUniqueId toNode, size_t toPortIndex);
    void create();

private:
    void add(const graph::Connection* connection);

private:
    struct ConnectionInfo {
        graph::ConnectionUniqueId id;
        graph::NodeUniqueId fromNode;
        size_t fromPortIndex;
        graph::NodeUniqueId toNode;
        size_t toPortIndex;
    };

private:
    graph::Graph& _graph;
    std::vector<ConnectionInfo> _connections;
};

}