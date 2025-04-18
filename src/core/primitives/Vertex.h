#pragma once

#include "Linalg.h"
#include "Color.h"

#include <stdexcept>
#include <vector>

namespace Render3D {
class Vertex {
public:
    Vector3 position;
    Vector3 normal;
    Color base_color;

    bool position_in_world_set;

    Vector3 GetPositionInWorld() const {
        if (position_in_world_set) {
            return position_in_world;
        }

        throw std::runtime_error("World position is not set");
    }

    void SetPostionInWorld(Vector3 pos) {
        position_in_world_set = true;
        position_in_world = pos;
    }
private:
    Vector3 position_in_world;
};
}
