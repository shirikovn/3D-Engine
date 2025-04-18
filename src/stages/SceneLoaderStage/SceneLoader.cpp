#include "SceneLoader.h"
#include "core/primitives/Vertex.h"
#include "scene/Mesh.h"

#include <vector>

namespace Render3D {
void SceneLoader::addMeshOnScene(Scene &scene, Parser::ParsedMesh&& parsed_mesh, Color color, const Matrix4& model_matrix) const {
    Mesh result;
    result.model_matrix = model_matrix;

    std::vector<Vertex> vertices(parsed_mesh.vertices.size());

    for (size_t i = 0; i < parsed_mesh.vertices.size(); ++i) {
        vertices[i].base_color = color;
        vertices[i].position = {parsed_mesh.vertices[i].x, parsed_mesh.vertices[i].y, parsed_mesh.vertices[i].z};
    }

    for (auto face : parsed_mesh.faces) {
        Parser::Vertex p1v = parsed_mesh.vertices[face.vertexIndices[0]];
        Parser::Vertex p2v = parsed_mesh.vertices[face.vertexIndices[1]];
        Parser::Vertex p3v = parsed_mesh.vertices[face.vertexIndices[2]];

        Vector3 p1 = {p1v.x,  p1v.y,  p1v.z};
        Vector3 p2 = {p2v.x,  p2v.y,  p2v.z};
        Vector3 p3 = {p3v.x,  p3v.y,  p3v.z};

        Vector3 normal = (p2 - p1).cross(p3 - p1).normalized();

        vertices[face.vertexIndices[0]].normal += normal;
        vertices[face.vertexIndices[1]].normal += normal;
        vertices[face.vertexIndices[2]].normal += normal;
    }

    for (auto& vertex : vertices) {
        vertex.normal.normalize();
    }

    for (auto face : parsed_mesh.faces) {
        auto ind1 = face.vertexIndices[0];
        auto ind2 = face.vertexIndices[1];
        auto ind3 = face.vertexIndices[2];

        result.polygons.push_back({vertices[ind1], vertices[ind2], vertices[ind3]});
    }

    scene.meshes.push_back(std::move(result));
}
}
