#pragma once

#include "Linalg.h"
#include "core/primitives/Vertex.h"
#include "core/primitives/Polygon.h"

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

inline void transformVertexWithMatrix(Vertex& v, const Matrix4& transform_matrix) {
    v.position = Util::shrinkToVec3(transform_matrix * Util::expandToVec4(v.position));
}

inline void transformNormalWithMatrix(Vertex& v, const Matrix4& transform_matrix) {
    // FIXME преобразование для нормали считать по-другому, работает, пока нет скейла
    v.normal = Util::shrinkToVec3(transform_matrix * Util::expandToVec4(v.normal));
}

inline void trasformPolygonNormalsWithMatrix(Polygon& polygon, const Matrix4& transform_matrix) { 
    transformNormalWithMatrix(polygon.p1,transform_matrix);
    transformNormalWithMatrix(polygon.p2,transform_matrix);
    transformNormalWithMatrix(polygon.p3,transform_matrix);
}

inline void trasformPolygonWithMatrixNoNormals(Polygon& polygon, const Matrix4& transform_matrix) { 
    transformVertexWithMatrix(polygon.p1,transform_matrix);
    transformVertexWithMatrix(polygon.p2,transform_matrix);
    transformVertexWithMatrix(polygon.p3,transform_matrix);
}
} // namespace Render3D::Util
