#pragma once

#include "Linalg.h"
#include "core/primitives/Color.h"

namespace Render3D {
struct Fragment {
    float depth;
    Color color;
    Vector3 normal;
    Vector3 world_position;
};
};
