#include "Linalg.h"
#include "Renderer.h"
#include "Shaderer.h"
#include "SimpleParser.h"
#include "buffers/ImageBuffer.h"
#include "objects/Camera.h"
#include "objects/Mesh.h"
#include "objects/primitives/Polygon.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace Render3D {
class Application {
public:
    void run() {
        constexpr unsigned int height = 800;
        constexpr unsigned int width = 800;

        std::string input1 =
            "/Users/nikitashirikov/Edu/AMI2/coursework/3d-engine/models/teapot.obj";

        Parser::OBJParser parser;
        parser.parse(input1);

        std::vector<Render3D::Polygon> all_polygons;

        for (auto& face : parser.faces) {
            Polygon polygon{};

            polygon.p1.x() = parser.vertices[face.vertexIndices[0]].x;
            polygon.p1.y() = parser.vertices[face.vertexIndices[0]].y;
            polygon.p1.z() = parser.vertices[face.vertexIndices[0]].z;

            polygon.p2.x() = parser.vertices[face.vertexIndices[1]].x;
            polygon.p2.y() = parser.vertices[face.vertexIndices[1]].y;
            polygon.p2.z() = parser.vertices[face.vertexIndices[1]].z;

            polygon.p3.x() = parser.vertices[face.vertexIndices[2]].x;
            polygon.p3.y() = parser.vertices[face.vertexIndices[2]].y;
            polygon.p3.z() = parser.vertices[face.vertexIndices[2]].z;

            polygon.color = Polygon::BaseColor;

            all_polygons.push_back(polygon);
        }

        Render3D::Shaderer shaderer{};
        shaderer.addLight({{-2, 2.4, 2}, 1});

        float dist = 1.5;
        Render3D::Camera camera(Render3D::Vector3(-1 * dist, 1 * dist, 0.8 * dist),
                                Render3D::Vector3(0, 0, 0), 10, 10, 2);

        std::vector<Render3D::PolygonAttributes> all_polygons_attributes;
        for (const auto& polygon : all_polygons) {
            all_polygons_attributes.push_back(camera.transformToNormalizedSpace(polygon));
        }

        Render3D::Renderer renderer(width, height);
        auto buffer = renderer.render(all_polygons_attributes, {255, 255, 255});

        // TODO class Screen
        sf::RenderWindow window(sf::VideoMode({width, height}), "My window");

        sf::Image image({width, height}, sf::Color(255, 255, 255));
        sf::Texture texture(image);

        std::vector<std::uint8_t> pixels(width * height * 4);

        float angle = M_PI / 4 / 160.0f;
        Vector3 axis(0, 1, 1); // Z-axis
        Quaternion q(Eigen::AngleAxisf(angle, axis));

        int frame = 0;

        sf::Clock clock;
        int frameCount = 0;
        float fps = 0.0f;
        sf::Clock fpsClock;

        while (window.isOpen()) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }
            }

            for (auto& polygon : all_polygons) {
                polygon.p1 = q * polygon.p1;
                polygon.p2 = q * polygon.p2;
                polygon.p3 = q * polygon.p3;
            }

            for (auto& polygon : all_polygons) {
                shaderer.shadePolygon(polygon);
            }

            std::vector<Render3D::PolygonAttributes> all_polygons_attributes;
            for (const auto& polygon : all_polygons) {
                all_polygons_attributes.push_back(camera.transformToNormalizedSpace(polygon));
            }

            auto buffer = renderer.render(all_polygons_attributes, {255, 255, 255});

            for (unsigned int i = 0; i < height; ++i) {
                for (unsigned int j = 0; j < width; ++j) {
                    image.setPixel({i, j},
                                   {buffer(i, j).red, buffer(i, j).green, buffer(i, j).blue});
                }
            }

            texture.update(image);

            // std::ostringstream filename;
            // filename << "/Users/nikitashirikov/Edu/AMI2/coursework/3d-engine/output" << "/frame_"
            // << std::setw(3) << std::setfill('0') << frame++ << ".png"; auto tmp =
            // texture.copyToImage().saveToFile(filename.str());

            sf::Sprite sprite(texture);

            window.clear(sf::Color::White);
            window.draw(sprite);
            window.display();

            // std::cout << "frame " << frame++ << std::endl;

            frameCount++;
            if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
                fps = frameCount / fpsClock.getElapsedTime().asSeconds();
                frameCount = 0;
                fpsClock.restart();

                std::cout << "FPS: " << fps << std::endl;
            }
        }
    }
};
} // namespace Render3D
