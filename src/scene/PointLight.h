#pragma once

#include "Linalg.h"
#include "core/primitives/Color.h"

namespace Render3D {
struct PointLight {
    Vector3 position;
    Color color;
    float intensity;
};
}
