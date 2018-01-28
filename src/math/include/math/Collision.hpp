#pragma once

#include <math/Vector2.hpp>
#include <math/Rect.hpp>

namespace frontier {

/// Determine if a point lies within the AABB rectangle.
///
/// @param point The point to consider.
/// @param rect The rect to consider.
/// @returns bool True if the point lies inside the rectangle, false otherwise.
bool intersects(const Vector2f& point, const Rectf& rect);

/// Determine if two AABB rectangles intersect.
///
/// @param rect1 The first rect to consider.
/// @param rect2 The second rect to consider.
/// @returns bool True if the rectangles intersect, false otherwise.
bool intersects(const Rectf& rect1, const Rectf& rect2);

} // namespace frontier

