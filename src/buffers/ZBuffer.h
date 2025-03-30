#pragma once

#include <limits>
#include <vector>

namespace Render3D {
    class ZBuffer {
    public:
        ZBuffer(unsigned int m, unsigned int n) : height_(m), width_(n) {
            matrix_.resize(m * n, std::numeric_limits<float>::infinity());
        }

        float& operator()(size_t m, size_t n) {
            return matrix_[m * width_ + n];
        }

        const float& operator()(size_t m, size_t n) const{
            return matrix_[m * width_ + n];
        }

    private:
        size_t width_;
        size_t height_;
        std::vector<float> matrix_;
    };
}
