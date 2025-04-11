#pragma once

#include "Linalg.h"
#include "primitives/Polygon.h"

#include <vector>

namespace Render3D {
struct Mesh {
    std::vector<Polygon> polygons;
    Matrix4 transform_matrix;
};
} // namespace Render3D
