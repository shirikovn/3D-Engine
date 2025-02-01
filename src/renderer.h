#pragma once

#include <vector>
#include "objects/camera.h"
#include "world.h"

using namespace Eigen;

struct DumbPixel {
    DumbPixel(int red_component, int green_component, int blue_component) : red(red_component), green(green_component), blue(blue_component) {};
    int red, green, blue;
};

using DumbFrameBuffer = std::vector<std::vector<DumbPixel>>;

class Renderer {
public:
    DumbFrameBuffer Render(World world);
};
