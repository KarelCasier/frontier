#pragma once

#include <entityx/entityx.h>

namespace frontier {

class RenderSystem : public entityx::System<RenderSystem> {
public:
    RenderSystem() = default;
    ~RenderSystem() override = default;
};

} // namespace frontier
