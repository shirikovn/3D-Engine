#pragma once

#include <vector>

#include "primitives/Polygon.h"
#include "Linalg.h"

namespace Render3D {
struct Mesh {
    std::vector<Polygon> polygons;
    Matrix4 transform_matrix;
};
}
