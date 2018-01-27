#pragma once

#include <math/Point2.hpp>
#include <math/Rect.hpp>

namespace frontier {

/// Determine if a point lies within the AABB rectangle.
///
/// @param point The point to consider.
/// @param rect The rect to consider.
/// @returns bool True if the point lies inside the rectangle, false otherwise.
bool intersects(const Point2i& point, const Recti& rect);

/// Determine if two AABB rectanlges intersect.
///
/// @param rect1 The first rect to consider.
/// @param rect2 The second rect to consider.
/// @returns bool True if the rectangles intersect, false otherwise.
bool intersects(const Recti& rect1, const Recti& rect2);

} // namespace frontier
