#pragma once

#include "Linalg.h"

namespace Render3D {
class Plane {
public:
    Vector3 normal;
    float d;

    Plane(const Vector3& n, float d_) : normal(n.normalized()), d(d_) {}

    float distance(const Vector3& point) const {
        return normal.dot(point) + d;
    }

    bool isInside(const Vector3& point) const {
        return distance(point) >= 0.0f;
    }

    Vector3 intersect(const Vector3& a, const Vector3& b) const {
        float da = distance(a);
        float db = distance(b);
        float t = da / (da - db);
        return a + t * (b - a);
    }
};
}
