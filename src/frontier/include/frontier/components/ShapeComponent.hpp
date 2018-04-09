#pragma once

#include <entityx/entityx.h>

#include <math/Rect.hpp>

namespace frontier {

class ShapeComponent : public entityx::Component<ShapeComponent> {
public:
    enum class Type {
        Rect,
        Circle,
        Convex,
    };

    ShapeComponent(Vector2f rect)
    : _shape{std::move(rect)}
    , _type{Type::Rect}
    {
    }

    union {
        Vector2f _rect;
        // Circlef _circ;
        // ConvecShape<float> _convex;
    } _shape;
    Type _type;
};

} // namespace frontier
