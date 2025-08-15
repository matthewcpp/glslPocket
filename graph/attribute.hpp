#pragma once

#include "graph/schema.hpp"
#include "graph/nodeId.hpp"

namespace graph {

class Attribute : public Schema {
public:
    Attribute() : Schema("graph::attribute", GraphdevNodeAttribute) {
        addProperty("attribute::name", std::string());
    }

};

}