#pragma once

#include <entityx/entityx.h>

#include <math/Point2.hpp>

namespace frontier {

class Position : public entityx::Component<Position> {
public:
    Position(Point2i position)
    : _position{std::move(position)}
    {
    }

    Point2i _position;
};

} // namespace frontier
