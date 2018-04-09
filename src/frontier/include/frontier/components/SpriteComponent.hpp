#pragma once

#include <entityx/entityx.h>

#include <graphics/TextureManager.hpp>
#include <math/Rect.hpp>

namespace frontier {

class SpriteComponent : public entityx::Component<SpriteComponent> {
public:
    SpriteComponent(TextureRef* ref, Rectf srcRect)
    : _ref{ref}
    , _srcRect{std::move(srcRect)}
    {
    }

    TextureRef* _ref;
    Rectf _srcRect;
}; // namespace frontier

} // namespace frontier
