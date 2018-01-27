#include <frontier/systems/RenderSystem.hpp>

namespace frontier {

RenderSystem::RenderSystem(std::shared_ptr<TextureManager> textureManager)
: _textureManager{std::move(textureManager)}
{
}

void RenderSystem::update(entityx::EntityManager& /* entities*/,
                          entityx::EventManager& /* events*/,
                          entityx::TimeDelta /* dt*/)
{
}

} // namespace frontier
