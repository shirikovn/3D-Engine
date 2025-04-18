#include "Renderer.h"

namespace Render3D {
ImageBuffer Renderer::render(RasterizationStage::Resolution res, const Scene& scene) const {
    GeometryStage geometry_stage;
    auto geom_res = geometry_stage.process(scene);

    RasterizationStage raster_stage;
    auto rasterized = raster_stage.process(geom_res, res);

    FragmentShaderStage fragment_shader;
    fragment_shader.process(rasterized, scene.lights, scene.camera);

    ImageBufferWriter writer;
    auto output = writer.process(std::move(rasterized));

    return output;
}
}
