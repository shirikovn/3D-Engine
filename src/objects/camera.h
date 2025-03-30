#pragma once

#include <iostream>

#include "Linalg.h"
#include "primitives/Polygon.h"
#include "util.h"

namespace Render3D {
class Camera {
public:
    Camera(const Vector3& eye, const Vector3& target, float camera_width, float camera_height, float near = 1.0)
    : eye_(eye), target_(target), camera_width_(camera_width), camera_height_(camera_height), near_(near) {
        view_matrix_ = computeViewMatrix();
    }

    PolygonAttributes transformToNormalizedSpace(const Polygon& polygon) const {
        PolygonAttributes attr = projectOnScreen(polygon);

        Polygon2D& res = attr.projectionOnScreen; 

        res.p1(0) = (res.p1(0) + camera_width_ / 2) / camera_width_;
        res.p1(1) = (res.p1(1) + camera_height_ / 2) / camera_height_;

        res.p2(0) = (res.p2(0) + camera_width_ / 2) / camera_width_;
        res.p2(1) = (res.p2(1) + camera_height_ / 2) / camera_height_;

        res.p3(0) = (res.p3(0) + camera_width_ / 2) / camera_width_;
        res.p3(1) = (res.p3(1) + camera_height_ / 2) / camera_height_;

        return attr;
    }

private:
    Matrix4 computeViewMatrix() const {
        Vector3 z = -(target_ - eye_).normalized();
        Vector3 y = Util::calculateOrthogonalComponentToVector(Vector3(0, 0, 1), -z).normalized();
        Vector3 x = y.cross(-z);

        Matrix4 view = Matrix4::Identity();
        view.block<1, 3>(0, 0) = x;
        view.block<1, 3>(1, 0) = y;
        view.block<1, 3>(2, 0) = z;

        view(0, 3) = -x.dot(eye_);
        view(1, 3) = -y.dot(eye_);
        view(2, 3) = -z.dot(eye_);
    
        return view;
    }

    Polygon transfromToCameraCoordinates(const Polygon& polygon) const {
        Polygon res_polygon(polygon);

        // NOTE use marix mult is faste
        res_polygon.p1 = Util::shrinkToVec3(view_matrix_ * Util::expandToVec4(polygon.p1));
        res_polygon.p2 = Util::shrinkToVec3(view_matrix_ * Util::expandToVec4(polygon.p2));
        res_polygon.p3 = Util::shrinkToVec3(view_matrix_ * Util::expandToVec4(polygon.p3));

        return res_polygon;
    }

    PolygonAttributes projectOnScreen(const Polygon& polygon) const {
        Polygon transformed_polygon = transfromToCameraCoordinates(polygon);

        Polygon2D res_polygon {
            .p1 = Vector2(near_ * transformed_polygon.p1(0) / - transformed_polygon.p1(2), near_ * transformed_polygon.p1(1) / - transformed_polygon.p1(2)),
            .p2 = Vector2(near_ * transformed_polygon.p2(0) / - transformed_polygon.p2(2), near_ * transformed_polygon.p2(1) / - transformed_polygon.p2(2)),
            .p3 = Vector2(near_ * transformed_polygon.p3(0) / - transformed_polygon.p3(2), near_ * transformed_polygon.p3(1) / - transformed_polygon.p3(2)),
        };

        res_polygon.color = polygon.color;

        PolygonDepth depths{
            .p1 = -transformed_polygon.p1(2),
            .p2 = -transformed_polygon.p2(2),
            .p3 = -transformed_polygon.p3(2),
        };

        return {res_polygon, depths};
    }

    Vector3 eye_, target_;
    float   near_;
    float   camera_width_, camera_height_;
    Matrix4 view_matrix_;
};
}  // namespace Render3D
