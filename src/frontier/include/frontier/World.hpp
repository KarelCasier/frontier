#pragma once

#include <chrono>
#include <texture_manager/TextureManager.hpp>
#include <frontier/Level.hpp>

namespace frontier {

class World {
public:
    World(std::shared_ptr<TextureManager> textureManager);

    void update(std::chrono::milliseconds delta);
    void render();

private:
    std::shared_ptr<TextureManager> _textureManager;
    std::shared_ptr<Level> _level;
};

} // namespace frontier
