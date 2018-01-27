#pragma once

#include <entityx/entityx.h>

#include <texture_manager/TextureManager.hpp>
#include <math/Rect.hpp>

namespace frontier {

class Sprite : public entityx::Component<Sprite> {
public:
    Sprite(TextureRef* ref, Recti rect)
    : _ref{ref}
    , _rect{std::move(rect)}
    {
    }

    TextureRef* _ref;
    Recti _rect;
}; // namespace frontier

} // namespace frontier
