#pragma once

#include <chrono>
#include <entityx/entityx.h>
#include <texture_manager/TextureManager.hpp>

namespace frontier {

class Level {
public:
    Level(std::shared_ptr<TextureManager> textureManager);

    void finishInit();
    void update(std::chrono::milliseconds delta);
    void render();

private:
    friend class LevelParser;

    std::shared_ptr<TextureManager> _textureManager;
    entityx::EntityX _entityX;
};

} // namespace frontier
