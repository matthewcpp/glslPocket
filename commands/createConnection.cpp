#include "commands/createConnection.hpp"

namespace command {

bool CreateConnection::execute() {
    _nodeConnections.gatherForNewConnection(_toNode, _toPortIndex);
    const graph::Connection* connection = _userFunc->graph.createConnection(_fromNode, _fromPortIndex, _toNode, _toPortIndex);

    if (!connection) {
        return false;
    }

    _createdConnectionId = connection->uniqueId();
    return true;
}

void CreateConnection::undo() {
    _userFunc->graph.deleteConnection(_createdConnectionId);
    _nodeConnections.create();
}

void CreateConnection::redo() {
    _userFunc->graph.createConnectionWithId(_createdConnectionId, _fromNode, _fromPortIndex, _toNode, _toPortIndex);
}

}