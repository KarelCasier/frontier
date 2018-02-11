#include <frontier/Level.hpp>

#include <frontier/systems/PhysicsSystem.hpp>
#include <frontier/systems/RenderSystem.hpp>
#include <frontier/systems/NavigationSystem.hpp>

namespace frontier {

using namespace std::chrono;

Level::Level(std::shared_ptr<TextureManager> textureManager)
: _textureManager{std::move(textureManager)}
{
    // Vector2f a{1.0, 1.0};
    // Vector2f b{10.0, 10.0};
    // Vector2f c{1.0, 10.0};
    //
    // Vector2f d{10.0, 1.0};
    //
    // std::vector<Vector2f> pointsA = {a,b,c};
    // std::vector<Vector2f> pointsB = {a,d,b};
    //
    // auto shapeA = std::make_shared<ConvexShape<float>>(pointsA);
    // auto shapeB = std::make_shared<ConvexShape<float>>(pointsB);
    //_navMesh.addPoly(shapeA);
    //_navMesh.addPoly(shapeB);
}

void Level::finishInit()
{
    _entityX.systems.configure();
}

void Level::update(milliseconds delta)
{
    const auto secondsDelta = duration<double, seconds::period>(delta).count();
    _entityX.systems.update<PhysicsSystem>(secondsDelta);
    _entityX.systems.update<NavigationSystem>(secondsDelta);
}

void Level::render()
{
    _entityX.systems.update<RenderSystem>(0);
}

} // namespace frontier
