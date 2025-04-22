#pragma once

#include "scene/Camera.h"
#include "stages/RasterizationStage/FragmentBuffer.h"
#include "scene/PointLight.h"

#include <vector>

namespace Render3D {
class FragmentShaderStage {
public:
    void process(FragmentBuffer& fragment_buffer, const std::vector<PointLight>& lights, const Camera& camera) const;

private:
    void shadeFragment(Fragment& frag, const PointLight&, const Camera& camera) const;
};
}
