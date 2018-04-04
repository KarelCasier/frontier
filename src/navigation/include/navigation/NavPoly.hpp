#pragma once

#include <vector>
#include <map>

#include <math/Vector2.hpp>
#include <math/ConvexShape.hpp>

namespace frontier {

struct Edge {
    Vector2f start;
    Vector2f end;
    Vector2f mid;
};

struct NavPoly {
    NavPoly(ConvexShape<float> shape)
    : _shape{std::move(shape)}
    {
    }

    std::vector<std::pair<NavPoly, Edge>> _neighbours;

    ConvexShape<float> _shape;
};

} // namespace frontier
