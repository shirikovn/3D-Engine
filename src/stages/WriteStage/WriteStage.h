#pragma once

#include "core/ImageBuffer.h"
#include "stages/RasterizationStage/FragmentBuffer.h"

namespace Render3D {
class ImageBufferWriter {
public:
    ImageBuffer process(FragmentBuffer&& buffer, const Color& background = {0, 0, 0}) const;
};
}