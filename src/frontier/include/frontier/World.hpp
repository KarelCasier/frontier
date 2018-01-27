#pragma once

#include <chrono>
#include <entityx/entityx.h>
#include <texture_manager/TextureManager.hpp>

namespace frontier {

class World {
public:
    World(std::shared_ptr<TextureManager> textureManager);

    void update(std::chrono::milliseconds delta);
    void render();

private:
    std::shared_ptr<TextureManager> _textureManager;
    TextureRef* ref;
    entityx::EntityX _entityX;
};

} // namespace frontier
