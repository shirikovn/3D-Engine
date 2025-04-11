#pragma once

#include "Linalg.h"

#include <array>
#include <vector>

namespace Render3D {
struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    Pixel operator*(float scalar) const {
        return {static_cast<uint8_t>(red * scalar), static_cast<uint8_t>(green * scalar),
                static_cast<uint8_t>(blue * scalar)};
    }
};

using Color = Pixel;

class ImageBuffer {
public:
    ImageBuffer(size_t m, size_t n, Pixel color) : height_(m), width_(n) {
        matrix_.resize(m * n, color);
    }

    Pixel& operator()(size_t m, size_t n) {
        return matrix_[m * width_ + n];
    }

    const Pixel& operator()(size_t m, size_t n) const {
        return matrix_[m * width_ + n];
    }

private:
    size_t width_;
    size_t height_;
    std::vector<Pixel> matrix_;
};
} // namespace Render3D
