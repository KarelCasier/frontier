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
bool intersects(const Vector2<T>& point, const Rect<T>& rect);

/// Determine if two AABB rectangles intersect.
///
/// @param rect1 The first rect to consider.
/// @param rect2 The second rect to consider.
/// @returns bool True if the rectangles intersect, false otherwise.
template <typename T>
bool intersects(const Rect<T>& rect1, const Rect<T>& rect2);

} // namespace frontier

