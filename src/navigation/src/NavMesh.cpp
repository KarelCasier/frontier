#include <iostream>
#include <math.h>
#include <algorithm>

#include <navigation/NavMesh.hpp>
#include <math/Collision.hpp>
#include <log/log.hpp>

namespace {
using namespace frontier;

/// 2D cross product of "oa" and "ob" vectors, i.e. z-component of their 3D cross product.
/// Returns a positive value, if "oab" makes a counter-clockwise turn,
/// negative for clockwise turn, and zero if the points are collinear.
template <typename T>
double cross(const Vector2<T>& o, const Vector2<T>& a, const Vector2<T>& b)
{
    return (a.x() - o.x()) * (b.y() - o.y()) - (a.y() - o.y()) * (b.x() - o.x());
}

template <typename T>
bool vectorCompare(Vector2<T>& a, Vector2<T>& b)
{
    return a.x() < b.x() || (a.x() == b.x() && a.y() < b.y());
}

/// Returns a list of points on the convex hull in counter-clockwise order.
/// Note: the last point in the returned list is the same as the first one.
template <typename T>
std::vector<Vector2<T>> toConvexHull(std::vector<Vector2<T>> points)
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
template <typename T>
bool isNeighbour(std::shared_ptr<NavPoly<T>> polyA, std::shared_ptr<NavPoly<T>> polyB, Edge<T>& edge)
{
    if (polyA.get() == polyB.get()) {
        return false;
    }

    const auto& shapeA = polyA->_shape;
    const auto& shapeB = polyB->_shape;

    if (!intersects(shapeA->boundingBox(), shapeB->boundingBox())) {
        return false;
    }

    std::vector<Vector2<T>> connectedPoints;

    for (auto& pointA : shapeA->points()) {
        for (auto& pointB : shapeB->points()) {
            if (pointA == pointB) {
                connectedPoints.emplace_back(pointA);
            }
        }
    }

    if (connectedPoints.size() == 2) {
        LOGI << "Connected Polygons";
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

template <typename T>
void NavMesh<T>::addPoly(std::shared_ptr<ConvexShape<T>> poly)
{
    _mesh.push_back(std::make_shared<NavPoly<T>>(poly));
    regenerate();
}

template <typename T>
void NavMesh<T>::regenerate()
{
    for (auto I = begin(_mesh); I != end(_mesh); ++I) {
        (*I)->_neighbours.clear();
    }
    for (auto I = begin(_mesh); I != end(_mesh); ++I) {
        for (auto J = I; J != end(_mesh); ++J) {
            auto edge = Edge<T>{};
            auto neighbour = isNeighbour(*I, *J, edge);
            if (neighbour) {
                (*I)->_neighbours.emplace_back(*J, edge);
                (*J)->_neighbours.emplace_back(*I, edge);
            }
        }
    }
}

template <typename T>
std::vector<Vector2<T>> NavMesh<T>::navigationPath(const Vector2<T>& startPos, const Vector2<T>& targetPos)
{
}

/// Explicit template instantiation
template class NavMesh<float>;
template class NavMesh<double>;
template class NavMesh<int>;

} // namespace frontier