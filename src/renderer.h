#pragma once

#include "Linalg.h"
#include "buffers/ImageBuffer.h"
#include "buffers/ZBuffer.h"
#include "objects/Light.h"
#include "objects/primitives/Polygon.h"

#include <iostream>
#include <vector>

namespace Render3D {
class Renderer {
public:
    Renderer(unsigned int width, unsigned int height) : width_(width), height_(height) {
    }

    ImageBuffer render(std::vector<PolygonAttributes>& all_polygons_attrs,
                       Pixel background_color) const {
        ImageBuffer image_buffer{width_, height_, background_color};
        ZBuffer z_buffer{width_, height_};

        for (PolygonAttributes& attrs : all_polygons_attrs) {
            transformToRasterSpace(attrs.projectionOnScreen);
        }

        for (const PolygonAttributes& attributes : all_polygons_attrs) {
            // TODO do normally
            int minX = width_, minY = height_, maxX = 0, maxY = 0;

            minX = std::min(minX, static_cast<int>(attributes.projectionOnScreen.p1.x()));
            minX = std::min(minX, static_cast<int>(attributes.projectionOnScreen.p2.x()));
            minX = std::min(minX, static_cast<int>(attributes.projectionOnScreen.p3.x()));

            minY = std::min(minY, static_cast<int>(attributes.projectionOnScreen.p1.y()));
            minY = std::min(minY, static_cast<int>(attributes.projectionOnScreen.p2.y()));
            minY = std::min(minY, static_cast<int>(attributes.projectionOnScreen.p3.y()));

            maxX = std::max(maxX, static_cast<int>(attributes.projectionOnScreen.p1.x() + 0.5));
            maxX = std::max(maxX, static_cast<int>(attributes.projectionOnScreen.p2.x() + 0.5));
            maxX = std::max(maxX, static_cast<int>(attributes.projectionOnScreen.p3.x() + 0.5));

            maxY = std::max(maxY, static_cast<int>(attributes.projectionOnScreen.p1.y() + 0.5));
            maxY = std::max(maxY, static_cast<int>(attributes.projectionOnScreen.p2.y() + 0.5));
            maxY = std::max(maxY, static_cast<int>(attributes.projectionOnScreen.p3.y() + 0.5));

            // std::cout << minX << ' ' << maxX << ' ' << minY << ' ' << maxY << std::endl;

            for (unsigned int i = minX; i < maxX; ++i) {
                for (unsigned int j = minY; j < maxY; ++j) {
                    Vector2 point(i + 0.5, j + 0.5);

                    Vector3 barycentric_coordinates =
                        calculateBarycentricCoordinates(point, attributes.projectionOnScreen);
                    if (barycentric_coordinates(0) >= 0 && barycentric_coordinates(1) >= 0 &&
                        barycentric_coordinates(2) >= 0) {
                        float area = edgeFunction(attributes.projectionOnScreen.p1,
                                                  attributes.projectionOnScreen.p2,
                                                  attributes.projectionOnScreen.p3);
                        barycentric_coordinates /= area;

                        float point_depth =
                            calculatePointDepth(barycentric_coordinates, attributes.depths);

                        if (point_depth < z_buffer(i, j)) {
                            z_buffer(i, j) = point_depth;
                            image_buffer(i, j) = attributes.projectionOnScreen.color;
                        }
                    }
                }
            }
        }

        return image_buffer;
    }

private:
    Vector3 calculateBarycentricCoordinates(const Vector2& point, const Polygon2D& polygon) const {
        float w1 = edgeFunction(polygon.p2, polygon.p3, point);
        float w2 = edgeFunction(polygon.p3, polygon.p1, point);
        float w3 = edgeFunction(polygon.p1, polygon.p2, point);

        return {w1, w2, w3};
    }

    float calculatePointDepth(const Vector3& barycentric_coordinates,
                              const PolygonDepth& depths) const {
        return barycentric_coordinates.x() * (1 / depths.p1) +
               barycentric_coordinates.y() * (1 / depths.p2) +
               barycentric_coordinates.z() * (1 / depths.p3);
    }

    float edgeFunction(const Vector2& a, const Vector2& b, const Vector2& c) const {
        return -((c(0) - a(0)) * (b(1) - a(1)) - (c(1) - a(1)) * (b(0) - a(0)));
    }

    void transformToRasterSpace(Polygon2D& polygon) const {
        polygon.p1(0) = width_ * polygon.p1(0);
        polygon.p1(1) = height_ * (1 - polygon.p1(1));

        polygon.p2(0) = width_ * polygon.p2(0);
        polygon.p2(1) = height_ * (1 - polygon.p2(1));

        polygon.p3(0) = width_ * polygon.p3(0);
        polygon.p3(1) = height_ * (1 - polygon.p3(1));
    }

    unsigned int width_;
    unsigned int height_;
};
} // namespace Render3D
