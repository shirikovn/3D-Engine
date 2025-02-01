#include "renderer.h"
#include "primitives/primitives.h"

Matrix4f GetToCameraSpaceMatrix(Camera camera) {
    Vector3f z = (camera.eye - camera.target).normalized();
    Vector3f x = camera.up.cross(z).normalized();
    Vector3f y = camera.up.normalized();

    Matrix4f transform_matrix = Matrix4f::Identity();

    transform_matrix(0, 0) = x.x(); transform_matrix(0, 1) = x.y(); transform_matrix(0, 2) = x.z(); transform_matrix(0, 3) = -x.dot(camera.eye);
    transform_matrix(1, 0) = y.x(); transform_matrix(1, 1) = y.y(); transform_matrix(1, 2) = y.z(); transform_matrix(1, 3) = -y.dot(camera.eye);
    transform_matrix(2, 0) = z.x(); transform_matrix(2, 1) = z.y(); transform_matrix(2, 2) = z.z(); transform_matrix(2, 3) = -z.dot(camera.eye);

    return transform_matrix;
}

Vector4f TransformToCameraSpace(Vector3f point, const Matrix4f& viewMatrix) {
    Vector4f point4D(point.x(), point.y(), point.z(), 1.0f);
    return viewMatrix * point4D;
}

// Config image in another place
static int IMAGE_HIGHT = 600;
static int IMAGE_WIDTH = 1200;

DumbFrameBuffer Renderer::Render(World world) {
    Matrix4f transform_matrix = GetToCameraSpaceMatrix(world.main_camera);

    for (Mesh mesh : world.mess) {
        for (Polygon polygon : mesh.polygons) {
            for (auto p : {polygon.p1, polygon.p2, polygon.p3}) {
                Vector4f vector_in_camera = TransformToCameraSpace(p, transform_matrix);

                float screen_x = world.main_camera.near * vector_in_camera.x() / - vector_in_camera.z();
                float screen_y = world.main_camera.near * vector_in_camera.y() / - vector_in_camera.z();

                // convert to NDC
                Vector2f pNDC;
                pNDC(0) = screen_x / world.main_camera.window_width;
                pNDC(1) = screen_y / world.main_camera.window_height;

                // convert to raster
                Vector3f p_raster;
                p_raster(0) = (pNDC.x() + 1) / 2 * IMAGE_WIDTH;
                p_raster(1) = (1 - pNDC.y()) / 2 * IMAGE_HIGHT;
                p_raster(2) = -vector_in_camera.z();

                // TODO
            }
        }
    }

    return {}; // FIXME
}
