#pragma once

#include "graph/schema.hpp"
#include "graph/nodeId.hpp"

namespace graph {

class Operator : public Schema {
public:
    Operator() : Schema("graph::operator", GraphdevNodeOperator) {
        addProperty("operator::op", std::string());
    }

};

}