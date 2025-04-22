#include "WriteStage.h"

namespace Render3D {
ImageBuffer ImageBufferWriter::process(FragmentBuffer&& buffer, const Color& background) const {
    auto width = buffer.width_;
    auto height = buffer.height_;

    ImageBuffer res{height, width, background};

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            if (buffer(i, j)) {
                res(i, j) = buffer(i, j)->color;
            } else {
                res(i, j) = background;
            }
        }
    }

    return res;
}
}