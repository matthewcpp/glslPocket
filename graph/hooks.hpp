#pragma once

#include "graph/callback.hpp"

namespace graph {

class Node;
class Connection;

class Hooks{
public:
    Callback<Node*> nodeCreated;
    Callback<Node*> nodeDeleted;
    Callback<Connection*> connectionCreated;
    Callback<Connection*> connectionDeleted;
};

}
