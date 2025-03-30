#include "Linalg.h"
#include "Renderer.h"
#include "Shaderer.h"
#include "buffers/ImageBuffer.h"
#include "objects/Camera.h"
#include "objects/Mesh.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

namespace Render3D {
class Application {
public:
    void run() {
        constexpr unsigned int height = 800;
        constexpr unsigned int width = 800;

        // TESTING pyramid
        std::vector<Render3D::Polygon> all_polygons;

        all_polygons.push_back({Polygon::BaseColor, {-2, 2, 0}, {0, 0, 2}, {2, 2, 0}});
        all_polygons.push_back({Polygon::BaseColor, {-2, -2, 0}, {0, 0, 2}, {-2, 2, 0}});
        all_polygons.push_back({Polygon::BaseColor, {2, -2, 0}, {0, 0, 2}, {-2, -2, 0}});
        all_polygons.push_back({Polygon::BaseColor, {2, -2, 0}, {2, 2, 0}, {0, 0, 2}});

        Render3D::Shaderer shaderer{};
        shaderer.addLight({{-1, 1.2, 1.5}, 1});

        for (auto& polygon : all_polygons) {
            shaderer.shadePolygon(polygon);
        }

        float dist = 2.8;
        Render3D::Camera camera(Render3D::Vector3(-1 * dist, 1 * dist, 0.5 * dist),
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

        for (unsigned int i = 0; i < height; ++i) {
            for (unsigned int j = 0; j < width; ++j) {
                sf::Color color{buffer(i, j).red, buffer(i, j).green, buffer(i, j).blue};
                image.setPixel({i, j}, color);
            }
        }

        sf::Texture texture(image);
        sf::Sprite sprite(texture);

        while (window.isOpen()) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }

                window.clear(sf::Color::White);
                window.draw(sprite);
                window.display();
            }
        }
    }
};
} // namespace Render3D
