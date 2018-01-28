#pragma once

#include <tinyxml2.h>
#include <string>
#include <frontier/Level.hpp>
#include <frontier/components/PositionComponent.hpp>
#include <frontier/components/SpriteComponent.hpp>
#include <frontier/components/VelocityComponent.hpp>

namespace frontier {

class LevelParser {
public:
    LevelParser(std::shared_ptr<TextureManager> textureManager);

    std::shared_ptr<Level> parse(const std::string& file);

private:
    entityx::Entity parseEntity(const tinyxml2::XMLElement* baseElement);
    SpriteComponent parseSpriteComponent(const tinyxml2::XMLElement* baseElement);
    PositionComponent parsePositionComponent(const tinyxml2::XMLElement* baseElement);
    VelocityComponent parseVelocityComponent(const tinyxml2::XMLElement* baseElement);

    void parseSystem(const tinyxml2::XMLElement* baseElement);

    std::shared_ptr<TextureManager> _textureManager;
    std::shared_ptr<Level> _level;
};

} // namespace frontier
