#pragma once

#include <vector>

#include "primitives/primitives.h"
#include "objects/camera.h"
#include "objects/mesh.h"

struct World {
    Camera main_camera;
    std::vector<Mesh> mess;
};
