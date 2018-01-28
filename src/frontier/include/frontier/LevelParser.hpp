#pragma once

#include <tinyxml2.h>
#include <string>
#include <frontier/Level.hpp>
#include <frontier/components/Position.hpp>
#include <frontier/components/Sprite.hpp>

namespace frontier {

class LevelParser {
public:
    LevelParser(std::shared_ptr<TextureManager> textureManager);

    std::shared_ptr<Level> parse(const std::string& file);

private:
    entityx::Entity parseEntity(const tinyxml2::XMLElement* baseElement);
    Sprite parseSprite(const tinyxml2::XMLElement* baseElement);
    Position parsePosition(const tinyxml2::XMLElement* baseElement);

    void parseSystem(const tinyxml2::XMLElement* baseElement);

    std::shared_ptr<TextureManager> _textureManager;
    std::shared_ptr<Level> _level;
};

} // namespace frontier
