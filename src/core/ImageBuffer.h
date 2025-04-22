#pragma once

#include "primitives/Color.h"

namespace Render3D {
class ImageBuffer {
    public:
        ImageBuffer(size_t m, size_t n, Color color) : height_(m), width_(n) {
            matrix_.resize(m * n, color);
        }
        
        auto GetData() {
            return matrix_.data();
        }
    
        Color& operator()(size_t m, size_t n) {
            return matrix_[m * width_ + n];
        }
    
        const Color& operator()(size_t m, size_t n) const {
            return matrix_[m * width_ + n];
        }
    
    private:
        size_t width_;
        size_t height_;
        std::vector<Color> matrix_;
    };
}
