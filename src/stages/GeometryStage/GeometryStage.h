#pragma once

#include <vector>

#include "core/primitives/Polygon.h"
#include "scene/Scene.h"
#include "scene/Camera.h"

namespace Render3D {
class GeometryStage {
public:
    std::vector<Polygon> process(const Scene& scene) const;
private:
    std::vector<Polygon> transformToWorldSpace(const Scene& scene) const;
    void transformToCameraSpace(std::vector<Polygon>& polygons, const Camera& camera) const;
    void transformToScreenSpace(std::vector<Polygon>& polygons, const Camera& camera) const;
    void transformToNormalizedSpace(std::vector<Polygon>& polygons, const Camera& camera) const;

    bool backFaceCulling(const Polygon& polygon, const Camera& camera) const;

    Matrix4 computeCameraViewMatrix(const Camera& camera) const;
};
}
