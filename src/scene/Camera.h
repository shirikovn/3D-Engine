#pragma once

#include "Linalg.h"
#include "util/VectorTransforms.h"

namespace Render3D {
class Camera {
public:
    Camera(Vector3 eye, Vector3 target, float near, float camera_width, float camera_height) : eye_(eye), target_(target), near_(near), camera_width_(camera_width), camera_height_(camera_height) {
        z = -(target - eye).normalized();
        y = Util::calculateOrthogonalComponentToVector(Vector3(0, 0, 1), -z).normalized();
        x = y.cross(-z);
    }

    void moveForward() {
        eye_ -= movement_speed * z;
    }

    void moveBackward() {
        eye_ += movement_speed * z;
    }

    void moveRight() {
        eye_ += movement_speed * x;
    }

    void moveLeft() {
        eye_ -= movement_speed * x;
    }

    void moveUp() {
        eye_ += movement_speed * y;
    }

    void moveDown() {
        eye_ -= movement_speed * y;
    }

    void rotateUp() {
        double theta = - M_PI / 360;
        Vector3 k = x;
        Matrix3 K;

        K <<  0,    -k.z(),   k.y(),
          k.z(),  0,      -k.x(),
         -k.y(),  k.x(),  0;

        Matrix3 R = Matrix3::Identity() + std::sin(theta) * K + (1 - std::cos(theta)) * K * K;
        
        x = R * x;
        y = R * y;
        z = R * z;
    }

    void rotateDown() {
        double theta = M_PI / 360;
        Vector3 k = x;
        Matrix3 K;

        K <<  0,    -k.z(),   k.y(),
          k.z(),  0,      -k.x(),
         -k.y(),  k.x(),  0;

        Matrix3 R = Matrix3::Identity() + std::sin(theta) * K + (1 - std::cos(theta)) * K * K;
        
        x = R * x;
        y = R * y;
        z = R * z;
    }

    void rotateRight() {
        double theta = M_PI / 360;
        Vector3 k = {0, 0, 1};
        Matrix3 K;

        K <<  0,    -k.z(),   k.y(),
          k.z(),  0,      -k.x(),
         -k.y(),  k.x(),  0;

        Matrix3 R = Matrix3::Identity() + std::sin(theta) * K + (1 - std::cos(theta)) * K * K;
        
        x = R * x;
        y = R * y;
        z = R * z;
    }

    void rotateLeft() {
        double theta = -M_PI / 360;
        Vector3 k = {0, 0, 1};
        Matrix3 K;

        K <<  0,    -k.z(),   k.y(),
            k.z(),  0,      -k.x(),
            -k.y(),  k.x(),  0;

        Matrix3 R = Matrix3::Identity() + std::sin(theta) * K + (1 - std::cos(theta)) * K * K;
        
        x = R * x;
        y = R * y;
        z = R * z;
    }

    void increaseNear() {
        near_ += 0.01;
    }

    void decreaseNear() {
        near_ -= 0.01;
    }

    Vector3 x, y, z;
    Vector3 eye_, target_;
    float near_;
    float camera_width_, camera_height_;

    float movement_speed = 0.01;
};
}
