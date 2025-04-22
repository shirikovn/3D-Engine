#pragma once

#include "Linalg.h"
#include <algorithm>

namespace Render3D {
struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t aplha;

    Color operator+(const Color& other) const {
        return {
            static_cast<uint8_t>(std::clamp(static_cast<int>(red) + other.red, 0, 255)),
            static_cast<uint8_t>(std::clamp(static_cast<int>(green) + other.green, 0, 255)),
            static_cast<uint8_t>(std::clamp(static_cast<int>(blue) + other.blue, 0, 255))
        };
    }

    Color operator*(float factor) const {
        return {
            static_cast<uint8_t>(std::clamp(static_cast<int>(red * factor), 0, 255)),
            static_cast<uint8_t>(std::clamp(static_cast<int>(green * factor), 0, 255)),
            static_cast<uint8_t>(std::clamp(static_cast<int>(blue * factor), 0, 255))
        };
    }

    friend Color operator*(float factor, const Color& color) {
        return color * factor;
    }
};
}
