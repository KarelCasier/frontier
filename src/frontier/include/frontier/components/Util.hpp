#pragma once

#include <vector>

#include <frontier/components/TransformComponent.hpp>
#include <frontier/components/ShapeComponent.hpp>
#include <graphics/Transform.hpp>
#include <math/Misc.hpp>
#include <math/ConvexShape.hpp>

namespace frontier {

/// Get the transformed shape of an entity from its transform and shape.
inline ConvexShape<float> transformedShape(entityx::ComponentHandle<TransformComponent> transComp,
                                           entityx::ComponentHandle<ShapeComponent> shapeComp)
{
    assert(shapeComp->_type == ShapeComponent::Type::Rect); // TODO support other shapes

    auto trans = Transform{};
    trans.translate(transComp->_position + shapeComp->_shape._rect / 2.f);
    trans.rotate(toDegrees(transComp->_orientation));
    trans.translate(-(transComp->_position + shapeComp->_shape._rect / 2.f));

    auto points = Rectf{transComp->_position, shapeComp->_shape._rect}.points();
    auto transformedPoints = std::vector<Vector2f>{};
    std::transform(begin(points), end(points), back_inserter(transformedPoints),
                   [&trans](const auto& point) { return trans.transformPoint(point); });
    return {std::move(transformedPoints)};
}

} // namespace frontier
