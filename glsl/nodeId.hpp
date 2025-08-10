#pragma once

namespace graphdev::glsl {

enum GlslNodeId {
    GlslNodeFloat = 1000,
    GlslNodeVec,
    GlslNodeVec2,
    GlslNodeVec3,
    GlslNodeVec4,

    GlslNodeOperator,
    GlslNodeBuiltin,
    GlslNodeSwizzle
};

}
