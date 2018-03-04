#pragma once

#include <chrono>
#include <memory>

namespace frontier {

class RenderManager;
class TextureManager;
class InputManager;
class Level;

class World {
public:
    World(std::shared_ptr<RenderManager> renderManager,
          std::shared_ptr<TextureManager> textureManager,
          std::shared_ptr<InputManager> inputManager);

    void update(std::chrono::milliseconds delta);
    void render();

private:
    std::shared_ptr<RenderManager> _renderManager;
    std::shared_ptr<TextureManager> _textureManager;
    std::shared_ptr<InputManager> _inputManager;
    std::shared_ptr<Level> _level;
};

} // namespace frontier
