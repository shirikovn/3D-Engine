#pragma once

#include "stages/RasterizationStage/Fragment.h"

#include <limits>
#include <vector>
#include <optional>

namespace Render3D {
class FragmentBuffer {
public:
FragmentBuffer(unsigned int m, unsigned int n) : height_(m), width_(n) {
        matrix_.resize(m * n);
    }

    std::optional<Fragment>& operator()(size_t m, size_t n) {
        return matrix_[m * width_ + n];
    }

    const std::optional<Fragment>& operator()(size_t m, size_t n) const {
        return matrix_[m * width_ + n];
    }


    const unsigned int width_;
    const unsigned int height_;
private:
    std::vector<std::optional<Fragment>> matrix_;
};
};
