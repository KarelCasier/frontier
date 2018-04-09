#pragma once

#include <vector>

#include <math/ConvexShape.hpp>
#include <math/Rect.hpp>
#include <math/Vector2.hpp>
#include <utils/Optional.hpp>

namespace frontier {

struct Manifest {
};

/// Determine if two AABB rectangles intersect.
///
/// @param rect1 The first rect to consider.
/// @param rect2 The second rect to consider.
/// @returns bool True if the rectangles intersect, false otherwise.
template <typename T>
inline bool intersects(const Rect<T>& rect1, const Rect<T>& rect2, double tol = 1.0)
{
    const auto left1 = rect1.x() - tol;
    const auto right1 = rect1.x() + rect1.w() + tol;
    const auto top1 = rect1.y() - tol;
    const auto bottom1 = rect1.y() + rect1.h() + tol;

    const auto left2 = rect2.x() - tol;
    const auto right2 = rect2.x() + rect2.w() + tol;
    const auto top2 = rect2.y() - tol;
    const auto bottom2 = rect2.y() + rect2.h() + tol;

    if (bottom1 <= top2 || top1 >= bottom2 || right1 <= left2 || left1 >= right2) {
        return false;
    }

    return true;
}

/// Get the furthest point in a given direction
template <typename T>
inline Vector2<T> supportPoint(const ConvexShape<T>& convexShape, const Vector2<T>& axis)
{
    auto largestProjection = std::numeric_limits<double>::lowest();
    const auto& points = convexShape.points();
    typename std::vector<Vector2<T>>::const_iterator furthestPoint;
    for (auto I = begin(points); I != end(points); ++I) {
        const auto projection = I->dot(axis);
        if (projection > largestProjection) {
            largestProjection = projection;
            furthestPoint = I;
        }
    }
    return *furthestPoint;
}

template <typename T>
inline double findAxisLeastPenetration(std::size_t& faceIdx, const ConvexShape<T>& shapeA, const ConvexShape<T>& shapeB)
{
    auto greatestDistance = std::numeric_limits<double>::lowest();
    auto bestIndex = std::size_t{0u};

    const auto& pointsA = shapeA.points();
    for (auto i{0u}; i < pointsA.size() - 1; ++i) {
        const auto& normal = shapeA.normal(i);
        const auto support = supportPoint(shapeB, -normal);
        const auto& point = pointsA[i];
        // Compute penetration distance (in B's model space)
        const auto penDist = normal.dot(support - point);
        if (penDist > greatestDistance) {
            greatestDistance = penDist;
            bestIndex = i;
        }
    }

    faceIdx = bestIndex;
    return greatestDistance;
}

template <typename T>
inline std::optional<Manifest> intersects(const ConvexShape<T>& shapeA, const ConvexShape<T>& shapeB)
{
    auto faceA = std::size_t{};
    const auto penA = findAxisLeastPenetration(faceA, shapeA, shapeB);
    if (penA >= 0.f) {
        return {};
    }
    auto faceB = std::size_t{};
    const auto penB = findAxisLeastPenetration(faceB, shapeB, shapeA);
    if (penB >= 0.f) {
        return {};
    }

    return Manifest{};
}

} // namespace frontier
