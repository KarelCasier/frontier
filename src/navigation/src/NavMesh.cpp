#include <navigation/NavMesh.hpp>

#include <SDL2/SDL.h>

#include <algorithm>
#include <iostream>
#include <math.h>

#include <log/log.hpp>
#include <math/Collision.hpp>

namespace {
using namespace frontier;

/// 2D cross product of "oa" and "ob" vectors, i.e. z-component of their 3D cross product.
/// Returns a positive value, if "oab" makes a counter-clockwise turn,
/// negative for clockwise turn, and zero if the points are collinear.
double cross(const Vector2f& o, const Vector2f& a, const Vector2f& b)
{
    return (a.x() - o.x()) * (b.y() - o.y()) - (a.y() - o.y()) * (b.x() - o.x());
}

bool vectorCompare(Vector2f& a, Vector2f& b)
{
    return a.x() < b.x() || (a.x() == b.x() && a.y() < b.y());
}

/// Returns a list of points on the convex hull in counter-clockwise order.
/// Note: the last point in the returned list is the same as the first one.
std::vector<Vector2f> toConvexHull(std::vector<Vector2f> points)
{
    return points;
}

/// Determine if 2 NavPolys are neighbours.
///
/// @param[in] polyA The first navigation poly.
/// @param[in] polyB The second navigation poly.
/// @param[out] edge The edge they are connected by.
/// @returns true if they are neighbours, false otherwise.
///
/// TODO: Ensure that the points are contigous.
bool isNeighbour(std::shared_ptr<NavPoly> polyA, std::shared_ptr<NavPoly> polyB, Edge& edge)
{
    if (polyA.get() == polyB.get()) {
        return false;
    }

    const auto& shapeA = polyA->_shape;
    const auto& shapeB = polyB->_shape;

    if (!intersects(shapeA->boundingBox(), shapeB->boundingBox())) {
        return false;
    }

    std::vector<Vector2f> connectedPoints;

    for (auto& pointA : shapeA->points()) {
        for (auto& pointB : shapeB->points()) {
            if (pointA == pointB) {
                connectedPoints.emplace_back(pointA);
            }
        }
    }

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
        const auto shape = poly->_shape;
        auto points = shape->points();
        points.push_back(points.front());
        renderTarget.render(points, PrimativeType::LineStrip, {255, 0, 0});
    }
}

void NavMesh::addPoly(std::shared_ptr<ConvexShape<float>> poly)
{
    _mesh.push_back(std::make_shared<NavPoly>(poly));
    regenerate();
}

void NavMesh::regenerate()
{
    for (auto I = begin(_mesh); I != end(_mesh); ++I) {
        (*I)->_neighbours.clear();
    }
    for (auto I = begin(_mesh); I != end(_mesh); ++I) {
        for (auto J = I; J != end(_mesh); ++J) {
            auto edge = Edge{};
            auto neighbour = isNeighbour(*I, *J, edge);
            if (neighbour) {
                (*I)->_neighbours.emplace_back(*J, edge);
                (*J)->_neighbours.emplace_back(*I, edge);
            }
        }
    }
}

std::vector<Vector2f> NavMesh::navigationPath(const Vector2f& startPos, const Vector2f& targetPos)
{
}

} // namespace frontier
