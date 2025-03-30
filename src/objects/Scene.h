#pragma once

#include <vector>
#include "objects/Camera.h"
#include "objects/Mesh.h"

namespace Render3D {
struct Scene {
    Camera main_camera;
    std::vector<Mesh> objects;
};
}
