#pragma once

#include "objects/Camera.h"
#include "objects/Mesh.h"

#include <vector>

namespace Render3D {
struct Scene {
    Camera main_camera;
    std::vector<Mesh> objects;
};
} // namespace Render3D
