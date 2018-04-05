#pragma once

#include <math/Vector2.hpp>
#include <math/Rect.hpp>

namespace frontier {

/// Determine if a point lies within the AABB rectangle.
///
/// @param point The point to consider.
/// @param rect The rect to consider.
/// @returns bool True if the point lies inside the rectangle, false otherwise.
template <typename T>
inline bool intersects(const Vector2<T>& point, const Rect<T>& rect)
{
    return (point.x() > rect.x() && point.x() < rect.x() + rect.w()) ||
           (point.y() > rect.y() && point.y() < rect.y() + rect.h());
}

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

} // namespace frontier

