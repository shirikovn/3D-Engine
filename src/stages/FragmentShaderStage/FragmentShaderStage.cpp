#include "FragmentShaderStage.h"
#include "core/primitives/Color.h"

#include <algorithm>
#include <iostream>

namespace Render3D {
    void FragmentShaderStage::process(FragmentBuffer& fragment_buffer, const std::vector<PointLight>& lights, const Camera& camera) const {
        for (size_t i = 0; i < fragment_buffer.height_; ++i) {
            for (size_t j = 0; j < fragment_buffer.width_; ++j) {
                if (!fragment_buffer(i, j).has_value()) {
                    continue;
                }
                for (const auto& light : lights) {
                    shadeFragment(fragment_buffer(i, j).value(), light, camera);
                }
            }
        } 
    }

    void FragmentShaderStage::shadeFragment(Fragment& frag, const PointLight& light, const Camera& camera) const {
        Vector3 N = frag.normal; 
        Vector3 L = (light.position - frag.world_position).normalized();
        Vector3 V = (camera.eye_ - frag.world_position).normalized();
        Vector3 H = (L + V).normalized();

        float diff = std::max(N.dot(L), 0.0f);
        Color diffuse = frag.color * light.intensity * diff;

        Color ambient = frag.color * 0.2;

        float spec = pow(std::max(N.dot(H), 0.0f), 0.1);
        Color specular = spec * frag.color * 0.1;

        frag.color = ambient + diffuse + specular;
    }
}
