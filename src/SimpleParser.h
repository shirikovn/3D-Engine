#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace Parser {
struct Vertex {
    float x, y, z;
};

struct Face {
    std::vector<int> vertexIndices; // Indices of the vertices forming the face
};

class OBJParser {
public:
    // Parses the .obj file and stores vertices and faces
    bool parse(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return false;
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
        return true;
    }

    // Prints the vertices
    void printVertices() const {
        for (const auto& vertex : vertices) {
            std::cout << "Vertex: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")\n";
        }
    }

    // Prints the faces
    void printFaces() const {
        for (const auto& face : faces) {
            std::cout << "Face: ";
            for (const auto& index : face.vertexIndices) {
                std::cout << index + 1 << " "; // Convert back to 1-based index for display
            }
            std::cout << "\n";
        }
    }

    std::vector<Vertex> vertices;
    std::vector<Face> faces;
};
} // namespace Parser
