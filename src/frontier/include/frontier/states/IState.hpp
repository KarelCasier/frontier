#pragma once

#include <chrono>
#include <SDL2/SDL_events.h>

namespace frontier {

class IState {
public:
    virtual ~IState() = default;
    /// Called when entering the state.
    virtual void onEnter() = 0;
    /// Called when exiting the state.
    virtual void onExit() = 0;
    /// Called to update.
    ///
    /// @param delta The time delta since last update.
    virtual void update(std::chrono::milliseconds delta) = 0;
    /// Called when an event occurs.
    ///
    /// @param event The event that occured.
    virtual void handleEvent(const SDL_Event& event) = 0;
    /// Called to render.
    virtual void render() = 0;
};

} // namespace frontier
