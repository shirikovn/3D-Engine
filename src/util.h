#pragma once

#include "Linalg.h"

namespace Render3D::Util {
inline Vector4 expandToVec4(const Vector3& v, float w = 1.0f) {
    return Vector4(v.x(), v.y(), v.z(), w);
}

inline Vector3 shrinkToVec3(const Vector4& v) {
    return Vector3(v.x(), v.y(), v.z());
}

inline Vector3 calculateOrthogonalProjectionOnVector(const Vector3& x, const Vector3& on) {
    return (x.dot(on) / on.dot(on)) * on;
}

inline Vector3 calculateOrthogonalComponentToVector(const Vector3& x, const Vector3& to) {
    return x - (x.dot(to) / to.dot(to)) * to;
}
} // namespace Render3D::Util
