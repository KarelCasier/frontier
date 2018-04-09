#include <frontier/LevelParser.hpp>

#include <frontier/systems/InputSystem.hpp>
#include <frontier/systems/NavigationSystem.hpp>
#include <frontier/systems/PhysicsSystem.hpp>
#include <frontier/systems/RenderSystem.hpp>
#include <graphics/TextureManager.hpp>
#include <graphics/Util.hpp>
#include <graphics/Window.hpp>
#include <input/InputManager.hpp>
#include <log/log.hpp>
#include <math/Misc.hpp>

#include <sstream>

namespace {

using namespace frontier;
using namespace entityx;
using namespace tinyxml2;

/// Case insensitive string comparrison.
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

std::shared_ptr<NavigationSystem> parseNavigationSystem(const XMLElement* baseElement)
{
    assertName(baseElement, "navigationsystem");
    return std::make_shared<NavigationSystem>(baseElement->GetText());
}

} // namespace

namespace frontier {

LevelParser::LevelParser(std::shared_ptr<Window> window,
                         std::shared_ptr<TextureManager> textureManager,
                         std::shared_ptr<InputManager> inputManager)
: _window{std::move(window)}
, _textureManager{std::move(textureManager)}
, _inputManager{std::move(inputManager)}
{
}

std::shared_ptr<Level> LevelParser::parse(const std::string& file)
{
    const auto filePath = getResourcePath() + file;
    XMLDocument doc;
    doc.LoadFile(filePath.c_str());
    if (doc.Error()) {
        auto error = std::string{"XML Error: "} + doc.ErrorStr();
        throw std::runtime_error{error};
    }
    LOGI << "Parsing file: " << file;

    _level = std::make_shared<Level>(_window, _textureManager, _inputManager);

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
        if (isEqual(name, "transformcomponent")) {
            entity.assign<TransformComponent>(parseTransformComponent(component));
        } else if (isEqual(name, "physicscomponent")) {
            entity.assign<PhysicsComponent>(parsePhysicsComponent(component));
        } else if (isEqual(name, "spritecomponent")) {
            entity.assign<SpriteComponent>(parseSpriteComponent(component));
        } else if (isEqual(name, "shapecomponent")) {
            entity.assign<ShapeComponent>(parseShapeComponent(component));
        } else {
            LOGE << "Unknown component: " << name;
        }
    }
    return entity;
}

TransformComponent LevelParser::parseTransformComponent(const XMLElement* baseElement)
{
    assertName(baseElement, "transformcomponent");

    auto element = baseElement->FirstChildElement();
    assertName(element, "position");
    const auto position = parseVector2f(element);

    element = element->NextSiblingElement();
    assertName(element, "orientation");
    const auto orientation = toRadians(element->DoubleText(0));

    return {position, orientation};
}

PhysicsComponent LevelParser::parsePhysicsComponent(const XMLElement* baseElement)
{
    assertName(baseElement, "physicscomponent");

    auto element = baseElement->FirstChildElement();
    assertName(element, "mass");
    const auto mass = element->DoubleText();

    element = element->NextSiblingElement("velocity");
    assertName(element, "velocity");
    const auto velocity = parseVector2f(element);

    element = element->NextSiblingElement("friction");
    assertName(element, "friction");
    const auto friction = element->DoubleText(0);

    element = element->NextSiblingElement();
    assertName(element, "angularvelocity");
    const auto angularVelocity = toRadians(element->DoubleText(0));

    element = element->NextSiblingElement();
    assertName(element, "torque");
    const auto torque = toRadians(element->DoubleText(0));

    return {mass, velocity, friction, angularVelocity, torque};
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

ShapeComponent LevelParser::parseShapeComponent(const XMLElement* baseElement)
{
    assertName(baseElement, "shapecomponent");

    auto element = baseElement->FirstChildElement();
    assertName(element, "w");
    const auto w = element->FloatText(0);

    element = element->NextSiblingElement();
    assertName(element, "h");
    const auto h = element->FloatText(0);

    return {{w, h}};
}

void LevelParser::parseSystem(const XMLElement* baseElement)
{
    const auto name = baseElement->Name();
    if (isEqual(name, "rendersystem")) {
        _level->_entityX.systems.add<RenderSystem>(_window);
    } else if (isEqual(name, "physicssystem")) {
        _level->_entityX.systems.add<PhysicsSystem>();
    } else if (isEqual(name, "navigationsystem")) {
        _level->_entityX.systems.add(parseNavigationSystem(baseElement));
    } else if (isEqual(name, "inputsystem")) {
        _level->_entityX.systems.add<InputSystem>(_inputManager);
    } else {
        LOGE << "Unknown system: " << name;
    }
}

} // namespace frontier
