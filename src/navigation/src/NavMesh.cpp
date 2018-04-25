#include <navigation/NavMesh.hpp>

#include <SDL2/SDL.h>

#include <algorithm>
#include <cmath>
#include <iostream>

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

    /// Since first and last points are the same, we may have duplicated points.
    std::sort(begin(connectedPoints), end(connectedPoints), lexicographVectorCompare<float>);
    auto I = std::unique(begin(connectedPoints), end(connectedPoints));
    connectedPoints.resize(distance(begin(connectedPoints), I));

    if (connectedPoints.size() == 2) {
        edge.start = connectedPoints[0];
        edge.end = connectedPoints[1];
        edge.mid = (edge.start + edge.end) / 2.0;
        return true;
    }
    if (connectedPoints.size() > 2) {
        for (const auto& pt : connectedPoints) {
            LOGI << "[" << pt.x() << "," << pt.y() << "]";
        }
        throw std::runtime_error("NavPolys connected by more than 2 points.");
    }
    return false;
}

std::vector<Vector2f> createPointPath(const Vector2f& initial,
                                      const Vector2f& target,
                                      const std::vector<const NavPoly*>& navPolyPath)
{
    // TODO(Karel) perform funnel algorithm
    auto pointPath = std::vector<Vector2f>{};
    pointPath.reserve(navPolyPath.size() + 1);

    pointPath.emplace_back(initial);
    for (auto I = cbegin(navPolyPath); I != cend(navPolyPath);) {
        auto nextI = I + 1;
        if (nextI == cend(navPolyPath)) {
            break;
        }
        if (I == nextI) {
            continue;
        }
        const auto edge = (*I)->_neighbours.at(*nextI);
        pointPath.emplace_back(edge.mid);
        I = nextI;
    }
    pointPath.emplace_back(target);

    return pointPath;
}

} // namespace

namespace frontier {

NavMesh::NavMesh(std::unique_ptr<INavAlgorithm> navAlgorithm)
: _navAlgorithm{std::move(navAlgorithm)}
{
}

void NavMesh::render(IRenderTarget& renderTarget)
{
    for (const auto& poly : _mesh) {
        const auto& shape = poly._shape;
        auto points = shape.points();
        points.push_back(points.front());
        renderTarget.render(points, PrimativeType::LineStrip, {255, 0, 0});
        renderTarget.render({shape.center()}, PrimativeType::Points, {255, 0, 0});
        for (const auto& [_, edge] : poly._neighbours) {
            renderTarget.render({edge.mid}, PrimativeType::Points, {255, 255, 255});
        }
    }
}

void NavMesh::addPoly(ConvexShape<float> poly)
{
    StateLock lock{_stateMutex};
    _mesh.emplace_back(std::move(poly));
    regenerateNavMesh(lock);
}

void NavMesh::regenerateNavMesh(const StateLock& /*unused*/)
{
    for (auto I = begin(_mesh); I != end(_mesh); ++I) {
        (*I)._neighbours.clear();
    }
    for (auto I = begin(_mesh); I != end(_mesh); ++I) {
        for (auto J = I + 1; J != end(_mesh); ++J) {
            auto edge = Edge{};
            auto neighbour = isNeighbour(*I, *J, edge);
            if (neighbour) {
                (*I)._neighbours.emplace(&(*J), edge);
                (*J)._neighbours.emplace(&(*I), edge);
            }
        }
    }
}

std::optional<const NavPoly*> NavMesh::findNavPolyContaining(const StateLock& /*unused*/, const Vector2f& point)
{
    for (const NavPoly& poly : _mesh) {
        if (poly._shape.contains(point)) {
            return &poly;
        }
    }
    return {};
}

std::vector<Vector2f> NavMesh::findPath(const Vector2f& initial, const Vector2f& target)
{
    StateLock lock{_stateMutex};

    const auto initialNavPoly = findNavPolyContaining(lock, initial);
    const auto targetNavPoly = findNavPolyContaining(lock, target);

    if (!initialNavPoly || !targetNavPoly) {
        return {initial, target};
    }

    const auto navPolyPath = _navAlgorithm->findNavPolyPath(*initialNavPoly, *targetNavPoly);
    return createPointPath(initial, target, navPolyPath);
}

} // namespace frontier
