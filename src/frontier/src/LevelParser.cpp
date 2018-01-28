#include <frontier/LevelParser.hpp>

#include <frontier/systems/RenderSystem.hpp>
#include <log/log.hpp>
#include <sstream>

namespace {

using namespace frontier;
using namespace entityx;
using namespace tinyxml2;

// Case insensitive string comparrison.
bool isEqual(const std::string_view& left, const std::string_view& right)
{
    auto lowerLeft = std::string{};
    std::transform(begin(left), end(left), std::back_inserter(lowerLeft), ::tolower);
    auto lowerRight = std::string{};
    std::transform(begin(right), end(right), std::back_inserter(lowerRight), ::tolower);
    return lowerLeft.compare(lowerRight) == 0;
}

/// Ensure that the element name is as expected.
void assertName(const XMLElement* element, const std::string_view& name)
{
    assert(element);
    if (!isEqual(element->Name(), name)) {
        auto err = std::stringstream{};
        err << "Parsing error. Expected: '" << name << "' but found: '" << element->Name() << "'";
        LOGE << err.str();
        throw std::runtime_error(err.str());
    }
}

} // namespace

namespace frontier {

LevelParser::LevelParser(std::shared_ptr<TextureManager> textureManager)
: _textureManager{std::move(textureManager)}
{
}

std::shared_ptr<Level> LevelParser::parse(const std::string& file)
{
    const auto filePath = std::string{"assets/"} + file;
    XMLDocument doc;
    doc.LoadFile(filePath.c_str());
    LOGI << "Parsing file: " << file;

    _level = std::make_shared<Level>(_textureManager);

    auto element = doc.RootElement();
    assertName(element, "level");

    element = element->FirstChildElement();
    assertName(element, "systems");
    for (auto system = element->FirstChildElement(); system != nullptr; system = system->NextSiblingElement()) {
        parseSystem(system);
    }

    element = element->NextSiblingElement();
    assertName(element, "entities");
    for (auto entity = element->FirstChildElement(); entity != nullptr; entity = entity->NextSiblingElement()) {
        parseEntity(entity);
    }

    _level->finishInit();
    return _level;
}

Entity LevelParser::parseEntity(const XMLElement* baseElement)
{
    assertName(baseElement, "entity");
    auto entity = _level->_entityX.entities.create();
    for (auto component = baseElement->FirstChildElement(); component != nullptr;
         component = component->NextSiblingElement()) {
        const auto name = component->Name();
        if (isEqual(name, "position")) {
            entity.assign<Position>(parsePosition(component));
        } else if (isEqual(name, "sprite")) {
            entity.assign<Sprite>(parseSprite(component));
        } else {
            LOGE << "Unknown component: " << name;
        }
    }
    return entity;
}

Position LevelParser::parsePosition(const XMLElement* baseElement)
{
    assertName(baseElement, "position");

    auto element = baseElement->FirstChildElement();
    assertName(element, "x");
    const auto x = element->IntText(0);

    element = element->NextSiblingElement();
    assertName(element, "y");
    const auto y = element->IntText(0);

    return {{x, y}};
}

Sprite LevelParser::parseSprite(const XMLElement* baseElement)
{
    assertName(baseElement, "sprite");

    auto element = baseElement->FirstChildElement();
    assertName(element, "asset");
    const auto asset = element->GetText();

    element = element->NextSiblingElement();
    assertName(element, "x");
    const auto x = element->IntText(0);

    element = element->NextSiblingElement();
    assertName(element, "y");
    const auto y = element->IntText(0);

    element = element->NextSiblingElement();
    assertName(element, "w");
    const auto w = element->IntText(0);

    element = element->NextSiblingElement();
    assertName(element, "h");
    const auto h = element->IntText(0);

    auto textureRef = _textureManager->loadTexture(asset);

    return {textureRef, Recti{x, y, w, h}};
}

void LevelParser::parseSystem(const XMLElement* baseElement)
{
    const auto name = baseElement->Name();
    if (isEqual(name, "rendersystem")) {
        _level->_entityX.systems.add<RenderSystem>(_textureManager);
    } else {
        LOGE << "Unknown system: " << name;
    }
}

} // namespace frontier
