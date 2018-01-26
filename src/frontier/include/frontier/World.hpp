#pragma once

#include <chrono>
#include <entityx/entityx.h>

namespace frontier {

class World : public entityx::EntityX {
    World();

    void update(std::chrono::milliseconds delta);
};

} // namespace frontier
