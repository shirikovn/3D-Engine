#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace Parser {
struct Vertex {
    float x, y, z;
};

struct Face {
    std::vector<int> vertexIndices; // Indices of the vertices forming the face
};

struct ParsedMesh {
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
};

class OBJParser {
public:
    ParsedMesh parse(const std::string& filename);

    std::vector<Vertex> vertices;
    std::vector<Face> faces;
};
} // namespace Parser
