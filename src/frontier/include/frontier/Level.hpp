#pragma once

#include <chrono>
#include <entityx/entityx.h>
#include <graphics/TextureManager.hpp>
#include <input/InputManager.hpp>
#include <navigation/NavMesh.hpp>

namespace frontier {

class Level {
public:
    Level(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<InputManager> inputManager);

    void finishInit();
    void update(std::chrono::milliseconds delta);
    void render();

private:
    friend class LevelParser;

    std::shared_ptr<TextureManager> _textureManager;
    std::shared_ptr<InputManager> _inputManager;
    entityx::EntityX _entityX;
};

} // namespace frontier
