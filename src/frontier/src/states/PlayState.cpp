#include <frontier/states/PlayState.hpp>

#include <log/log.hpp>

namespace frontier {

PlayState::PlayState(std::shared_ptr<TextureManager> textureManager)
: _textureManager{std::move(textureManager)}
, _world{_textureManager}
{
}

PlayState::~PlayState()
{
    LOGD << "Destroy";
}

void PlayState::onEnter()
{
    LOGD << "PlayState::onEnter()";
}
void PlayState::onExit()
{
    LOGD << "PlayState::onExit()";
}
void PlayState::update(std::chrono::milliseconds delta)
{
    _world.update(delta);
}
void PlayState::render()
{
    _world.render();
}
void PlayState::handleEvent(const SDL_Event& /* event */) {}

} // namespace frontier
