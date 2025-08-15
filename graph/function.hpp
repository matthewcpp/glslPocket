#pragma once

#include "graph/schema.hpp"
#include "graph/nodeId.hpp"

namespace graph {

class Function : public Schema {
public:
    Function() : Schema("graph::function", GraphdevNodeFunction) {
        addProperty("function::name", std::string());
    }

};

}