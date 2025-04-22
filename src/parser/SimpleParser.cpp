#include "SimpleParser.h"

namespace Parser {
    ParsedMesh OBJParser::parse(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            throw std::runtime_error("Cannot open file: " + filename);
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream stream(line);
            std::string prefix;
            stream >> prefix;

            // Parse vertex line
            if (prefix == "v") {
                Vertex vertex;
                stream >> vertex.x >> vertex.y >> vertex.z;
                vertices.push_back(vertex);
            }
            // Parse face line
            else if (prefix == "f") {
                Face face;
                std::string vertexData;
                while (stream >> vertexData) {
                    std::istringstream vertexStream(vertexData);
                    int vertexIndex;
                    // Only extract the vertex index (ignore texture and normal indices)
                    char slash; // To skip the '/' character
                    vertexStream >> vertexIndex;
                    face.vertexIndices.push_back(vertexIndex - 1); // Convert to 0-based index
                }
                faces.push_back(face);
            }
        }

        file.close();
        return {std::move(vertices), std::move(faces)};
    }
}
