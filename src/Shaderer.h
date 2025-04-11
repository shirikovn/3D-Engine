#pragma once

#include "objects/Light.h"
#include "objects/primitives/Polygon.h"

#include <algorithm>
#include <vector>

namespace Render3D {
class Shaderer {
public:
    void shadePolygon(Polygon& polygon) {
        for (const SimpleLight& light : lights_) {
            Vector3 L = light.position.normalized();

            // FIXME should be attribute of polygon? or just method?
            Vector3 edge1 = polygon.p2 - polygon.p1;
            Vector3 edge2 = polygon.p3 - polygon.p1;
            Vector3 normal = edge1.cross(edge2).normalized();

            // FIXME simulate Ambient lighting somewhere else
            float NdotL = std::max(normal.dot(L), 0.2f);
            polygon.color = Polygon::BaseColor * light.intensity * NdotL;
        }
    }

    void addLight(const SimpleLight& light) {
        lights_.push_back(light);
    }

private:
    std::vector<SimpleLight> lights_;
};
} // namespace Render3D
