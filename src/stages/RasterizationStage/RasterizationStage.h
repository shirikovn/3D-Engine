#pragma once

#include <vector>

#include "Fragment.h"
#include "core/primitives/Polygon.h"
#include "ZBuffer.h"
#include "FragmentBuffer.h"

namespace Render3D {
class RasterizationStage {
public:
    struct Resolution {
        unsigned int width;
        unsigned int height;
    };

    FragmentBuffer process(std::vector<Polygon>& polygons, Resolution res) const;
private:
    unsigned threads_num = 32;

    float edgeFunction(const Vector3& a, const Vector3& b, const Vector3& c) const;
    Vector3 calculateBarycentricCoordinates(const Vector3& point, const Polygon& polygon) const;
    float calculatePointDepth(const Vector3& barycentric_coordinates, const Polygon& polygon) const;
    void transformToRasterSpace(Polygon& polygon) const;

    void rasterizePolygon(const std::vector<Polygon>& polygons, FragmentBuffer& frag_buffer, ZBuffer& z_buffer, Resolution res, unsigned ind) const;

    void transformPolygonToRasterSpace(Polygon& polygon, Resolution res) const;
};
}
