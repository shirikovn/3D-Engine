#include "RasterizationStage.h"

#include <iostream>
#include <thread>
#include <vector>

namespace Render3D {
    FragmentBuffer RasterizationStage::process(std::vector<Polygon>& polygons, Resolution res) const {
        unsigned int width = res.width;
        unsigned int height = res.height;

        FragmentBuffer result{width, height};
        ZBuffer z_buffer{width, height};

        for (Polygon& polygon : polygons) {
            transformPolygonToRasterSpace(polygon, res);
        }

        std::vector<std::thread> threads;

        for (unsigned int i = 0; i < threads_num; ++i) {
            threads.emplace_back([this, &polygons, &result, &z_buffer, res, i](){
                rasterizePolygon(polygons, result, z_buffer, res, i);
            });
        }

        for (auto& thread : threads) {
            thread.join();
        }

        return result;
    }

    void RasterizationStage::rasterizePolygon(const std::vector<Polygon>& polygons, FragmentBuffer& frag_buffer, ZBuffer& z_buffer, Resolution res, unsigned ind) const {
        for (const Polygon& polygon : polygons) {
            // TODO do normally
            unsigned minX = res.width, minY = res.height, maxX = 0, maxY = 0;

            minX = std::min(minX, static_cast<unsigned>(polygon.p1.position.x()));
            minX = std::min(minX, static_cast<unsigned>(polygon.p2.position.x()));
            minX = std::min(minX, static_cast<unsigned>(polygon.p3.position.x()));

            minY = std::min(minY, static_cast<unsigned>(polygon.p1.position.y()));
            minY = std::min(minY, static_cast<unsigned>(polygon.p2.position.y()));
            minY = std::min(minY, static_cast<unsigned>(polygon.p3.position.y()));

            maxX = std::max(maxX, static_cast<unsigned>(polygon.p1.position.x() + 0.5));
            maxX = std::max(maxX, static_cast<unsigned>(polygon.p2.position.x() + 0.5));
            maxX = std::max(maxX, static_cast<unsigned>(polygon.p3.position.x() + 0.5));

            maxY = std::max(maxY, static_cast<unsigned>(polygon.p1.position.y() + 0.5));
            maxY = std::max(maxY, static_cast<unsigned>(polygon.p2.position.y() + 0.5));
            maxY = std::max(maxY, static_cast<unsigned>(polygon.p3.position.y() + 0.5));

            std::vector<std::thread> threads;

            for (unsigned int i = minX + ind; i < maxX; i += threads_num) {
                for (unsigned int j = minY; j < maxY; ++j) {
                    Vector3 point(i + 0.5, j + 0.5, 0);
                    Vector3 barycentric_coordinates = calculateBarycentricCoordinates(point, polygon);

                    if (barycentric_coordinates(0) >= 0 && barycentric_coordinates(1) >= 0 &&
                        barycentric_coordinates(2) >= 0) {

                        float area = edgeFunction(polygon.p1.position, polygon.p2.position, polygon.p3.position);
                        barycentric_coordinates /= area;

                        float point_depth =
                            calculatePointDepth(barycentric_coordinates, polygon);

                        if (point_depth < z_buffer(i, j) && point_depth > 0) {
                            z_buffer(i, j) = point_depth;

                            Fragment fragment{
                                .depth = point_depth,
                                .color = polygon.p1.base_color, // TODO should calculate using bar coords for gradient
                                .normal = (polygon.p1.normal * barycentric_coordinates(0) + polygon.p2.normal * barycentric_coordinates(1) + polygon.p3.normal * barycentric_coordinates(2)).normalized(),
                                .world_position =  polygon.p1.GetPositionInWorld() * barycentric_coordinates(0) + polygon.p2.GetPositionInWorld() * barycentric_coordinates(1) + polygon.p3.GetPositionInWorld() * barycentric_coordinates(2),
                            };

                            frag_buffer(i, j) = fragment;
                        }
                    }
                }
            }
        }
    }

    float RasterizationStage::edgeFunction(const Vector3& a, const Vector3& b, const Vector3& c) const {
        return -((c(0) - a(0)) * (b(1) - a(1)) - (c(1) - a(1)) * (b(0) - a(0)));
    }

    Vector3 RasterizationStage::calculateBarycentricCoordinates(const Vector3& point, const Polygon& polygon) const {
        float w1 = edgeFunction(polygon.p2.position, polygon.p3.position, point);
        float w2 = edgeFunction(polygon.p3.position, polygon.p1.position, point);
        float w3 = edgeFunction(polygon.p1.position, polygon.p2.position, point);

        return {w1, w2, w3};
    }

    float RasterizationStage::calculatePointDepth(const Vector3& barycentric_coordinates, const Polygon& polygon) const {
        return 1 / (barycentric_coordinates(0) * (1 / polygon.p1.position.z()) +
               barycentric_coordinates(1) * (1 / polygon.p2.position.z()) +
               barycentric_coordinates(2) * (1 / polygon.p3.position.z()));
    }

    void RasterizationStage::transformPolygonToRasterSpace(Polygon& polygon, Resolution res) const {
        polygon.p1.position.x() *= res.width;
        polygon.p1.position.y() = (1 - polygon.p1.position.y()) * res.height;

        polygon.p2.position.x() *= res.width;
        polygon.p2.position.y() = (1 - polygon.p2.position.y()) * res.height;

        polygon.p3.position.x() *= res.width;
        polygon.p3.position.y() = (1 - polygon.p3.position.y()) * res.height;
    }
}
