#include "stages/GeometryStage/GeometryStage.h"
#include "util/VectorTransforms.h"
#include "Plane.h"
#include <vector>

namespace Render3D {
std::vector<Polygon> GeometryStage::process(const Scene& scene) const {
    auto res = transformToWorldSpace(scene);

    transformToCameraSpace(res, scene.camera);


    transformToScreenSpace(res, scene.camera);
    transformToNormalizedSpace(res, scene.camera);

    return res;
}

std::vector<Polygon> GeometryStage::transformToWorldSpace(const Scene& scene) const {
    std::vector<Polygon> result;
    for (const auto& mesh : scene.meshes) {
        for (const auto& polygon : mesh.polygons) {
            result.push_back(polygon);
            Polygon& last = result.back(); 
            Util::trasformPolygonWithMatrixNoNormals(last, mesh.model_matrix);
            Util::trasformPolygonNormalsWithMatrix(last, mesh.model_matrix);

            if (!backFaceCulling(last, scene.camera)) {
                result.pop_back();
                continue;
            }

            // TODO function here
            last.p1.SetPostionInWorld(last.p1.position);
            last.p2.SetPostionInWorld(last.p2.position);
            last.p3.SetPostionInWorld(last.p3.position);
        }
    }
    return result;
}

bool GeometryStage::backFaceCulling(const Polygon& polygon, const Camera& camera) const {
    Vector3 normal = (polygon.p2.position - polygon.p1.position).cross(polygon.p3.position - polygon.p1.position).normalized();
    Vector3 camera_dir = -(camera.target_ - camera.eye_).normalized();

    if (normal.dot(camera_dir) >= 0) {
        return true;
    }

    return false;
}

void GeometryStage::transformToCameraSpace(std::vector<Polygon>& polygons, const Camera& camera) const {
    Matrix4 camera_matrix = computeCameraViewMatrix(camera);
    for (auto& polygon : polygons) {
        Util::trasformPolygonWithMatrixNoNormals(polygon, camera_matrix);
    }
}

void GeometryStage::transformToScreenSpace(std::vector<Polygon>& polygons, const Camera& camera) const {
    for (auto& polygon : polygons) {
         // FIXME make normal clipping
        if (polygon.p1.position.z() >= 0 || polygon.p2.position.z() >= 0 || polygon.p3.position.z() >= 0) {
            polygon.p1.position = {0, 0,0};
            polygon.p1.SetPostionInWorld({0, 0,0});
            polygon.p2.position = {0, 0,0};
            polygon.p2.SetPostionInWorld({0, 0,0});
            polygon.p3.position = {0, 0,0};
            polygon.p3.SetPostionInWorld({0, 0,0});

            continue;
        }

        // TODO make function for this
        polygon.p1.position.x() *= camera.near_ / -polygon.p1.position.z();
        polygon.p1.position.y() *= camera.near_ / -polygon.p1.position.z();
        polygon.p1.position.z() = -polygon.p1.position.z();

        polygon.p2.position.x() *= camera.near_ / -polygon.p2.position.z();
        polygon.p2.position.y() *= camera.near_ / -polygon.p2.position.z();
        polygon.p2.position.z() = -polygon.p2.position.z();

        polygon.p3.position.x() *= camera.near_ / -polygon.p3.position.z();
        polygon.p3.position.y() *= camera.near_ / -polygon.p3.position.z();
        polygon.p3.position.z() = -polygon.p3.position.z();
    }
}

void GeometryStage::transformToNormalizedSpace(std::vector<Polygon>& polygons, const Camera& camera) const {
    float camera_width_ = camera.camera_width_;
    float camera_height_ = camera.camera_height_;

    for (auto& polygon : polygons) {
       polygon.p1.position.x() = (polygon.p1.position.x() + camera_width_ / 2) / camera_width_;
       polygon.p1.position.y() = (polygon.p1.position.y() + camera_height_ / 2) / camera_height_;

       polygon.p2.position.x() = (polygon.p2.position.x() + camera_width_ / 2) / camera_width_;
       polygon.p2.position.y() = (polygon.p2.position.y() + camera_height_ / 2) / camera_height_;

       polygon.p3.position.x() = (polygon.p3.position.x() + camera_width_ / 2) / camera_width_;
       polygon.p3.position.y() = (polygon.p3.position.y() + camera_height_ / 2) / camera_height_;

       // FIXME make normal clipping
       if (polygon.p1.position.x() > 1 || polygon.p1.position.x() < 0 || polygon.p1.position.y() > 1 || polygon.p1.position.y() < 0 ||
       polygon.p2.position.x() > 1 || polygon.p2.position.x() < 0 || polygon.p2.position.y() > 1 || polygon.p2.position.y() < 0 ||
       polygon.p3.position.x() > 1 || polygon.p3.position.x() < 0 || polygon.p3.position.y() > 1 || polygon.p3.position.y() < 0) {
            polygon.p1.position = {0, 0,0};
            polygon.p1.SetPostionInWorld({0, 0,0});
            polygon.p2.position = {0, 0,0};
            polygon.p2.SetPostionInWorld({0, 0,0});
            polygon.p3.position = {0, 0,0};
            polygon.p3.SetPostionInWorld({0, 0,0});
       }
    }
}

Matrix4 GeometryStage::computeCameraViewMatrix(const Camera& camera) const {
    Matrix4 view = Matrix4::Identity();
    view.block<1, 3>(0, 0) = camera.x;
    view.block<1, 3>(1, 0) = camera.y;
    view.block<1, 3>(2, 0) = camera.z;

    view(0, 3) = -camera.x.dot(camera.eye_);
    view(1, 3) = -camera.y.dot(camera.eye_);
    view(2, 3) = -camera.z.dot(camera.eye_);

    return view;
}
}
