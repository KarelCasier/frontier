#pragma once

#include <vector>
#include <map>

#include <math/Vector2.hpp>
#include <math/ConvexShape.hpp>

namespace frontier {

template <typename T>
struct Edge {
    Vector2<T> start;
    Vector2<T> end;
    Vector2<T> mid;
};

template <typename T>
struct NavPoly {
    NavPoly(std::shared_ptr<ConvexShape<T>> shape)
    : _shape{std::move(shape)}
    {
    }

    std::vector<std::pair<std::shared_ptr<NavPoly<T>>, Edge<T>>> _neighbours;

    std::shared_ptr<ConvexShape<T>> _shape;
};

} // namespace frontier
