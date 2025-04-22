#pragma once

#include <vector>
#include "Camera.h"
#include "Mesh.h"
#include "PointLight.h"

namespace Render3D {
struct Scene {
    std::vector<Mesh> meshes;
    std::vector<PointLight> lights;
    Camera camera;
};
} // namespace Render3D
