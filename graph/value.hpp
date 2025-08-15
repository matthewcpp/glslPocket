#pragma once

#include "graph/property.hpp"
#include "graph/schema.hpp"
#include "graph/nodeId.hpp"

namespace graph {

class Value : public Schema {
public:
    Value() : Schema("graph::value", GraphdevNodeValue) {
        addProperty("value::value", Property::ValueType());
    }

};

}