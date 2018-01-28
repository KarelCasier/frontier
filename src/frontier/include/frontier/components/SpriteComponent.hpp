#pragma once

#include <entityx/entityx.h>

#include <texture_manager/TextureManager.hpp>
#include <math/Rect.hpp>

namespace frontier {

class SpriteComponent : public entityx::Component<SpriteComponent> {
public:
    SpriteComponent(TextureRef* ref, Rectf rect)
    : _ref{ref}
    , _rect{std::move(rect)}
    {
    }

    TextureRef* _ref;
    Rectf _rect;
}; // namespace frontier

} // namespace frontier
