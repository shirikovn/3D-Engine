#pragma once

#include <Eigen/Dense>

struct Camera {
    Eigen::Vector3f eye, up, target;
    float near;
    float window_width, window_height;
};
