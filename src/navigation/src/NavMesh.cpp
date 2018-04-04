#include <navigation/NavMesh.hpp>

#include <SDL2/SDL.h>

#include <algorithm>
#include <iostream>
#include <math.h>

#include <log/log.hpp>
#include <math/Collision.hpp>

namespace {
using namespace frontier;

/// Determine if 2 NavPolys are neighbours.
///
/// @param[in] polyA The first navigation poly.
/// @param[in] polyB The second navigation poly.
/// @param[out] edge The edge they are connected by.
/// @returns true if they are neighbours, false otherwise.
///
/// TODO: Ensure that the points are contigous.
bool isNeighbour(const NavPoly& polyA, const NavPoly& polyB, Edge& edge)
{
    const auto& shapeA = polyA._shape;
    const auto& shapeB = polyB._shape;

    if (!intersects(shapeA.boundingBox(), shapeB.boundingBox())) {
        return false;
    }

    auto connectedPoints = std::vector<Vector2f>{};

    for (auto& pointA : shapeA.points()) {
        for (auto& pointB : shapeB.points()) {
            if (pointA == pointB) {
                connectedPoints.emplace_back(pointA);
            }
        }
    }

    std::sort(begin(connectedPoints), end(connectedPoints), lexicographVectorCompare<float>);
    /// Since first and last points are the same, we may have duplicated points.
    auto I = std::unique(begin(connectedPoints), end(connectedPoints));
    connectedPoints.resize(distance(begin(connectedPoints), I));

    if (connectedPoints.size() == 2) {
        edge.start = connectedPoints[0];
        edge.end = connectedPoints[1];
        edge.mid = (edge.start + edge.end) / 2.0;
        return true;
    } else if (connectedPoints.size() > 2) {
        for (const auto& pt : connectedPoints) {
            LOGI << "[" << pt.x() << "," << pt.y() << "]";
        }
        throw std::runtime_error("NavPolys connected by more than 2 points.");
    }
    return false;
}

} // namespace

namespace frontier {

void NavMesh::render(IRenderTarget& renderTarget)
{
    for (const auto& poly : _mesh) {
        const auto& shape = poly._shape;
        auto points = shape.points();
        points.push_back(points.front());
        renderTarget.render(points, PrimativeType::LineStrip, {255, 0, 0});
    }
}

void NavMesh::addPoly(ConvexShape<float> poly)
{
    _mesh.emplace_back(std::move(poly));
    regenerate();
}

void NavMesh::regenerate()
{
    for (auto I = begin(_mesh); I != end(_mesh); ++I) {
        (*I)._neighbours.clear();
    }
    for (auto I = begin(_mesh); I != end(_mesh); ++I) {
        for (auto J = I + 1; J != end(_mesh); ++J) {
            auto edge = Edge{};
            auto neighbour = isNeighbour(*I, *J, edge);
            if (neighbour) {
                (*I)._neighbours.emplace_back(*J, edge);
                (*J)._neighbours.emplace_back(*I, edge);
            }
        }
    }
}

std::vector<Vector2f> NavMesh::navigationPath(const Vector2f& startPos, const Vector2f& targetPos)
{
}

} // namespace frontier
