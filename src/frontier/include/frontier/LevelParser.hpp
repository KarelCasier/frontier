#pragma once

#include <tinyxml2.h>
#include <string>
#include <frontier/Level.hpp>
#include <frontier/components/PhysicsComponent.hpp>
#include <frontier/components/SpriteComponent.hpp>
#include <frontier/components/TransformComponent.hpp>

namespace frontier {

class Window;
class TextureManager;
class InputManager;

class LevelParser {
public:
    LevelParser(std::shared_ptr<Window> window,
                std::shared_ptr<TextureManager> textureManager,
                std::shared_ptr<InputManager> inputManager);

    std::shared_ptr<Level> parse(const std::string& file);

private:
    entityx::Entity parseEntity(const tinyxml2::XMLElement* baseElement);
    PhysicsComponent parsePhysicsComponent(const tinyxml2::XMLElement* baseElement);
    TransformComponent parseTransformComponent(const tinyxml2::XMLElement* baseElement);
    SpriteComponent parseSpriteComponent(const tinyxml2::XMLElement* baseElement);

    void parseSystem(const tinyxml2::XMLElement* baseElement);

    std::shared_ptr<Window> _window;
    std::shared_ptr<TextureManager> _textureManager;
    std::shared_ptr<InputManager> _inputManager;
    std::shared_ptr<Level> _level;
};

} // namespace frontier
