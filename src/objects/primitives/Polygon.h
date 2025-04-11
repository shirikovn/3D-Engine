#pragma once

#include "Linalg.h"
#include "buffers/ImageBuffer.h"

namespace Render3D {
struct Polygon {
    Color color;

    Vector3 p1;
    Vector3 p2;
    Vector3 p3;

    static Color BaseColor;
};

struct Polygon2D {
    Color color;

    Vector2 p1;
    Vector2 p2;
    Vector2 p3;
};

struct PolygonDepth {
    float p1;
    float p2;
    float p3;
};

struct PolygonAttributes {
    Polygon2D projectionOnScreen;
    PolygonDepth depths;
};

inline Color Polygon::BaseColor{210, 180, 140};
} // namespace Render3D
