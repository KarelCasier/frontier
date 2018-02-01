#include <frontier/LevelParser.hpp>

#include <frontier/systems/PhysicsSystem.hpp>
#include <frontier/systems/RenderSystem.hpp>
#include <log/log.hpp>
#include <math/Misc.hpp>
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

Vector2f parseVector2f(const XMLElement* element)
{
    element = element->FirstChildElement();
    assertName(element, "x");
    const auto x = element->FloatText(0);

    element = element->NextSiblingElement();
    assertName(element, "y");
    const auto y = element->FloatText(0);

    return {x, y};
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
        if (isEqual(name, "positioncomponent")) {
            entity.assign<PositionComponent>(parsePositionComponent(component));
        } else if (isEqual(name, "physicscomponent")) {
            entity.assign<PhysicsComponent>(parsePhysicsComponent(component));
        } else if (isEqual(name, "spritecomponent")) {
            entity.assign<SpriteComponent>(parseSpriteComponent(component));
        } else if (isEqual(name, "rotationcomponent")) {
            entity.assign<RotationComponent>(parseRotationComponent(component));
        } else {
            LOGE << "Unknown component: " << name;
        }
    }
    return entity;
}

PositionComponent LevelParser::parsePositionComponent(const XMLElement* baseElement)
{
    assertName(baseElement, "positioncomponent");

    auto element = baseElement->FirstChildElement();
    assertName(element, "position");
    auto position = parseVector2f(element);

    return {position};
}

PhysicsComponent LevelParser::parsePhysicsComponent(const XMLElement* baseElement)
{
    assertName(baseElement, "physicscomponent");

    auto element = baseElement->FirstChildElement();
    assertName(element, "velocity");
    auto velocity = parseVector2f(element);

    element = element->NextSiblingElement("friction");
    if (element) {
        assertName(element, "friction");
        const auto friction = element->FloatText(0);
        return {velocity, friction};
    }

    return {velocity};
}

RotationComponent LevelParser::parseRotationComponent(const XMLElement* baseElement)
{
    assertName(baseElement, "rotationcomponent");

    auto element = baseElement->FirstChildElement();
    assertName(element, "orientation");
    auto orientation = toRadians(element->DoubleText(0));

    element = element->NextSiblingElement();
    assertName(element, "angularvelocity");
    const auto angularVelocity = toRadians(element->DoubleText(0));

    element = element->NextSiblingElement();
    assertName(element, "torque");
    const auto torque = toRadians(element->DoubleText(0));

    return {orientation, angularVelocity, torque};
}

SpriteComponent LevelParser::parseSpriteComponent(const XMLElement* baseElement)
{
    assertName(baseElement, "spritecomponent");

    auto element = baseElement->FirstChildElement();
    assertName(element, "asset");
    const auto asset = element->GetText();

    element = element->NextSiblingElement();
    assertName(element, "x");
    const auto x = element->FloatText(0);

    element = element->NextSiblingElement();
    assertName(element, "y");
    const auto y = element->FloatText(0);

    element = element->NextSiblingElement();
    assertName(element, "w");
    const auto w = element->FloatText(0);

    element = element->NextSiblingElement();
    assertName(element, "h");
    const auto h = element->FloatText(0);

    auto textureRef = _textureManager->loadTexture(asset);

    return {textureRef, Rectf{x, y, w, h}};
}

void LevelParser::parseSystem(const XMLElement* baseElement)
{
    const auto name = baseElement->Name();
    if (isEqual(name, "rendersystem")) {
        _level->_entityX.systems.add<RenderSystem>(_textureManager);
    } else if (isEqual(name, "physicssystem")) {
        _level->_entityX.systems.add<PhysicsSystem>();
    } else {
        LOGE << "Unknown system: " << name;
    }
}

} // namespace frontier
