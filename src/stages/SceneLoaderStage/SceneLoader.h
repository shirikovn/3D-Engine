#pragma once

#include "Linalg.h"
#include "core/primitives/Color.h"
#include "scene/Scene.h"
#include "parser/SimpleParser.h"

namespace Render3D {
class SceneLoader {
public:
    void addMeshOnScene(Scene& scene, Parser::ParsedMesh&& parsed_mesh, Color color, const Matrix4& model_matrix = Matrix4::Identity()) const;
};
}
