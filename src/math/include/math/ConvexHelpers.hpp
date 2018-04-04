#pragma once

#include <math/Vector2.hpp>

#include <vector>

namespace frontier {

/// 2D cross product of "oa" and "ob" vectors, i.e. z-component of their 3D cross product.
/// Returns a positive value if "oab" makes a counter-clockwise turn,
/// negative for clockwise turn, and zero if the points are collinear.
template <typename T>
double cross(const Vector2<T>& o, const Vector2<T>& a, const Vector2<T>& b)
{
    return (a.x() - o.x()) * (b.y() - o.y()) - (a.y() - o.y()) * (b.x() - o.x());
}

template <typename T>
bool lexicographVectorCompare(const Vector2<T>& a, const Vector2<T>& b)
{
    return a.x() < b.x() || (a.x() == b.x() && a.y() < b.y());
}

/// Returns a list of points on the convex hull in counter-clockwise order.
/// Note: the last point in the returned list is the same as the first one.
/// O(nlogn)
template <typename T>
std::vector<Vector2<T>> toConvexHull(std::vector<Vector2<T>> points)
{
    auto numPoints = static_cast<int>(points.size());
    auto k = 0;
    std::vector<Vector2<T>> hull(2 * numPoints);

    // Sort points lexicographically
    std::sort(points.begin(), points.end(), lexicographVectorCompare<T>);

    // Build lower hull
    for (auto i{0}; i < numPoints; ++i) {
        while (k >= 2 && cross(hull[k - 2], hull[k - 1], points[i]) <= 0) {
            k--;
        }
        hull[k++] = points[i];
    }

    // Build upper hull
    for (int i{numPoints - 2}, t{k + 1}; i >= 0; i--) {
        while (k >= t && cross(hull[k - 2], hull[k - 1], hull[i]) <= 0) {
            k--;
        }
        hull[k++] = points[i];
    }

    hull.resize(k);
    return hull;
}

} // namespace frontier
