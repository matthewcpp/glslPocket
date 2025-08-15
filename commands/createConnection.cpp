#include "commands/createConnection.hpp"

namespace command {

bool CreateConnection::execute() {
    const graph::Connection* connection = _userFunc->graph.connect(_fromNode, _fromPortIndex, _toNode, _toPortIndex);

    if (!connection) {
        return false;
    }

    _createdConnectionId = connection->uniqueId();
    return true;
}

}