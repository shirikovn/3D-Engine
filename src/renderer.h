#pragma once

#include "core/ImageBuffer.h"
#include "scene/Scene.h"
#include "stages/FragmentShaderStage/FragmentShaderStage.h"
#include "stages/GeometryStage/GeometryStage.h"
#include "stages/RasterizationStage/RasterizationStage.h"
#include "stages/WriteStage/WriteStage.h"

namespace Render3D {
class Renderer {
public:
    ImageBuffer render(RasterizationStage::Resolution res, const Scene& scene) const;
private:
    GeometryStage geometry_stage_;
    RasterizationStage rasterization_stage_;
    FragmentShaderStage fragment_shader_stage_;
    ImageBufferWriter image_writer_;
};
}
