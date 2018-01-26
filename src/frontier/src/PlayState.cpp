#include <frontier/PlayState.hpp>

#include <log/log.hpp>

namespace frontier {

PlayState::PlayState() {}
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
void PlayState::update(std::chrono::milliseconds /* delta */) {}
void PlayState::render() {}
void PlayState::handleEvent(const SDL_Event& /* event */) {}

} // namespace frontier
